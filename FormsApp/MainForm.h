#pragma once

#include "HuffHelperClasses.h"
#include "WindowInfo.h"
#include "ArchiveIO.h"
#include <msclr\marshal_cppstd.h>

namespace FormsApp {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for MainForm
	/// </summary>
	public ref class MainForm : public System::Windows::Forms::Form
	{
	public:
		MainForm(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~MainForm()
		{
			if (components)
			{
				delete components;
			}
		}

	cli::array<String^>^ argfiles;
	String^ argarch;

	OpenArchiveContainer^ archInfo;
	NewArchiveViewContainer^ newArchInfo = gcnew NewArchiveViewContainer();
	System::Windows::Forms::ListViewItem^ files;		//list of files for compression
	private: System::Windows::Forms::OpenFileDialog^  addFilesDlg;
	private: System::Windows::Forms::SaveFileDialog^  saveFileDialog1;

	private: System::Windows::Forms::StatusStrip^  statusStrip1;

	private: System::Windows::Forms::ToolStripStatusLabel^  status;
	private: System::Windows::Forms::ToolStripProgressBar^  progbar;
	private: System::ComponentModel::BackgroundWorker^  compworker;

	private: System::Windows::Forms::ImageList^  imageList1;
	private: System::Windows::Forms::ContextMenuStrip^  filemenu;
	private: System::Windows::Forms::ToolStripMenuItem^  removeSelectionMenu;

	private: System::Windows::Forms::ToolStripSeparator^  toolStripSeparator1;


	private: System::Windows::Forms::ToolStrip^  toolbar;
	private: System::Windows::Forms::ToolStripButton^  compToolBtn;

	private: System::Windows::Forms::ToolStripButton^  addfilesToolBtn;
	private: System::Windows::Forms::ListView^  fileList;
	private: System::Windows::Forms::ColumnHeader^  filenamecol;
	private: System::Windows::Forms::ColumnHeader^  szcol;

	private: System::Windows::Forms::ColumnHeader^  path;
	private: System::Windows::Forms::ColumnHeader^  modified;
	private: System::Windows::Forms::ToolStripSeparator^  toolStripSeparator2;
	private: System::Windows::Forms::ToolStripButton^  openarchToolBtn;
	private: System::Windows::Forms::ToolStripButton^  extractToolBtn;
	private: System::Windows::Forms::OpenFileDialog^  openArchDlg;
	private: System::Windows::Forms::FolderBrowserDialog^  extractDlg;
	private: System::Windows::Forms::ToolStripSeparator^  toolStripSeparator3;
	private: System::Windows::Forms::ToolStripComboBox^  viewModeBox;
	private: System::Windows::Forms::ListView^  archList;
	private: System::Windows::Forms::ColumnHeader^  columnHeader1;
	private: System::Windows::Forms::ColumnHeader^  columnHeader2;
	private: System::Windows::Forms::ColumnHeader^  columnHeader3;
	private: System::ComponentModel::BackgroundWorker^  decompworker;

	private: System::Windows::Forms::ToolStrip^  toolStrip1;
	private: System::Windows::Forms::ToolStripButton^  backBtn;

	private: System::Windows::Forms::ToolStripTextBox^  pathTxtBox;
	private: System::Windows::Forms::ToolStripSeparator^  toolStripSeparator4;
	private: System::Windows::Forms::ToolStripMenuItem^  newFolderMenu;
	private: System::Windows::Forms::ToolStripTextBox^  newFolderTextBox;
	private: System::Windows::Forms::ToolStripMenuItem^  renameItemMenu;
	private: System::Windows::Forms::ToolStripButton^  newFolderBtn;




	private: System::ComponentModel::IContainer^  components;

	protected:

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>


#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(MainForm::typeid));
			this->addFilesDlg = (gcnew System::Windows::Forms::OpenFileDialog());
			this->saveFileDialog1 = (gcnew System::Windows::Forms::SaveFileDialog());
			this->imageList1 = (gcnew System::Windows::Forms::ImageList(this->components));
			this->statusStrip1 = (gcnew System::Windows::Forms::StatusStrip());
			this->progbar = (gcnew System::Windows::Forms::ToolStripProgressBar());
			this->status = (gcnew System::Windows::Forms::ToolStripStatusLabel());
			this->compworker = (gcnew System::ComponentModel::BackgroundWorker());
			this->filemenu = (gcnew System::Windows::Forms::ContextMenuStrip(this->components));
			this->removeSelectionMenu = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->renameItemMenu = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->toolStripSeparator1 = (gcnew System::Windows::Forms::ToolStripSeparator());
			this->newFolderMenu = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->newFolderTextBox = (gcnew System::Windows::Forms::ToolStripTextBox());
			this->toolStripSeparator4 = (gcnew System::Windows::Forms::ToolStripSeparator());
			this->toolbar = (gcnew System::Windows::Forms::ToolStrip());
			this->addfilesToolBtn = (gcnew System::Windows::Forms::ToolStripButton());
			this->compToolBtn = (gcnew System::Windows::Forms::ToolStripButton());
			this->toolStripSeparator2 = (gcnew System::Windows::Forms::ToolStripSeparator());
			this->openarchToolBtn = (gcnew System::Windows::Forms::ToolStripButton());
			this->extractToolBtn = (gcnew System::Windows::Forms::ToolStripButton());
			this->toolStripSeparator3 = (gcnew System::Windows::Forms::ToolStripSeparator());
			this->viewModeBox = (gcnew System::Windows::Forms::ToolStripComboBox());
			this->fileList = (gcnew System::Windows::Forms::ListView());
			this->filenamecol = (gcnew System::Windows::Forms::ColumnHeader());
			this->szcol = (gcnew System::Windows::Forms::ColumnHeader());
			this->modified = (gcnew System::Windows::Forms::ColumnHeader());
			this->path = (gcnew System::Windows::Forms::ColumnHeader());
			this->openArchDlg = (gcnew System::Windows::Forms::OpenFileDialog());
			this->extractDlg = (gcnew System::Windows::Forms::FolderBrowserDialog());
			this->archList = (gcnew System::Windows::Forms::ListView());
			this->columnHeader1 = (gcnew System::Windows::Forms::ColumnHeader());
			this->columnHeader2 = (gcnew System::Windows::Forms::ColumnHeader());
			this->columnHeader3 = (gcnew System::Windows::Forms::ColumnHeader());
			this->decompworker = (gcnew System::ComponentModel::BackgroundWorker());
			this->toolStrip1 = (gcnew System::Windows::Forms::ToolStrip());
			this->backBtn = (gcnew System::Windows::Forms::ToolStripButton());
			this->pathTxtBox = (gcnew System::Windows::Forms::ToolStripTextBox());
			this->newFolderBtn = (gcnew System::Windows::Forms::ToolStripButton());
			this->statusStrip1->SuspendLayout();
			this->filemenu->SuspendLayout();
			this->toolbar->SuspendLayout();
			this->toolStrip1->SuspendLayout();
			this->SuspendLayout();
			// 
			// addFilesDlg
			// 
			this->addFilesDlg->AddExtension = false;
			this->addFilesDlg->DereferenceLinks = false;
			this->addFilesDlg->RestoreDirectory = true;
			// 
			// saveFileDialog1
			// 
			this->saveFileDialog1->DefaultExt = L"tcc";
			// 
			// imageList1
			// 
			this->imageList1->ImageStream = (cli::safe_cast<System::Windows::Forms::ImageListStreamer^>(resources->GetObject(L"imageList1.ImageStream")));
			this->imageList1->TransparentColor = System::Drawing::Color::Transparent;
			this->imageList1->Images->SetKeyName(0, L"folder.png");
			// 
			// statusStrip1
			// 
			this->statusStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) { this->progbar, this->status });
			this->statusStrip1->Location = System::Drawing::Point(0, 555);
			this->statusStrip1->Name = L"statusStrip1";
			this->statusStrip1->Size = System::Drawing::Size(538, 22);
			this->statusStrip1->SizingGrip = false;
			this->statusStrip1->TabIndex = 2;
			this->statusStrip1->Text = L"statusStrip1";
			// 
			// progbar
			// 
			this->progbar->Name = L"progbar";
			this->progbar->Padding = System::Windows::Forms::Padding(10, 0, 0, 0);
			this->progbar->Size = System::Drawing::Size(230, 16);
			this->progbar->Style = System::Windows::Forms::ProgressBarStyle::Continuous;
			// 
			// status
			// 
			this->status->Name = L"status";
			this->status->Size = System::Drawing::Size(29, 17);
			this->status->Text = L"Idle.";
			this->status->TextAlign = System::Drawing::ContentAlignment::MiddleRight;
			// 
			// compworker
			// 
			this->compworker->DoWork += gcnew System::ComponentModel::DoWorkEventHandler(this, &MainForm::compworker_DoWork);
			this->compworker->RunWorkerCompleted += gcnew System::ComponentModel::RunWorkerCompletedEventHandler(this, &MainForm::compworker_RunWorkerCompleted);
			// 
			// filemenu
			// 
			this->filemenu->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(5) {
				this->removeSelectionMenu,
					this->renameItemMenu, this->toolStripSeparator1, this->newFolderMenu, this->toolStripSeparator4
			});
			this->filemenu->Name = L"filemenu";
			this->filemenu->Size = System::Drawing::Size(143, 82);
			// 
			// removeSelectionMenu
			// 
			this->removeSelectionMenu->Name = L"removeSelectionMenu";
			this->removeSelectionMenu->Size = System::Drawing::Size(142, 22);
			this->removeSelectionMenu->Text = L"Remove";
			this->removeSelectionMenu->Click += gcnew System::EventHandler(this, &MainForm::toolStripMenuItem1_Click);
			// 
			// renameItemMenu
			// 
			this->renameItemMenu->Name = L"renameItemMenu";
			this->renameItemMenu->Size = System::Drawing::Size(142, 22);
			this->renameItemMenu->Text = L"Rename";
			this->renameItemMenu->Click += gcnew System::EventHandler(this, &MainForm::renameItemMenu_Click);
			// 
			// toolStripSeparator1
			// 
			this->toolStripSeparator1->Name = L"toolStripSeparator1";
			this->toolStripSeparator1->Size = System::Drawing::Size(139, 6);
			// 
			// newFolderMenu
			// 
			this->newFolderMenu->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(1) { this->newFolderTextBox });
			this->newFolderMenu->Name = L"newFolderMenu";
			this->newFolderMenu->Size = System::Drawing::Size(142, 22);
			this->newFolderMenu->Text = L"Create folder";
			// 
			// newFolderTextBox
			// 
			this->newFolderTextBox->Name = L"newFolderTextBox";
			this->newFolderTextBox->Size = System::Drawing::Size(100, 23);
			this->newFolderTextBox->KeyUp += gcnew System::Windows::Forms::KeyEventHandler(this, &MainForm::newFolderTextBox_KeyUp);
			// 
			// toolStripSeparator4
			// 
			this->toolStripSeparator4->Name = L"toolStripSeparator4";
			this->toolStripSeparator4->Size = System::Drawing::Size(139, 6);
			// 
			// toolbar
			// 
			this->toolbar->AutoSize = false;
			this->toolbar->GripStyle = System::Windows::Forms::ToolStripGripStyle::Hidden;
			this->toolbar->ImageScalingSize = System::Drawing::Size(64, 64);
			this->toolbar->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(7) {
				this->addfilesToolBtn, this->compToolBtn,
					this->toolStripSeparator2, this->openarchToolBtn, this->extractToolBtn, this->toolStripSeparator3, this->viewModeBox
			});
			this->toolbar->Location = System::Drawing::Point(0, 0);
			this->toolbar->MaximumSize = System::Drawing::Size(0, 67);
			this->toolbar->Name = L"toolbar";
			this->toolbar->Size = System::Drawing::Size(538, 67);
			this->toolbar->TabIndex = 3;
			this->toolbar->Text = L"toolbar";
			// 
			// addfilesToolBtn
			// 
			this->addfilesToolBtn->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Image;
			this->addfilesToolBtn->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"addfilesToolBtn.Image")));
			this->addfilesToolBtn->ImageTransparentColor = System::Drawing::Color::Magenta;
			this->addfilesToolBtn->Name = L"addfilesToolBtn";
			this->addfilesToolBtn->Padding = System::Windows::Forms::Padding(20, 0, 0, 0);
			this->addfilesToolBtn->Size = System::Drawing::Size(88, 64);
			this->addfilesToolBtn->Text = L"toolStripButton2";
			this->addfilesToolBtn->ToolTipText = L"Add files for compression";
			this->addfilesToolBtn->Click += gcnew System::EventHandler(this, &MainForm::addfilesToolBtn_Click);
			// 
			// compToolBtn
			// 
			this->compToolBtn->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Image;
			this->compToolBtn->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"compToolBtn.Image")));
			this->compToolBtn->ImageTransparentColor = System::Drawing::Color::Magenta;
			this->compToolBtn->Name = L"compToolBtn";
			this->compToolBtn->Padding = System::Windows::Forms::Padding(20, 0, 0, 0);
			this->compToolBtn->Size = System::Drawing::Size(88, 64);
			this->compToolBtn->Text = L"compToolBtn";
			this->compToolBtn->ToolTipText = L"Compress to archive";
			this->compToolBtn->Click += gcnew System::EventHandler(this, &MainForm::compToolBtn_Click);
			// 
			// toolStripSeparator2
			// 
			this->toolStripSeparator2->Name = L"toolStripSeparator2";
			this->toolStripSeparator2->Size = System::Drawing::Size(6, 67);
			// 
			// openarchToolBtn
			// 
			this->openarchToolBtn->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Image;
			this->openarchToolBtn->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"openarchToolBtn.Image")));
			this->openarchToolBtn->ImageTransparentColor = System::Drawing::Color::Magenta;
			this->openarchToolBtn->Name = L"openarchToolBtn";
			this->openarchToolBtn->Padding = System::Windows::Forms::Padding(20, 0, 0, 0);
			this->openarchToolBtn->Size = System::Drawing::Size(88, 64);
			this->openarchToolBtn->Text = L"toolStripButton1";
			this->openarchToolBtn->ToolTipText = L"Open archive";
			this->openarchToolBtn->Click += gcnew System::EventHandler(this, &MainForm::openarchToolBtn_Click);
			// 
			// extractToolBtn
			// 
			this->extractToolBtn->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Image;
			this->extractToolBtn->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"extractToolBtn.Image")));
			this->extractToolBtn->ImageTransparentColor = System::Drawing::Color::Magenta;
			this->extractToolBtn->Name = L"extractToolBtn";
			this->extractToolBtn->Padding = System::Windows::Forms::Padding(20, 0, 0, 0);
			this->extractToolBtn->Size = System::Drawing::Size(88, 64);
			this->extractToolBtn->Text = L"toolStripButton2";
			this->extractToolBtn->ToolTipText = L"Extract archive to folder";
			this->extractToolBtn->Click += gcnew System::EventHandler(this, &MainForm::extractToolBtn_Click);
			// 
			// toolStripSeparator3
			// 
			this->toolStripSeparator3->Name = L"toolStripSeparator3";
			this->toolStripSeparator3->Size = System::Drawing::Size(6, 67);
			// 
			// viewModeBox
			// 
			this->viewModeBox->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
			this->viewModeBox->Items->AddRange(gcnew cli::array< System::Object^  >(2) { L"New archive", L"Open archive" });
			this->viewModeBox->Name = L"viewModeBox";
			this->viewModeBox->Size = System::Drawing::Size(121, 67);
			this->viewModeBox->SelectedIndexChanged += gcnew System::EventHandler(this, &MainForm::viewModeBox_SelectedIndexChanged);
			// 
			// fileList
			// 
			this->fileList->AllowDrop = true;
			this->fileList->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->fileList->Columns->AddRange(gcnew cli::array< System::Windows::Forms::ColumnHeader^  >(4) {
				this->filenamecol, this->szcol,
					this->modified, this->path
			});
			this->fileList->FullRowSelect = true;
			this->fileList->GridLines = true;
			this->fileList->LabelEdit = true;
			this->fileList->Location = System::Drawing::Point(12, 105);
			this->fileList->Name = L"fileList";
			this->fileList->Size = System::Drawing::Size(514, 447);
			this->fileList->SmallImageList = this->imageList1;
			this->fileList->TabIndex = 8;
			this->fileList->UseCompatibleStateImageBehavior = false;
			this->fileList->View = System::Windows::Forms::View::Details;
			this->fileList->AfterLabelEdit += gcnew System::Windows::Forms::LabelEditEventHandler(this, &MainForm::fileList_AfterLabelEdit);
			this->fileList->ColumnClick += gcnew System::Windows::Forms::ColumnClickEventHandler(this, &MainForm::fileList_ColumnClick);
			this->fileList->DragDrop += gcnew System::Windows::Forms::DragEventHandler(this, &MainForm::fileList_DragDrop);
			this->fileList->DragEnter += gcnew System::Windows::Forms::DragEventHandler(this, &MainForm::fileList_DragEnter);
			this->fileList->KeyUp += gcnew System::Windows::Forms::KeyEventHandler(this, &MainForm::fileList_KeyUp);
			this->fileList->MouseDoubleClick += gcnew System::Windows::Forms::MouseEventHandler(this, &MainForm::fileList_MouseDoubleClick);
			this->fileList->MouseUp += gcnew System::Windows::Forms::MouseEventHandler(this, &MainForm::fileList_MouseUp);
			// 
			// filenamecol
			// 
			this->filenamecol->Text = L"Filename";
			this->filenamecol->Width = 158;
			// 
			// szcol
			// 
			this->szcol->Text = L"Size (bytes)";
			this->szcol->Width = 85;
			// 
			// modified
			// 
			this->modified->Text = L"Modified";
			this->modified->Width = 102;
			// 
			// path
			// 
			this->path->Text = L"Path";
			this->path->Width = 127;
			// 
			// openArchDlg
			// 
			this->openArchDlg->DefaultExt = L"tcc";
			// 
			// archList
			// 
			this->archList->AllowDrop = true;
			this->archList->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->archList->Columns->AddRange(gcnew cli::array< System::Windows::Forms::ColumnHeader^  >(3) {
				this->columnHeader1, this->columnHeader2,
					this->columnHeader3
			});
			this->archList->FullRowSelect = true;
			this->archList->GridLines = true;
			this->archList->Location = System::Drawing::Point(12, 105);
			this->archList->Name = L"archList";
			this->archList->Size = System::Drawing::Size(514, 447);
			this->archList->SmallImageList = this->imageList1;
			this->archList->Sorting = System::Windows::Forms::SortOrder::Ascending;
			this->archList->TabIndex = 9;
			this->archList->UseCompatibleStateImageBehavior = false;
			this->archList->View = System::Windows::Forms::View::Details;
			// 
			// columnHeader1
			// 
			this->columnHeader1->Text = L"Filename";
			this->columnHeader1->Width = 158;
			// 
			// columnHeader2
			// 
			this->columnHeader2->Text = L"Size (bytes)";
			this->columnHeader2->Width = 85;
			// 
			// columnHeader3
			// 
			this->columnHeader3->Text = L"Packed (bytes)";
			this->columnHeader3->Width = 102;
			// 
			// decompworker
			// 
			this->decompworker->DoWork += gcnew System::ComponentModel::DoWorkEventHandler(this, &MainForm::decompworker_DoWork);
			this->decompworker->RunWorkerCompleted += gcnew System::ComponentModel::RunWorkerCompletedEventHandler(this, &MainForm::decompworker_RunWorkerCompleted);
			// 
			// toolStrip1
			// 
			this->toolStrip1->AutoSize = false;
			this->toolStrip1->GripStyle = System::Windows::Forms::ToolStripGripStyle::Hidden;
			this->toolStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(3) {
				this->backBtn, this->pathTxtBox,
					this->newFolderBtn
			});
			this->toolStrip1->Location = System::Drawing::Point(0, 67);
			this->toolStrip1->MaximumSize = System::Drawing::Size(0, 35);
			this->toolStrip1->Name = L"toolStrip1";
			this->toolStrip1->Size = System::Drawing::Size(538, 35);
			this->toolStrip1->TabIndex = 11;
			this->toolStrip1->Text = L"toolStrip1";
			// 
			// backBtn
			// 
			this->backBtn->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Image;
			this->backBtn->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"backBtn.Image")));
			this->backBtn->ImageTransparentColor = System::Drawing::Color::Magenta;
			this->backBtn->Name = L"backBtn";
			this->backBtn->Padding = System::Windows::Forms::Padding(20, 0, 0, 0);
			this->backBtn->Size = System::Drawing::Size(40, 32);
			this->backBtn->ToolTipText = L"Up to previous folder";
			this->backBtn->Click += gcnew System::EventHandler(this, &MainForm::toolStripButton1_Click);
			// 
			// pathTxtBox
			// 
			this->pathTxtBox->Enabled = false;
			this->pathTxtBox->Name = L"pathTxtBox";
			this->pathTxtBox->Size = System::Drawing::Size(430, 35);
			this->pathTxtBox->Text = L"<root>";
			this->pathTxtBox->ToolTipText = L"Current archive path in view";
			// 
			// newFolderBtn
			// 
			this->newFolderBtn->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Image;
			this->newFolderBtn->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"newFolderBtn.Image")));
			this->newFolderBtn->ImageTransparentColor = System::Drawing::Color::Magenta;
			this->newFolderBtn->Name = L"newFolderBtn";
			this->newFolderBtn->Padding = System::Windows::Forms::Padding(20, 0, 0, 0);
			this->newFolderBtn->Size = System::Drawing::Size(40, 32);
			this->newFolderBtn->Text = L"toolStripButton1";
			this->newFolderBtn->ToolTipText = L"Create folder";
			this->newFolderBtn->Click += gcnew System::EventHandler(this, &MainForm::newFolderBtn_Click);
			// 
			// MainForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(538, 577);
			this->Controls->Add(this->toolStrip1);
			this->Controls->Add(this->fileList);
			this->Controls->Add(this->toolbar);
			this->Controls->Add(this->statusStrip1);
			this->Controls->Add(this->archList);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedDialog;
			this->Icon = (cli::safe_cast<System::Drawing::Icon^>(resources->GetObject(L"$this.Icon")));
			this->MaximizeBox = false;
			this->Name = L"MainForm";
			this->Text = L"Huffman Compression Tool";
			this->Load += gcnew System::EventHandler(this, &MainForm::MainForm_Load);
			this->statusStrip1->ResumeLayout(false);
			this->statusStrip1->PerformLayout();
			this->filemenu->ResumeLayout(false);
			this->toolbar->ResumeLayout(false);
			this->toolbar->PerformLayout();
			this->toolStrip1->ResumeLayout(false);
			this->toolStrip1->PerformLayout();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void compworker_DoWork(System::Object^  sender, System::ComponentModel::DoWorkEventArgs^  e) {
		// Get the BackgroundWorker that raised this event.
		BackgroundWorker^ worker = dynamic_cast<BackgroundWorker^>(sender);

		auto arg = safe_cast<NewArchiveViewContainer^>(e->Argument);

		//pass the result of compress function to the caller
		e->Result = Compress(arg, worker, e);
	}
	private: System::Void compworker_ProgressChanged(System::Object^  sender, System::ComponentModel::ProgressChangedEventArgs^  e) {
		this->progbar->Value = e->ProgressPercentage;
	}
	private: System::Void compworker_RunWorkerCompleted(System::Object^  sender, System::ComponentModel::RunWorkerCompletedEventArgs^  e) {
		// First, handle the case where an exception was thrown.
		if (e->Error != nullptr)
		{
			MessageBox::Show(e->Error->Message);
		}
		else
			if (e->Cancelled)
			{
				// Next, handle the case where the user cancelled 
				// the operation.
				this->status->Text = "Compression cancelled.";
			}
			else
			{
				// Finally, handle the case where the operation 
				// succeeded.
				if (e->Result){
					this->status->Text = "Compression complete.";
				}
				else {
					this->status->Text = "Compression failed.";
				}
			}

		// Enable the Compress control.
		this->compToolBtn->Enabled = true;
		this->addfilesToolBtn->Enabled = true;
		this->viewModeBox->Enabled = true;
		this->progbar->Style = System::Windows::Forms::ProgressBarStyle::Blocks;
	}
	private: System::Void decompworker_DoWork(System::Object^  sender, System::ComponentModel::DoWorkEventArgs^  e) {
		// Get the BackgroundWorker that raised this event.
		BackgroundWorker^ worker = dynamic_cast<BackgroundWorker^>(sender);

		auto arg = safe_cast<ExtractArchiveContainer^>(e->Argument);

		//pass the result of compress function to the caller
		e->Result = Decompress(arg, worker, e);
	}
	private: System::Void decompworker_RunWorkerCompleted(System::Object^  sender, System::ComponentModel::RunWorkerCompletedEventArgs^  e) {
		// First, handle the case where an exception was thrown.
		if (e->Error != nullptr)
		{
			MessageBox::Show(e->Error->Message);
		}
		else
			if (e->Cancelled)
			{
				// Next, handle the case where the user cancelled 
				// the operation.
				this->status->Text = "Decompression cancelled.";
			}
			else
			{
				// Finally, handle the case where the operation 
				// succeeded.
				if (e->Result) {
					this->status->Text = "Decompression complete.";
				}
				else {
					this->status->Text = "Decompression failed.";
				}
			}

		// Enable the Compress control.
		this->openarchToolBtn->Enabled = true;
		this->extractToolBtn->Enabled = true;
		this->viewModeBox->Enabled = true;
		this->progbar->Style = System::Windows::Forms::ProgressBarStyle::Blocks;
	}
	private: System::Void fileList_DragDrop(System::Object^  sender, System::Windows::Forms::DragEventArgs^  e) {
		Object^ droppedfiles;
		droppedfiles = e->Data->GetData(DataFormats::FileDrop, false);
		auto files_ = safe_cast<cli::array<String^>^>(droppedfiles);

		AddFilesEx(files_, newArchInfo->current_path);
	}
	private: System::Void fileList_DragEnter(System::Object^  sender, System::Windows::Forms::DragEventArgs^  e) {
		if (e->Data->GetDataPresent(DataFormats::FileDrop)) e->Effect = DragDropEffects::Copy;
	}
	private: System::Void toolStripMenuItem1_Click(System::Object^  sender, System::EventArgs^  e) {
		RemoveSelectedListItems();
	}
	private: System::Void fileList_MouseUp(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
		if (e->Button == System::Windows::Forms::MouseButtons::Right)
		{
			Point p(e->X, e->Y);

			filemenu->Show(fileList, p);
			if (fileList->SelectedItems->Count) {
				removeSelectionMenu->Enabled = true;
				renameItemMenu->Enabled = true;
			}
			else {
				removeSelectionMenu->Enabled = false;
				renameItemMenu->Enabled = false;
			}
		}
	}
	private: System::Void fileList_KeyUp(System::Object^  sender, System::Windows::Forms::KeyEventArgs^  e) {
		if (e->KeyCode == Keys::Delete) {
			RemoveSelectedListItems();
		}
		else if (e->KeyCode == Keys::Enter) {
			//check if label is being edited
			if (newArchInfo->labeledit) {
				return;
			}
			//if only 1 item is selected, check if folder and enter
			if (fileList->SelectedItems->Count == 1) {
				if (fileList->SelectedItems[0]->Tag == "<folder>") {
					newArchInfo->current_path += "\\" + fileList->SelectedItems[0]->Text;
					UpdateNewArchView();
				}
			}
		}
		else if (e->KeyCode == Keys::Back) {
			if (JumpToPreviousFolder()) {
				UpdateNewArchView();
			}
		}
		else if (e->KeyCode == Keys::F2) {
			fileList->SelectedItems[0]->BeginEdit();\
			newArchInfo->labeledit = true;
		}
	}

	int JumpToPreviousFolder() {
		if (newArchInfo->current_path != "") {
			newArchInfo->current_path = newArchInfo->current_path->Remove(newArchInfo->current_path->LastIndexOf("\\"));
			return 1;
		}
		return 0;
	}

	void RemoveSelectedListItems() {	
		int selcount = fileList->SelectedIndices->Count;
		while (selcount > 0) {
			String^ tag = fileList->Items[fileList->SelectedIndices[0]]->Tag->ToString();
			if (tag == "<folder>") {
				String ^ path = newArchInfo->current_path + "\\" + fileList->Items[fileList->SelectedIndices[0]]->Text;
				if (newArchInfo->RemoveFolder(path)) { selcount--; }
			}
			else {
				if (newArchInfo->RemoveFile(tag)) { selcount--; }
			}
		}
		UpdateNewArchView();
	}

	void AddFilesEx(cli::array<String^>^ fullpaths, String^ pathinarch) {

		int filesadded = 0;
		for (int i = 0; i < fullpaths->Length; i++) {

			System::String^ fullpath(fullpaths[i]->ToString());
			String^ filename;
			String^ delim = "\\";
			cli::array<Char>^ delimiter = delim->ToCharArray();
			cli::array<String^>^ words;
			words = fullpath->Split(delimiter);
			filename = words[words->Length - 1];
			//check if it is a file
			System::IO::FileInfo^ fi = gcnew System::IO::FileInfo(fullpath);
			String^ currpath = pathinarch;
			if (!fi->Exists) {
				//if not, check if it is a directory
				System::IO::DirectoryInfo^ dir = gcnew System::IO::DirectoryInfo(fullpath);
				if (dir->Exists) {
					cli::array<String^>^ folderitems = System::IO::Directory::GetDirectories(fullpath);
					pathinarch += "\\" + dir->Name;
					if (folderitems->Length) {
						AddFilesEx(folderitems, pathinarch);		//recursion
					}
					
					cli::array<String^>^ fileitems = System::IO::Directory::GetFiles(fullpath);
					if (fileitems->Length) {
						AddFilesEx(fileitems, pathinarch);			//recursion
						pathinarch = currpath;
					}
				}
				continue;
			}
			// Set a default icon for the file.
			System::Drawing::Icon^ iconForFile = System::Drawing::SystemIcons::WinLogo;

			//check if there is an image key for the current extension
			//if it is .exe keep the full filename
			String^ newkey = fi->Extension;
			if (newkey == ".exe") {
				newkey = fi->Name;
			}
			else {
				newkey = fi->Extension;
			}
			if (!this->imageList1->Images->ContainsKey(newkey))
			{
				// If not, add the image to the image list.
#define ExtractAssociatedIcon ExtractAssociatedIcon
				iconForFile = System::Drawing::Icon::ExtractAssociatedIcon(fi->FullName);
				imageList1->Images->Add(newkey, iconForFile);
			}
			filesadded++;
			//New archive view
			NewArchiveFile^ newfile = gcnew NewArchiveFile{ filename, pathinarch, fullpath, newkey, fi->LastWriteTime.ToString(), fi->Length };
			newArchInfo->AddFile(newfile);
		}
		if (filesadded) {
			this->status->Text = filesadded + " files added for compression.";
			UpdateNewArchView();
		}

	}

	void UpdateNewArchView() {
		fileList->Items->Clear();
		System::Windows::Forms::ListViewItem^ folders;		//list of folders in current view
		if (newArchInfo->current_path != "") {
			pathTxtBox->Text = newArchInfo->current_path;
		}
		else {
			pathTxtBox->Text = "<root>";
		}
		
		FolderElement^ currentfolder = newArchInfo->FindFolderByPath(newArchInfo->current_path);
		if (currentfolder) {
			//proceed only if folder exists
			for each(FolderElement^ folder in currentfolder->subfolders) {
				folders = gcnew System::Windows::Forms::ListViewItem(folder->foldername);
				folders->ImageKey = "folder.png";
				folders->Tag = "<folder>";
				fileList->Items->Add(folders);
			}
		}
		for each(NewArchiveFile^ file in newArchInfo->files) {
			if (!String::Compare(file->folderpath, newArchInfo->current_path)) {
				files = gcnew System::Windows::Forms::ListViewItem(file->filename);
				files->SubItems->Add(file->size.ToString());
				files->SubItems->Add(file->modified);
				files->SubItems->Add(file->fullpath);
				files->ImageKey = file->extension;
				files->Tag = file->tag;
				fileList->Items->Add(files);
			}
		}
	}

