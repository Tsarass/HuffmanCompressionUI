#include "ArchiveIO.h"

using namespace std;

/*Runs the compression algorithm in a worker thread and writes the
compressed output file.*/
int Compress(NewArchiveViewContainer^ fileInfo, System::ComponentModel::BackgroundWorker^ worker, System::ComponentModel::DoWorkEventArgs ^ e) {
	int numfiles = fileInfo->numfiles;

	//create a temp name for the archive
	System::String^ outfiletmp = fileInfo->archpath + L".tmp";

	//open output file
	pin_ptr<const wchar_t> outfiletmp_wch = PtrToStringChars(outfiletmp);	//convert to wchar_t
	ofstream out(outfiletmp_wch, ios::binary);
	//fist 4 bytes contain magic header TCC
	const char magic_header[4] = "TCC";
	out.write(magic_header, 4);
	//next 4 bytes contain number of files
	out.write(reinterpret_cast<const char*>(&numfiles), sizeof(numfiles));
	//next block of data contains filenames, uncompressed and compressed sizes of files
	vector<std::streampos> uncompsize_positions;	//holds the file position in which to write the uncompressed file sizes
	vector<std::streampos> compsize_positions;		//holds the file position in which to write the compressed file sizes
	for (int fileid = 0; fileid < numfiles; fileid++) {
		//write 2 bytes containing length of filename
		String^ fullfilename = fileInfo->files[fileid]->folderpath + L"\\" + fileInfo->files[fileid]->filename;
		pin_ptr<const wchar_t> filename_wch = PtrToStringChars(fullfilename);	//convert to wchar_t
		short filenamesz = fullfilename->Length * sizeof(wchar_t);
		out.write(reinterpret_cast<const char*>(&filenamesz), sizeof(short));
		//write the filename as a char sequence
		out.write(reinterpret_cast<const char*>(filename_wch), filenamesz);
		//next 4 bytes contain the number of bytes in original file (placeholder)
		int plcholder = 0;
		uncompsize_positions.push_back(out.tellp());
		out.write(reinterpret_cast<const char*>(&plcholder), sizeof(int));
		//next 4 bytes contain the compressed byte size (placeholder)
		compsize_positions.push_back(out.tellp());
		out.write(reinterpret_cast<const char*>(&plcholder), sizeof(int));
	}

	for (int fileid = 0; fileid < numfiles; fileid++) {

		pin_ptr<const wchar_t> filepath_wch = PtrToStringChars(fileInfo->files[fileid]->fullpath);	//convert to wchar_t

		//read the contents and size of input file
		ifstream is(filepath_wch, ifstream::binary);
		if (!is) return 0;
		is.seekg(0, is.end);
		int length = is.tellg();
		is.seekg(0, is.beg);

		unsigned char *buffer = new unsigned char[length];

		// read data as a block
		is.read(reinterpret_cast<char *> (buffer), length);
		is.close();

		FreqTable fdat{ buffer, length };

		//Create the huffman tree
		Tree tree;
		fbpair dummydat;
		fbpair leaf1, leaf2;
		vector<fbpair> freqtable = fdat.table;	//make a copy of frequency table
		while (!fdat.table.empty())
		{
			leaf1.byte = 0; leaf1.freq = -1;	//init with frequency of -1 so that tree insertion knows if there is a leaf to insert
			leaf2.byte = 0; leaf2.freq = -1;
			if (!fdat.table.empty()) {
				leaf1 = fdat.table.back();
				fdat.table.pop_back();
			}
			if (!fdat.table.empty()) {
				leaf2 = fdat.table.back();
				fdat.table.pop_back();
			}
			dummydat = tree.addNode(leaf1, leaf2);
			if (!fdat.table.empty()) {
				fdat.insert_in_sorted(dummydat);
			}
		}

		HuffDict huffdict{ &tree };
		HuffEncoder encoder{ buffer, length, &huffdict };
		//next 2 bytes contain the number of dictionary entries
		short dictentries = huffdict.num_entries();
		out.write(reinterpret_cast<const char*>(&dictentries), sizeof(short));
		//next block contains the frequency table
		for (vector<fbpair>::iterator it = freqtable.begin(); it != freqtable.end(); ++it) {
			out.write(reinterpret_cast<const char*>(&(*it).byte), sizeof(char));
			out.write(reinterpret_cast<const char*>(&(*it).freq), sizeof(int));
		}

		if (length > 0) {

			//write encoded data
			int totalsz = 0;
			while (!encoder.isdone()) {
				int size = encoder.encode_chunk_ex();
				out.write(encoder.get_bitstream_ptr(), size);
				totalsz += size;
				//worker->ReportProgress(encoder.progress()*100);
			}
			//save current position in file
			std::streampos current_pos = out.tellp();
			//go back in the file and write the uncompressed file size
			out.seekp(uncompsize_positions[fileid]);
			out.write(reinterpret_cast<const char*>(&length), sizeof(int));
			//go back in the file and write the compressed file size
			out.seekp(compsize_positions[fileid]);
			out.write(reinterpret_cast<const char*>(&totalsz), sizeof(int));
			//go back to writing in the proper position
			out.seekp(current_pos);

			delete[] buffer;

		}

	}

	out.close();

	//delete old archive if it exists and rename tmp file to normal
	System::IO::File::Delete(fileInfo->archpath);
	System::IO::File::Move(outfiletmp, fileInfo->archpath);
	return 1;
}



