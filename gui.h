#pragma once

#include <Windows.h>
#include <vector>
#include "proc.h"
#include "addys.h"
#include <thread>

namespace Sploity {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	public ref class gui : public System::Windows::Forms::Form
	{

		public:
		gui()
		{
			InitializeComponent();
			console->Text = console->Text + "[CONSOLE]: Loading GUI...";
		}

	protected: ~gui()
		{
			if (components)
			{
				delete components;
			}
		}

	private: System::Windows::Forms::Panel^ backPanel;
	public: System::Windows::Forms::RichTextBox^ console;
	private: System::Windows::Forms::TextBox^ input;
	private: System::Windows::Forms::Label^ lblInput;
	private: System::ComponentModel::Container ^components;

	private: HANDLE hGame = 0;
	private: uintptr_t modBase;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent()
		{
			this->backPanel = (gcnew System::Windows::Forms::Panel());
			this->lblInput = (gcnew System::Windows::Forms::Label());
			this->console = (gcnew System::Windows::Forms::RichTextBox());
			this->input = (gcnew System::Windows::Forms::TextBox());
			this->backPanel->SuspendLayout();
			this->SuspendLayout();
			// 
			// backPanel
			// 
			this->backPanel->Controls->Add(this->lblInput);
			this->backPanel->Controls->Add(this->console);
			this->backPanel->Controls->Add(this->input);
			this->backPanel->Dock = System::Windows::Forms::DockStyle::Fill;
			this->backPanel->Location = System::Drawing::Point(0, 0);
			this->backPanel->Name = L"backPanel";
			this->backPanel->Size = System::Drawing::Size(510, 333);
			this->backPanel->TabIndex = 0;
			// 
			// lblInput
			// 
			this->lblInput->AutoSize = true;
			this->lblInput->Font = (gcnew System::Drawing::Font(L"Times New Roman", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->lblInput->ForeColor = System::Drawing::Color::Red;
			this->lblInput->Location = System::Drawing::Point(12, 303);
			this->lblInput->Name = L"lblInput";
			this->lblInput->Size = System::Drawing::Size(18, 19);
			this->lblInput->TabIndex = 2;
			this->lblInput->Text = L">";
			// 
			// console
			// 
			this->console->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->console->Font = (gcnew System::Drawing::Font(L"Times New Roman", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->console->ForeColor = System::Drawing::Color::Red;
			this->console->Location = System::Drawing::Point(12, 13);
			this->console->Name = L"console";
			this->console->ReadOnly = true;
			this->console->Size = System::Drawing::Size(486, 282);
			this->console->TabIndex = 1;
			this->console->Text = L"";
			// 
			// input
			// 
			this->input->BackColor = System::Drawing::SystemColors::Control;
			this->input->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->input->Font = (gcnew System::Drawing::Font(L"Times New Roman", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->input->ForeColor = System::Drawing::Color::Red;
			this->input->Location = System::Drawing::Point(36, 301);
			this->input->Name = L"input";
			this->input->Size = System::Drawing::Size(462, 26);
			this->input->TabIndex = 0;
			this->input->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &gui::input_KeyDown);
			// 
			// gui
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::Color::WhiteSmoke;
			this->ClientSize = System::Drawing::Size(510, 333);
			this->Controls->Add(this->backPanel);
			this->MaximizeBox = false;
			this->MaximumSize = System::Drawing::Size(526, 372);
			this->MinimumSize = System::Drawing::Size(526, 372);
			this->Name = L"gui";
			this->ShowIcon = false;
			this->Text = L"Sploity | BETA | LegendsZ#1526 |";
			this->Load += gcnew System::EventHandler(this, &gui::gui_Load);
			this->Shown += gcnew System::EventHandler(this, &gui::gui_Shown);
			this->backPanel->ResumeLayout(false);
			this->backPanel->PerformLayout();
			this->ResumeLayout(false);

		}
#pragma endregion

		private: System::Void gui_Shown(System::Object^ sender, System::EventArgs^ e) { 

			this->Text = "Project Sploity | BETA | @LegendsZ#1526 | Loading...";

			const wchar_t* name = L"ac_client.exe";

			console->Text = console->Text + "OK!\n";
			console->Text = console->Text + "[CONSOLE]: Looking for game...";
			DWORD processID = 0;
			do {
				processID = processID = getProcessID(name);
				Refresh();
				Sleep(500);
			} while (processID == 0);
			console->Text = console->Text + "OK!\n";

			console->Text = console->Text + "[CONSOLE]: Obtaining module base address...";
			modBase = getModBaseAddy(processID, name);
			console->Text = console->Text + "OK!\n";

			console->Text = console->Text + "[CONSOLE]: Opening handle...";
			hGame = OpenProcess(PROCESS_ALL_ACCESS, false, processID); //try null instead if need be
			console->Text = console->Text + "OK!\n";

			this->Text = "Project Sploiter | BETA | @LegendsZ#1526 | ACTIVE";

			Refresh();
			Sleep(1000);

			this->console->Text = "Welcome to Project Sploity!\nType 'cmds' for commands!\n";
		}

		private: System::Void gui_Load(System::Object^ sender, System::EventArgs^ e) {
			
		}
		private: System::Void input_KeyDown(System::Object^ sender, System::Windows::Forms::KeyEventArgs^ e) {
		if (e->KeyCode.Equals(Keys::Enter)) {
			String^ command = input->Text;
			if (command->Equals("godmode")) {
				godMode(&hGame, &modBase);
			}
			else if (command->Equals("infammo")) {
				infAmmo(&hGame, &modBase);
			}
			else if (command->Equals("jump")) {
				//std::thread newThread(keepJumping);
				keepJumping(&hGame, &modBase);
			}
			this->input->Text = "";
		}
	}

		private: void godMode(interior_ptr<HANDLE> proc, interior_ptr<uintptr_t> baseAddy) {
			int currentHealth = 0;
			int newHealth = INT_MAX;

			uintptr_t healthAddy = findDMAAddy(*proc, *baseAddy, healthOffset);
			ReadProcessMemory(*proc, (BYTE*)healthAddy, &currentHealth, sizeof(healthAddy), nullptr);
			WriteProcessMemory(*proc, (BYTE*)healthAddy, &newHealth, sizeof(newHealth), nullptr);

			this->console->Text += "[CONSOLE]: Changed health from " + currentHealth + " to " + newHealth + "!\n";
		   }

		private: void infAmmo(interior_ptr<HANDLE> proc, interior_ptr<uintptr_t> baseAddy) {
			int currentAmmo = 0;
			int newAmmo = INT_MAX;

			uintptr_t ammoAddy = findDMAAddy(*proc, *baseAddy, ammoOffset);
			ReadProcessMemory(*proc, (BYTE*)ammoAddy, &currentAmmo, sizeof(ammoAddy), nullptr);
			WriteProcessMemory(*proc, (BYTE*)ammoAddy, &newAmmo, sizeof(newAmmo), nullptr);

			this->console->Text += "[CONSOLE]: Changed ammo from " + currentAmmo + " to " + newAmmo + "!\n";
		}

		private: void keepJumping(interior_ptr<HANDLE> proc, interior_ptr<uintptr_t> baseAddy) {
			int currentStatus = 0; //1
			int newStatus = 1;//currentStatus;

			uintptr_t isOnGround = findDMAAddy(*proc, *baseAddy, isOnGroundOffset);
			ReadProcessMemory(*proc, (BYTE*)isOnGround, &currentStatus, sizeof(isOnGround), nullptr);
			//newStatus = (int)(!(bool)currentStatus);
			WriteProcessMemory(*proc, (BYTE*)isOnGround, &newStatus, sizeof(newStatus), nullptr);

			this->console->Text += "[CONSOLE]: Changed on-ground status from " + (bool)currentStatus + " to " + (bool)newStatus + "!\n";
		}

		//private: void loopJump()
};
}
