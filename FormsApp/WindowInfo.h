#pragma once

#ifndef WINDOWINFO_H
#define WINDOWINFO_H

using namespace System;
using namespace System::Collections::Generic;

/*Contains the info needed to send to the Compress function
in order to create the archive file.*/
public ref class FileInfoContainer {
public:
	int numfiles = 0;

	//ascii strings
	cli::array<System::String^>^ filepaths;
	cli::array<System::String^>^ filenames;
	System::String^ outfile;

	//unicode strings
	cli::array<System::String^>^ filepaths_w;
	cli::array<System::String^>^ filenames_w;
	System::String^ outfile_w;

	FileInfoContainer(cli::array<System::String^>^ filepaths, cli::array<System::String^>^ filenames, System::String^ outfile);
};


/*Contains the info required immediately after opening an
existing archive, which are inscribed in the archive header.*/
public ref class OpenArchiveContainer {
public:
	String^ archivepath;
	cli::array<System::String^>^ filenames;
	cli::array<System::String^>^ folderpaths;
	cli::array<Int32>^ compsizes;
	cli::array<Int32>^ uncompsizes;
	int numfiles;
	bool validarch = false;
	int endHeaderPos = 0;		//position in file where header ends

	OpenArchiveContainer() {};
	OpenArchiveContainer(System::String^ archivepath, cli::array<System::String^>^ filenames,
							cli::array<int>^ compsizes, cli::array<int>^ uncompsizes, int endHeaderPos);
};


/*Contains the info required to pass to the Decompress function
in order to extract all files from the archive.*/
public ref class ExtractArchiveContainer {
public:
	String^ archivepath;
	String^ extractdir;

	ExtractArchiveContainer(String^ archivepath, String^ extractdir);
};


/*Contains the info required for each file in the
new archive view.*/
public ref class NewArchiveFile {
public:
	String^ filename;
	String^ folderpath;
	String^ fullpath;
	String^ extension;
	String^ modified;
	property long long size;
	String^ tag;
	
	NewArchiveFile(String^ filename, String^ folderpath, String^ fullpath, String^ extension, String^ mod, Int32 size);
};


/*Predicate used to find matches of NewArchiveFile instances.*/
value class NewArchiveFilePredicate {
	String^ tag;
public:
	NewArchiveFilePredicate(String ^tag);
	bool IsMatch(NewArchiveFile^ file);
};

ref class FolderElement;

/*Contains the info needed to view the files and folders
associated with creating a new archive.*/
public ref class NewArchiveViewContainer {
	FolderElement^ _FindFolderByPath(String^ path, FolderElement^ currentfolder, FolderElement^ currentmatch);
public:
	Int32 numfiles = 0;
	List<NewArchiveFile^>^ files;
	FolderElement^ rootfolder;
	Int32 current_depth = 0;	//current folder depth in view
	String^ current_path = "";	//current folder path in archive
	String^ archpath = "";
	bool labeledit = false;

	NewArchiveViewContainer();
	void AddFile(NewArchiveFile^ newfile);
	int RemoveFile(String^ tag);
	void RenameFile(String^ tag, String^ newname);
	void AddNewFolder(String^ newfoldername);
	int RemoveFolder(String^ path);
	void RenameFolder(String^ path);
	FolderElement^ FindFolderByPath(String^ path);
};


/*Contains folder structure with subfolders and files.*/
public ref class FolderElement {
public:
	FolderElement^ root = nullptr;
	List<FolderElement^>^ subfolders = gcnew List<FolderElement^>;
	String^ foldername = "";
	String^ folderpath = "";

	FolderElement() {};
	FolderElement(FolderElement^ root, String^ foldername, String^ folderpath);
	void Update(NewArchiveViewContainer^ archViewInfo, NewArchiveFile^ newfile);
	void AddSubfolder(String^ newfoldername);

};

/*Predicate used to find matches of FolderElement instances.*/
value class FolderElementPredicate {
	String^ foldername;
public:
	FolderElementPredicate(String^ foldername);
	bool NameMatch(FolderElement^ folder);
};
#endif