private: System::Void addfilesToolBtn_Click(System::Object^  sender, System::EventArgs^  e) {
	addFilesDlg->Filter = "All files|*.*";
	addFilesDlg->Title = "Select files for compression";
	if (addFilesDlg->ShowDialog() == System::Windows::Forms::DialogResult::OK) {
		auto files_ = safe_cast<cli::array<String^>^>(addFilesDlg->FileNames);

		AddFilesEx(files_, newArchInfo->current_path);
	}
}
private: System::Void compToolBtn_Click(System::Object^  sender, System::EventArgs^  e) {
	if (fileList->Items->Count <= 0) {
		this->status->Text = "No files selected for compression.";
		return;
	}
	saveFileDialog1->Filter = "Archive files|*.tcc";
	saveFileDialog1->Title = "Choose a name for the compressed file";
	if (saveFileDialog1->ShowDialog() == System::Windows::Forms::DialogResult::OK) {
		this->progbar->Style = System::Windows::Forms::ProgressBarStyle::Marquee;
		this->progbar->MarqueeAnimationSpeed = 25;
		this->status->Text = "Compressing...";
		this->compToolBtn->Enabled = false;
		this->addfilesToolBtn->Enabled = false;
		this->viewModeBox->Enabled = false;

		newArchInfo->archpath = saveFileDialog1->FileName;

		compworker->RunWorkerAsync(newArchInfo);
		//compworker->ProgressChanged += gcnew ProgressChangedEventHandler(this, &MainForm::compworker_ProgressChanged);
	}
}
private: System::Void fileList_ColumnClick(System::Object^  sender, System::Windows::Forms::ColumnClickEventArgs^  e) {
	fileList->Sort();
}
private: System::Void openarchToolBtn_Click(System::Object^  sender, System::EventArgs^  e) {
	openArchDlg->Filter = "TCC Archives |*.tcc|All files|*.*";
	openArchDlg->Title = "Select archive to open";
	if (openArchDlg->ShowDialog() == System::Windows::Forms::DialogResult::OK) {
		//first clear the file list
		archList->Items->Clear();

		auto archpath = safe_cast<String^>(openArchDlg->FileName);

		archInfo = ReadArchiveHeader(archpath);
		if (archInfo->validarch) {
			//add file info to file list
			for (int fileid = 0; fileid < archInfo->numfiles; fileid++) {
				files = gcnew System::Windows::Forms::ListViewItem(archInfo->filenames[fileid]);
				files->SubItems->Add(archInfo->uncompsizes[fileid].ToString());
				files->SubItems->Add(archInfo->compsizes[fileid].ToString());
				archList->Items->Add(files);
			}
			this->status->Text = "Archive opened successfully (" + archInfo->numfiles + " files found).";
		}
		else {
			this->status->Text = "Invalid/corrupt archive or unable to read from source file.";
		}
	}
}
private: System::Void extractToolBtn_Click(System::Object^  sender, System::EventArgs^  e) {
	extractDlg->Description = "Select a folder to extract to:";
	if (extractDlg->ShowDialog() == System::Windows::Forms::DialogResult::OK) {
		auto destfolder = safe_cast<String^>(extractDlg->SelectedPath);

		this->progbar->Style = System::Windows::Forms::ProgressBarStyle::Marquee;
		this->progbar->MarqueeAnimationSpeed = 25;
		this->status->Text = "Decompressing...";
		this->openarchToolBtn->Enabled = false;
		this->extractToolBtn->Enabled = false;
		this->viewModeBox->Enabled = false;

		ExtractArchiveContainer^ newarch = gcnew ExtractArchiveContainer{ archInfo->archivepath, destfolder };

		//initialize background worker
		decompworker->RunWorkerAsync(newarch);
	}
}
private: System::Void viewModeBox_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e) {
	ChangeMode(viewModeBox->SelectedIndex);
}
	void ChangeMode(int mode) {
		//enables and disables controls according to desired mode
		if (mode == 0) {
			this->addfilesToolBtn->Enabled = true;
			this->compToolBtn->Enabled = true;
			this->fileList->Visible = true;

			this->openarchToolBtn->Enabled = false;
			this->extractToolBtn->Enabled = false;
			this->archList->Visible = false;
		}
		else if (mode == 1) {
			this->addfilesToolBtn->Enabled = false;
			this->compToolBtn->Enabled = false;
			this->fileList->Visible = false;

			this->openarchToolBtn->Enabled = true;
			this->extractToolBtn->Enabled = true;
			this->archList->Visible = true;
		}
	}
