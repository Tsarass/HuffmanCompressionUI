#pragma comment(linker, "/SUBSYSTEM:windows")

#include "MainForm.h"

using namespace System;
using namespace System::Windows::Forms;


[STAThread]
void Main(array<String^>^ args)
{
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);

	FormsApp::MainForm form;
	Application::Run(%form);

	if (args->Length) {
		if (args[0]->ToString() == "-open") {
		}

	}
}
