#include "WindowInfo.h"

FileInfoContainer::FileInfoContainer(cli::array<System::String^>^ filepaths, cli::array<System::String^>^ filenames, System::String ^ outfile)
{
	this->numfiles = filepaths->Length;

	//set up the ascii strings
	this->filepaths = filepaths;
	this->filenames = filenames;
	this->outfile = outfile;

	/*convert to unicode strings & wchar_t arrays and store*/
	int numfiles = filepaths->Length;
	//initialize unicode string arrays
	this->filepaths_w = gcnew cli::array<System::String^>(numfiles);
	this->filenames_w = gcnew cli::array<System::String^>(numfiles);
	this->outfile_w = gcnew String("");
	//convert and store
	System::Text::Encoding^ unicode = System::Text::Encoding::Unicode;
	for (int i = 0; i < numfiles; i++) {
		this->filepaths_w[i] = unicode->GetString(unicode->GetBytes(filepaths[i]));
		this->filenames_w[i] = unicode->GetString(unicode->GetBytes(filenames[i]));
	}
	this->outfile_w = unicode->GetString(unicode->GetBytes(outfile));
}

OpenArchiveContainer::OpenArchiveContainer(System::String^ archivepath, cli::array<System::String^>^ filenames,
											cli::array<int>^ compsizes, cli::array<int>^ uncompsizes, int endHeaderPos) {
	this->archivepath = archivepath;
	this->compsizes = compsizes;
	this->uncompsizes = uncompsizes;
	this->numfiles = filenames->Length;
	this->validarch = true;
	this->endHeaderPos = endHeaderPos;

	//convert fullpath filenames to filename + folderpath
	this->filenames = gcnew cli::array<String^>(filenames->Length);
	this->folderpaths = gcnew cli::array<String^>(filenames->Length);
	for (int i = 0; i < filenames->Length; i++) {
		int pos = filenames[i]->LastIndexOf("\\");
		this->folderpaths[i] = filenames[i]->Substring(0, pos);
		this->filenames[i] = filenames[i]->Substring(pos + 1);
	}
}

ExtractArchiveContainer::ExtractArchiveContainer(String^ archivepath, String^ extractdir) {
	this->archivepath = archivepath;
	this->extractdir = extractdir;
}

NewArchiveFile::NewArchiveFile(String^ filename, String^ folderpath, String^ fullpath, String^ extension, String^ modified, Int32 size) {
	this->filename = filename;
	this->folderpath = folderpath;
	this->fullpath = fullpath;
	this->extension = extension;
	this->modified = modified;
	this->size = size;
	this->tag = fullpath;
}

NewArchiveFilePredicate::NewArchiveFilePredicate(String ^tag) {
	this->tag = tag;
}

bool NewArchiveFilePredicate::IsMatch(NewArchiveFile^ file) {
	return !String::Compare(file->tag, this->tag);
}

NewArchiveViewContainer::NewArchiveViewContainer() {
	//initialize at size 5 even though no elements yet
	this->files = gcnew List<NewArchiveFile^>(5);
	//this->folders = gcnew FolderStructure();
	this->rootfolder = gcnew FolderElement(nullptr, "", "");
}

void NewArchiveViewContainer::AddFile(NewArchiveFile^ newfile) {
	//first check if file being added exists by tag
	NewArchiveFilePredicate p(newfile->tag);
	NewArchiveFile^ match = this->files->Find(gcnew Predicate<NewArchiveFile^>(p, &NewArchiveFilePredicate::IsMatch));
	//if file was found by tag, check folder path and remove old listing
	if ((match != nullptr) && (match->folderpath == newfile->folderpath)){
		this->files->Remove(match);
		this->numfiles--;
	}
	this->files->Add(newfile);
	this->numfiles++;
	this->rootfolder->Update(this, newfile);
}

int NewArchiveViewContainer::RemoveFile(String^ tag) {
	NewArchiveFilePredicate p(tag);
	NewArchiveFile^ match = this->files->Find(gcnew Predicate<NewArchiveFile^>(p, &NewArchiveFilePredicate::IsMatch));
	//if file was found by tag, remove it
	if (match) {
		this->files->Remove(match);
		this->numfiles--;
		return 1;
	}

	return 0;
}

