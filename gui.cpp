#include "gui.h"

using namespace System;
using namespace System::Windows::Forms;

[STAThreadAttribute]
int main(array<String^>^ args) {
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);
	Sploity::gui form;
	Application::Run(%form);

	form.console->Text = form.console->Text + "CONSOLE: Looking for Assault Cube...";
	do {
		break;
	} while (true);

	return 0;
}