private: System::Void MainForm_Load(System::Object^  sender, System::EventArgs^  e) {
	this->viewModeBox->SelectedIndex = 0;
}
private: System::Void toolStripButton1_Click(System::Object^  sender, System::EventArgs^  e) {
	if (JumpToPreviousFolder()) {
		UpdateNewArchView();
	}
}
private: System::Void renameItemMenu_Click(System::Object^  sender, System::EventArgs^  e) {
	fileList->SelectedItems[0]->BeginEdit();
	newArchInfo->labeledit = true;
}
private: System::Void fileList_AfterLabelEdit(System::Object^  sender, System::Windows::Forms::LabelEditEventArgs^  e) {
	if (e->Label == nullptr) {
		return;
	}
	//check for illegal characters
	String^ illegal = "<>:/\\|?*";
	int pos = e->Label->IndexOfAny(illegal->ToCharArray());
	if (e->Label->IndexOfAny(illegal->ToCharArray()) >= 0) {
		e->CancelEdit = true;
		return;
	}

	newArchInfo->labeledit = false;

	String^ tag = fileList->Items[e->Item]->Tag->ToString();
	if (tag == "<folder>") {
		//change folder name in tree
		//newArchInfo->RenameFolder()
	}
	else {
		//change the actual file name in data structure
		newArchInfo->RenameFile(fileList->Items[e->Item]->Tag->ToString(), e->Label);
	}	
}
private: System::Void newFolderTextBox_KeyUp(System::Object^  sender, System::Windows::Forms::KeyEventArgs^  e) {
	if (e->KeyCode == Keys::Enter) {
		if (newFolderTextBox->Text != "") {
			newArchInfo->AddNewFolder(newFolderTextBox->Text);
		}
		else {
			newArchInfo->AddNewFolder("New folder");
		}
		newFolderTextBox->Text = "";
		filemenu->Close();
		UpdateNewArchView();
	}
}
private: System::Void fileList_MouseDoubleClick(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
	System::Windows::Forms::ListViewHitTestInfo^ clicked = fileList->HitTest(e->X, e->Y);
	if (clicked->Item->Tag == "<folder>") {
		newArchInfo->current_path += "\\" + clicked->Item->Text;
		UpdateNewArchView();
	}
	
}
private: System::Void newFolderBtn_Click(System::Object^  sender, System::EventArgs^  e) {
	newArchInfo->AddNewFolder("New folder");
	UpdateNewArchView();
}
};

};