void NewArchiveViewContainer::RenameFile(String^ tag, String^ newname) {
	NewArchiveFilePredicate p(tag);
	NewArchiveFile^ match = this->files->Find(gcnew Predicate<NewArchiveFile^>(p, &NewArchiveFilePredicate::IsMatch));
	//if file was found by tag, remove it
	if (match) {
		match->filename = newname;
		this->numfiles--;
	}
}

void NewArchiveViewContainer::RenameFolder(String^ path) {

}

FolderElement^ NewArchiveViewContainer::FindFolderByPath(String^ path) {
	return this->_FindFolderByPath(path, this->rootfolder, nullptr);
}

FolderElement^ NewArchiveViewContainer::_FindFolderByPath(String^ path, FolderElement^ currentfolder, FolderElement^ currentmatch) {
	/*Takes a string argument and recursively traverses
	the	folder element tree until it finds the corresponding
	element	and returns it*/
	if (!String::Compare(currentfolder->folderpath, path)) {
		return currentfolder;
	}
	for each(FolderElement^ subfolder in currentfolder->subfolders) {
		FolderElement^ match = this->_FindFolderByPath(path, subfolder, currentmatch);
		if (match) {
			return match;
			break;
		}
	}
}

void NewArchiveViewContainer::AddNewFolder(String^ newfoldername) {
	FolderElement^ match = this->FindFolderByPath(this->current_path);
	if (match) {
		match->AddSubfolder(newfoldername);
	}
}

int NewArchiveViewContainer::RemoveFolder(String^ path) {
	//first remove the folder instance from the tree
	FolderElement^ match = this->FindFolderByPath(path);
	if (match) {
		match->root->subfolders->Remove(match);
		return 1;
	}
	//then find all files that start with the path
	for each(NewArchiveFile^ file in this->files) {
		if (file->folderpath->StartsWith(path)) {
			this->files->Remove(file);
		}
	}
	return 0;
}

void FolderElement::Update(NewArchiveViewContainer^ archViewInfo, NewArchiveFile^ newfile) {
	String^ folderpath;
	String^ delim;
	cli::array<String^>^ tokens;

	folderpath = newfile->folderpath;
	delim = "\\";
	tokens = folderpath->Split(delim->ToCharArray());

	//loop all tokens
	FolderElement^ currentfolder = archViewInfo->rootfolder;
	String^ currentpath = "";
	for each (String^ token in tokens) {
		if (String::Compare(token, "")) {
			//if token is not empty string
			FolderElementPredicate p(token);
			FolderElement^ match = currentfolder->subfolders->Find(gcnew Predicate<FolderElement^>(p, &FolderElementPredicate::NameMatch));
			if (!match) {
				currentpath += "\\" + token ;
				FolderElement^ newfolder = gcnew FolderElement(currentfolder, token, currentpath);
				currentfolder->subfolders->Add(newfolder);
				currentfolder = newfolder;
			}
			else {
				currentfolder = match;
				currentpath += "\\" + match->foldername;
			}
		}
	}
}

void FolderElement::AddSubfolder(String^ newfoldername) {
	FolderElementPredicate p(newfoldername);
	FolderElement^ match = this->subfolders->Find(gcnew Predicate<FolderElement^>(p, &FolderElementPredicate::NameMatch));
	String^ newname;
	String^ newpath;
	if (!match) {
		newname = newfoldername;
		newpath = this->folderpath + "\\" + newname;
	}
	else {
		newname = "Copy of " + newfoldername;
		newpath = this->folderpath + "\\" + newname;
	}
	this->subfolders->Add(gcnew FolderElement(nullptr, newname, newpath));
}

FolderElement::FolderElement(FolderElement^ root, String^ foldername, String^ folderpath) {
	this->root = root;
	this->foldername = foldername;
	this->folderpath = folderpath;
}

FolderElementPredicate::FolderElementPredicate(String^ foldername) {
	this->foldername = foldername;
}

bool FolderElementPredicate::NameMatch(FolderElement^ file) {
	return !String::Compare(file->foldername, this->foldername);
}