/*Runs the decompression algorithm in a worker thread and writes the
decompressed output files.*/
int Decompress(ExtractArchiveContainer^ fileInfo, System::ComponentModel::BackgroundWorker^ worker, System::ComponentModel::DoWorkEventArgs ^ e) {
	OpenArchiveContainer^ thisarchInfo = ReadArchiveHeader(fileInfo->archivepath);
	if (!thisarchInfo->validarch) {
		return 0;
	}

	//open archive
	pin_ptr<const wchar_t> archpath_wch = PtrToStringChars(fileInfo->archivepath);	//convert to wchar_t
	ifstream is(archpath_wch, ifstream::binary);
	if (!is) return 0;
	//move to end of header
	is.seekg(thisarchInfo->endHeaderPos);
	//loop over all files in archive
	for (int fileid = 0; fileid < thisarchInfo->numfiles; fileid++) {
		//read next 2 bytes for number of frequency table entries
		short numentries = 0;
		is.read(reinterpret_cast<char *> (&numentries), sizeof(short));
		//read the frequency table
		unsigned char* keys = new unsigned char[numentries];
		int* freqs = new int[numentries];
		for (int i = 0; i < numentries; i++) {
			is.read(reinterpret_cast<char *> (&keys[i]), sizeof(char));
			is.read(reinterpret_cast<char *> (&freqs[i]), sizeof(int));
		}
		FreqTable fdat{ numentries, keys, freqs };
		delete[] freqs;
		delete[] keys;

		int length = thisarchInfo->compsizes[fileid];

		//open output file
		String^ fullpath = fileInfo->extractdir + thisarchInfo->folderpaths[fileid];
		String^ outputdir = fullpath +  L'\\' + thisarchInfo->filenames[fileid];
		pin_ptr<const wchar_t> output_wch = PtrToStringChars(outputdir);	//convert to wchar_t
		//check if directory exists
		
		if (!System::IO::Directory::Exists(fullpath)) {
			System::IO::DirectoryInfo^ dir = System::IO::Directory::CreateDirectory(fullpath);
		}
		ofstream out(output_wch, ios::binary);

		if (length > 0) {

			unsigned char *buffer = new unsigned char[length];

			// read data as a block
			is.read(reinterpret_cast<char *> (buffer), length);

			//Create the huffman tree
			Tree tree;
			fbpair dummydat;
			fbpair leaf1, leaf2;
			while (!fdat.table.empty())
			{
				leaf1.byte = 0; leaf1.freq = -1;	//init with frequency of -1 so that tree insertion knows if there is a leaf to insert
				leaf2.byte = 0; leaf2.freq = -1;
				if (!fdat.table.empty()) {
					leaf1 = fdat.table.back();
					fdat.table.pop_back();
				}
				if (!fdat.table.empty()) {
					leaf2 = fdat.table.back();
					fdat.table.pop_back();
				}
				dummydat = tree.addNode(leaf1, leaf2);
				if (!fdat.table.empty()) {
					fdat.insert_in_sorted(dummydat);
				}
			}

			HuffDecoder decoder{ buffer, length, thisarchInfo->uncompsizes[fileid], &tree };

			while (!decoder.isdone()) {
				int size = decoder.decode_chunk();
				out.write(decoder.get_bytestream_ptr(), size);
			}

			delete[] buffer;

		}

		out.close();

	}

	is.close();

	return 1;
}



/*Reads the archive provided in archivepath parameter and returns
a valid OpenArchiveContainer object if successful.*/
OpenArchiveContainer^ ReadArchiveHeader(System::String^ archivepath) {
	//store an invalid archive container
	OpenArchiveContainer^ invalid_arch = gcnew OpenArchiveContainer{};

	//open archive
	pin_ptr<const wchar_t> archpath_wch = PtrToStringChars(archivepath);	//convert to wchar_t
	ifstream is(archpath_wch, ifstream::binary);
	if (!is) return invalid_arch;
	is.seekg(0, is.beg);
	//first read file header
	char header[4];
	char requestheader[4] = "TCC";
	is.read(reinterpret_cast<char *> (header), 4);
	if (strcmp(header, requestheader)) {
		//failed to validate header
		return invalid_arch;
	}
	//read next 4 bytes: number of files
	int numfiles = 0;
	is.read(reinterpret_cast<char *> (&numfiles), sizeof(int));
	//loop all file info in the header
	cli::array<String^>^ filenames = gcnew cli::array<String^>(numfiles);
	cli::array<Int32>^ uncompsizes = gcnew cli::array<Int32>(numfiles);
	cli::array<Int32>^ compsizes = gcnew cli::array<Int32>(numfiles);
	for (int fileid = 0; fileid < numfiles; fileid++) {
		//read 2 bytes containing length of filename
		short filenamesz;
		is.read(reinterpret_cast<char *> (&filenamesz), sizeof(short));
		//read filename
		wchar_t* filename_wch = new wchar_t[filenamesz];
		is.read(reinterpret_cast<char *> (filename_wch), filenamesz);
		String^ filename = gcnew String(filename_wch, 0, filenamesz/sizeof(wchar_t));
		delete[] filename_wch;
		filenames[fileid] = filename;
		//read 4 bytes containing uncompressed file size
		int uncompsize = 0;
		is.read(reinterpret_cast<char *> (&uncompsize), sizeof(int));
		uncompsizes[fileid] = uncompsize;
		//read 4 bytes containing compressed file size
		int compsize = 0;
		is.read(reinterpret_cast<char *> (&compsize), sizeof(int));
		compsizes[fileid] = compsize;
	}

	int endpos = is.tellg();

	is.close();

	//construct a valid OpenArchiveContainer
	OpenArchiveContainer^ valid_arch = gcnew OpenArchiveContainer{ archivepath, filenames, compsizes, uncompsizes, endpos };

	return valid_arch;
}