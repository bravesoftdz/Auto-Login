//---------------------------------------------------------------------------

#include <vcl.h>
#include <string.h>
#include <clipbrd.hpp>
#pragma hdrstop

#include "Unit1.h"
#include "Unit2.h"
#include "Unit3.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;
int s,sec=0, sek2=0,n_log,n_pass,i,k=0,L,T,Anim,Access,Minimize,Delete=1,Top=0, onoff=0, Speed_Anim=-10;
AnsiString login,password, buf, Name_window;

int Slee_p(int interval)
	{
		for(DWORD tt=GetTickCount();GetTickCount()-tt<1;Sleep(interval))
			Application->ProcessMessages();
    }

int Tab()
	{
        keybd_event(VK_TAB, 0,0,0);  //Tab
		keybd_event(VK_TAB, 0,KEYEVENTF_KEYUP,0);
	}

int Contrl_V()
	{
		keybd_event(VK_CONTROL, 0,0,0);  //Ctrl
		keybd_event(0x56, 0,0,0);  //V
		keybd_event(0x56, 0,KEYEVENTF_KEYUP,0);
		keybd_event(VK_CONTROL, 0,KEYEVENTF_KEYUP,0);
    }

AnsiString XOR_Crypt(AnsiString in)
	{
		AnsiString out,
		pass="~�%g";
			for (int x=1;x<in.Length()+1;x++)
				{
					out += (char)(in[x] ^ pass[x%pass.Length()+1]);
				}
		return out;
	}

int Count()
{
	Form1->Label4->Caption="���������� �������: "+IntToStr(Form1->ADOTable1->RecordCount);
		Form1->Label7->Caption=Form1->Label4->Caption;
}

int OffFiltreFormTwo()
	{
		Form2->ADOTable1->Active=false;
		Form2->ADOTable1->Active=true;
    }

int Numb()
	{
		Form1->ADOTable1->Active=false;
		Form1->ADOTable1->Active=true;
		Form1->ADOTable1->First();
			for(i=1;i<=Form1->ADOTable1->RecordCount;i++)
				{
					Form1->ADOTable1->Edit();
						Form1->ADOTable1->FieldByName("ID")->AsString=i;
					Form1->ADOTable1->Post();
						Form1->ADOTable1->Next();
				}
		Form1->ADOTable1->First();
	}

AnsiString Report(AnsiString Operation, AnsiString Account, AnsiString Site)
	{
		int ID, ID1, ID2;
		AnsiString time;

		if(Form2->ADOTable1->RecordCount==671)
			{
				Form2->ADOTable1->First();
				Form2->ADOTable1->Next();
				Form2->ADOTable1->Delete();
			}
		if(Form2->ADOTable1->RecordCount!=0)
			{
				Form2->ADOTable1->First();
					ID1=StrToInt(Form2->ADOTable1->FieldByName("ID")->AsString);
				Form2->ADOTable1->Last();
					ID2=StrToInt(Form2->ADOTable1->FieldByName("ID")->AsString);
				if(ID1 > ID2)
					ID=ID1+1;
				else ID=ID2+1;
			}
		else ID=1;

		Form2->ADOTable1->Append();
			Form2->ADOTable1->FieldByName("ID")->AsString=ID;
			Form2->ADOTable1->FieldByName("Site")->AsString=Site;
			Form2->ADOTable1->FieldByName("Account")->AsString=Account;
			Form2->ADOTable1->FieldByName("Operation")->AsString=Operation;
			Form2->ADOTable1->FieldByName("Date")->AsString=Date();
			Form2->ADOTable1->FieldByName("Time")->AsString=Time();
		Form2->ADOTable1->Post();
	}

void edit()
	{
		if(Form1->CheckBox1->Checked==true)
			{
				Form1->Edit10->Text=Form1->ADOTable1->FieldByName("Site")->AsString;
				Form1->Edit11->Text=Form1->ADOTable1->FieldByName("Login")->AsString;
				Form1->Edit12->Text=XOR_Crypt(Form1->ADOTable1->FieldByName("Password")->AsString);
				Form1->Memo2->Text=XOR_Crypt(Form1->ADOTable1->FieldByName("Note")->AsString);

				Form1->Edit14->Text=Form1->ADOTable1->FieldByName("Programm")->AsString;
				Form1->Edit15->Text=Form1->ADOTable1->FieldByName("Programm2")->AsString;
				Form1->Edit16->Text=Form1->ADOTable1->FieldByName("Programm3")->AsString;


			}
	}

void check_programm_address()
	{
		if(Form1->Edit14->Text=="")
			Form1->SpeedButton7->Enabled=false;
		else
			Form1->SpeedButton7->Enabled=true;

		if(Form1->Edit15->Text=="")
			Form1->SpeedButton8->Enabled=false;
		else
			Form1->SpeedButton8->Enabled=true;

		if(Form1->Edit16->Text=="")
			Form1->SpeedButton9->Enabled=false;
		else
			Form1->SpeedButton9->Enabled=true;
    }
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Timer1Timer(TObject *Sender)
{
	if(sec<0)                       //�����/���� ������
		{
			Timer1->Enabled=false;
		}
	if(sec==3)
		{
			if (Clipboard()->HasFormat(CF_TEXT))
				{
					CopyHere->Text = Clipboard()->AsText;
					buf=CopyHere->Text;
				}
		CopyThis->Text=login;           //�����
			CopyThis->SelectAll();
			CopyThis->CopyToClipboard();
		Contrl_V();
		}
	if(sec==2)
		{
			Tab();
		CopyThis->Text=password;          //������
			CopyThis->SelectAll();
			CopyThis->CopyToClipboard();
		Contrl_V();
			keybd_event(VK_RETURN, 0,0,0);  //����
			keybd_event(VK_RETURN, 0,KEYEVENTF_KEYUP,0);
		}
	if(sec==1)
		{
			if(buf=="")
				{
					CopyThis->Text="Clear";    // �������� ������ �� ������
						CopyThis->SelectAll();
						CopyThis->CopyToClipboard();
				}
			else
				{
					CopyThis->Text=buf;
						CopyThis->SelectAll();  //��������� ������ ����� � �����
						CopyThis->CopyToClipboard();
						CopyThis->Text="";
				}
        }
	sec=sec-1;
}
//---------------------------------------------------------------------------



void __fastcall TForm1::Button3Click(TObject *Sender)
{
	if(ADOTable1->RecordCount!=0)
		{
		Panel7Click(Sender);
			if(Delete==0)
				{
					Button23Click(Sender);
				}
			else
				{
					if(Panel7->Visible!=true)
						{
							Panel7->Height=-10;
							Panel7->Visible=true;
							if(Anim==1)
								for(i=1;i<=95;i=i+Speed_Anim)
									{
										Slee_p(1); //��������
										Panel7->Height=i;
									}
								Panel7->Height=95;
								Button23->SetFocus();
						}
				}
		}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button1Click(TObject *Sender)
{
	Button14Click(Sender);
	Button17Click(Sender);
	Button21Click(Sender);
	Button28Click(Sender);

	if(Form1->Width==380)
		{
			Button1->Caption="<<���. ����";
			if(Anim==1)
				for(i=Form1->Width;i<=515;i=i+10)
					{
						Slee_p(1); //��������
						Form1->Width=i;
					}
			Form1->Width=515;
		}
	else
		{
			Button1->Caption="          ���. ����>>";
			if(Anim==1)
				for(i=Form1->Width;i>=380;i=i-10)
					{
						Slee_p(1); //��������
						Form1->Width=i;
					}
				Form1->Width=380;
		}
	Label5->Left=Form1->Width-205;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button5Click(TObject *Sender)
{
	Edit1->Clear();
	Edit2->Clear();
	Edit8->Clear();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::FormCreate(TObject *Sender)
{
	if(FileExists("ALog.mdb"))
		{
			Form1->FormStyle=fsStayOnTop;
			Form1->FormStyle=fsNormal;
			//Form1->Close();
			Count();
					Form1->Width=380;
						Form1->Height=400;
						Form1->Constraints->MaxHeight=400;
						Form1->Constraints->MinHeight=400;
						Form1->Constraints->MinWidth=379;
						Form1->Constraints->MaxWidth=380;
									Panel1->Top=87;
									Panel1->Left=50;
								Panel2->Top=0;
								Panel2->Left=0;
							Panel3->Top=0;
							Panel3->Left=0;
						Panel4->Top=75;
						Panel4->Left=80;
						Panel4->Height=133;
					Panel5->Top=75;
					Panel5->Left=80;
				Panel6->Top=75;
				Panel6->Left=80;
				Panel6->Height=133;
			Panel7->Top=150;
			Panel7->Left=110;
		Panel8->Top=157;
		Panel8->Left=446;

			if(CheckBox4->Checked==true)               //���������/���������� �������� ��������
				SpeedButton10->Enabled=true;
			else
				SpeedButton10->Enabled=false;

			Anim=StrToInt(ADOTable2->FieldByName("Animation")->AsString);
			if(Anim==1)
				CheckBox4->Checked=true;
			else
				CheckBox4->Checked=false;
			Minimize=StrToInt(ADOTable2->FieldByName("Minimize")->AsString);
				if(Minimize==1)
				CheckBox5->Checked=true;
			else
				CheckBox5->Checked=false;

			Speed_Anim=(StrToInt(ADOTable2->FieldByName("Speed_Anim")->AsString)+3)*(-1);
		}
	else
		{
			ShowMessage("����, ���� ���� �� ������!");
			Form1->Close();
		}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Edit3Click(TObject *Sender)
{
	if(Edit3->Text=="Live Search...")
		Edit3->Text="";
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Edit3KeyPress(TObject *Sender, System::WideChar &Key)
{
	if(Key==13)
		{
			ADOTable1->Filtered=false;
				ADOTable1->Filter =("[Login] LIKE '"+ Edit3->Text +"%'");
			ADOTable1->Filtered=true;
		}
	if(Key==VK_ESCAPE)
		TForm1::Button6Click(Sender);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button6Click(TObject *Sender)
{
	Edit3->Text="Live Search...";
		ADOTable1->Filtered=false;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::DBGrid1KeyPress(TObject *Sender, System::WideChar &Key)
{
	if(CheckBox1->Checked==false)
		{
			if(Key=13)
			{
				keybd_event(VK_MENU, 0, 0 ,0);
				keybd_event(VK_TAB, 0, 0 ,0);
					keybd_event(VK_MENU, 0, KEYEVENTF_KEYUP,0);
					keybd_event(VK_TAB, 0, KEYEVENTF_KEYUP,0);

	Slee_p(5); //��������

				login=ADOTable1->FieldByName("Login")->AsString;
					n_log=login.Length();
				password=ADOTable1->FieldByName("Password")->AsString;
					n_pass=password.Length();
					Report("Use record", login, ADOTable1->FieldByName("Site")->AsString);
				Timer1->Enabled=true;
			}
		}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::FormKeyPress(TObject *Sender, System::WideChar &Key)
{
	if(Key==VK_RETURN)
		{
			keybd_event(VK_MENU, 0, 0 ,0);
			keybd_event(VK_TAB, 0, 0 ,0);
				keybd_event(VK_MENU, 0, KEYEVENTF_KEYUP,0);
				keybd_event(VK_TAB, 0, KEYEVENTF_KEYUP,0);

	Slee_p(10); //��������
		 if(CheckBox1->Checked==false)
			{
			login=ADOTable1->FieldByName("Login")->AsString;
				n_log=login.Length();
			password=ADOTable1->FieldByName("Password")->AsString;
				n_pass=password.Length();
			ADOTable1->Next();
			Timer1->Enabled=true;
			}
		}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Edit7KeyPress(TObject *Sender, System::WideChar &Key)
{
	if(Key==13)
		{
			TForm1::Button13Click(Sender);
		}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Edit6KeyPress(TObject *Sender, System::WideChar &Key)
{
	if(Key==13)
		{
			TForm1::Button13Click(Sender);
		}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::ApplicationEvents1Message(tagMSG &Msg, bool &Handled)
{
	int next=0;
	AnsiString now_prog, now_prog2;
			HWND fore = ::GetForegroundWindow();
			TCHAR szTitle[MAX_PATH] = {0};
			::SendMessage(fore, WM_GETTEXT, MAX_PATH, LPARAM(szTitle));
			now_prog = String(szTitle);

	now_prog2=now_prog;
	if(now_prog.Length()>8)
		{
			now_prog.Delete(1, now_prog.Length()-8);
				if(now_prog==" � Opera")
					now_prog2.Delete(now_prog2.Length()-7,8 );
		}

	now_prog=now_prog2;
	if(now_prog.Length()>16)
		{
			now_prog.Delete(1, now_prog.Length()-16);
				if(now_prog==" - Google Chrome")
					now_prog2.Delete(now_prog2.Length()-15,16 );
		}

	now_prog=now_prog2;
	if(now_prog.Length()>18)
		{
			now_prog.Delete(1, now_prog.Length()-18);
				if(now_prog==" ?- Microsoft Edge")
					now_prog2.Delete(now_prog2.Length()-17,18 );
		}

			now_prog=now_prog2;
			if(now_prog.Length()>18)
				{
					now_prog.Delete(1, now_prog.Length()-18);
						if(now_prog==" - Mozilla Firefox")
							now_prog2.Delete(now_prog2.Length()-17,18 );
				}

		if(now_prog2=="AutoLogin by Alex [PraiD]")
			now_prog2="";

		if (Msg.message == WM_HOTKEY)
			   {
				   if (Msg.wParam == 0x00F)
					   if(Access==1)
							{
									login=ADOTable1->FieldByName("Login")->AsString;
									password=XOR_Crypt(ADOTable1->FieldByName("Password")->AsString);
								Report("�������������", login, ADOTable1->FieldByName("Site")->AsString);
										Label4->Caption="���������� �������:"+IntToStr(ADOTable1->RecordCount);
									Label7->Caption=Label4->Caption;

	if(now_prog2!=ADOTable1->FieldByName("Programm")->AsString &&
	now_prog2!=ADOTable1->FieldByName("Programm2")->AsString &&
	now_prog2!=ADOTable1->FieldByName("Programm3")->AsString)
		{

			if(ADOTable1->FieldByName("Programm")->AsString=="")
				{
					Name_window=now_prog2;
					ADOTable1->Edit();
						ADOTable1->FieldByName("Programm")->AsString=Name_window;
					ADOTable1->Post();
				}
			else
			if(ADOTable1->FieldByName("Programm2")->AsString=="")
				{
					Name_window=now_prog2;
					ADOTable1->Edit();
						ADOTable1->FieldByName("Programm2")->AsString=Name_window;
					ADOTable1->Post();
				}
			else
			if(ADOTable1->FieldByName("Programm3")->AsString=="")
				{
					Name_window=now_prog2;
					ADOTable1->Edit();
						ADOTable1->FieldByName("Programm3")->AsString=Name_window;
					ADOTable1->Post();
				}
			else
				{
					Name_window=now_prog2;
					Form3->Edit1->Text=Name_window;

					if(ADOTable1->FieldByName("Programm")->AsString!="")
						{
							Form3->RadioButton2->Visible=true;
							Form3->RadioButton2->Caption=ADOTable1->FieldByName("Programm")->AsString;
						}

					if(ADOTable1->FieldByName("Programm2")->AsString!="")
						{
							Form3->RadioButton1->Visible=true;
							Form3->RadioButton1->Caption=ADOTable1->FieldByName("Programm2")->AsString;
						}

					if(ADOTable1->FieldByName("Programm3")->AsString!="")
						{
							Form3->RadioButton3->Visible=true;
							Form3->RadioButton3->Caption=ADOTable1->FieldByName("Programm3")->AsString;
						}
					Timer5->Enabled=true;
				}
		}

	if(ADOTable5->Locate("Programm", now_prog2,TLocateOptions() << loCaseInsensitive))
		if(ADOTable1->FieldByName("Site")->AsString!=ADOTable5->FieldByName("Site")->AsString)
			Timer5->Enabled=true;
	if(ADOTable5->Locate("Programm2", now_prog2,TLocateOptions() << loCaseInsensitive))
		if(ADOTable1->FieldByName("Site")->AsString!=ADOTable5->FieldByName("Site")->AsString)
			Timer5->Enabled=true;
	if(ADOTable5->Locate("Programm3", now_prog2,TLocateOptions() << loCaseInsensitive))
		if(ADOTable1->FieldByName("Site")->AsString!=ADOTable5->FieldByName("Site")->AsString)
			Timer5->Enabled=true;

								ADOTable2->Edit();
								Timer1->Enabled=true;
								sec=6;
							}
			   }
	}
//---------------------------------------------------------------------------

void __fastcall TForm1::Edit3Change(TObject *Sender)
{
	if(Edit3->Text!="" && Edit3->Text!="Live Search...")
		{
			ADOTable1->Filtered=false;
				ADOTable1->Filter =("[Site] LIKE '"+ Edit3->Text +"%'"); // Search
			ADOTable1->Filtered=true;
		}
	if(Edit3->Text=="")
		ADOTable1->Filtered=false;
	Count();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::GroupBox6MouseMove(TObject *Sender, TShiftState Shift, int X,
          int Y)
{
	s=1;
	Timer2->Enabled=false;
	Button7->Visible=true;
	Button8->Visible=true;
	Button11->Visible=true;
	SpeedButton1->Visible=true;
	Timer2->Enabled=true;
	CheckBox7->Visible=true;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button9Click(TObject *Sender)
{
	int screenW=GetSystemMetrics(SM_CXSCREEN);
	int screenH=GetSystemMetrics(SM_CYSCREEN);

	Button14Click(Sender);
	Button17Click(Sender);
	Button21Click(Sender);
	Button24Click(Sender);
	Button28Click(Sender);
	Panel8->Visible=false;

	L=Form1->Left;
	T=Form1->Top;
		Form1->Visible=false;
			Form1->BorderStyle=bsNone;
					Form1->Constraints->MinHeight=0;
					Form1->Constraints->MinWidth=304;
						Form1->Width=308;
							Form1->Height=116;
						Panel2->Visible=true;
						Form1->Left=screenW-350;
						Form1->Top=screenH-200;
					Form1->Visible=true;
				Edit3->Text="Live Search...";
			Form1->FormStyle=fsStayOnTop;
		SpeedButton1->Flat=false;
	Timer6->Enabled=false;
	Count();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button7Click(TObject *Sender)
{
	Form1->Visible=false;
		Form1->Left=L;
		Form1->Top=T;
			Form1->BorderStyle=bsSizeable;
				Form1->FormStyle=fsNormal;
					Form1->Constraints->MinHeight=0;
						Form1->Width=515;
						Form1->Height=400;
							Form1->Constraints->MinHeight=400;
							Form1->Constraints->MinWidth=379;
							Form1->Constraints->MaxWidth=515;
						Button1->Caption="<<���. ����";
					Panel2->Visible=false;
				SpeedButton1->Flat=true;
			Button15Click(Sender);
		ComboBox1Change(Sender);
	Form1->Visible=true;
Timer6->Enabled=true;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Timer2Timer(TObject *Sender)
{
	if(s==0)
		{
			Button7->Visible=false;
			Button8->Visible=false;
			Button11->Visible=false;
			SpeedButton1->Visible=false;
			CheckBox7->Visible=false;
		}
	s--;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button8Click(TObject *Sender)
{
	ADOTable1->Last();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button11Click(TObject *Sender)
{
	ADOTable1->First();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button12Click(TObject *Sender)
{
	Form2->Show();
    Form2->ADOTable1->Last();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button13Click(TObject *Sender)
{
	if((Edit1->Text!="")||(Edit2->Text!="")||(Edit8->Text!=""))
		{
		Button6Click(Sender);   //���������� ������� � �������
		ADOTable1->First();
			ADOTable1->Append();
				ADOTable1->FieldByName("Site")->AsString=Edit1->Text;
				ADOTable1->FieldByName("Login")->AsString=Edit2->Text;
				ADOTable1->FieldByName("Password")->AsString=XOR_Crypt(Edit8->Text);
				ADOTable1->FieldByName("Note")->AsString=XOR_Crypt(Memo1->Text);
			ADOTable1->Post();
			OffFiltreFormTwo();
				Report("����������", Edit2->Text, Edit1->Text);
				Numb();

					Edit1->Clear(); Edit2->Clear(); Edit8->Clear();
						Slee_p(10); //��������
			Count();
			Button14Click(Sender);
		}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button14Click(TObject *Sender)
{
	Button5Click(Sender);
	if(Panel4->Visible==true)
		{
			if(Anim==1)
				for(i=133;i>=-10;i=i-Speed_Anim)
					{
						Slee_p(1); //��������
						Panel4->Height=i;
					}
			Panel4->Height=-10;
			Panel4->Visible=false;
		}
	CheckBox3->Checked=false;
	Memo1->Clear();
	SpeedButton2->Glyph=SpeedButton3->Glyph;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Edit8KeyPress(TObject *Sender, System::WideChar &Key)
{
	if(Key==13)
		Button13Click(Sender);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Edit1KeyPress(TObject *Sender, System::WideChar &Key)
{
	if(Key==13)
		Button13Click(Sender);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Edit2KeyPress(TObject *Sender, System::WideChar &Key)
{
	if(Key==13)
		Button13Click(Sender);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Image2MouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y)
{
	if(Button == mbLeft)
		{
		long SC_DRAGMOVE = 0xF012;
		ReleaseCapture();
		SendMessage(Form1->Handle, WM_SYSCOMMAND, SC_DRAGMOVE, 0);
		}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::GroupBox6MouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y)
{
	if(Button == mbLeft)
		{
		long SC_DRAGMOVE = 0xF012;
		ReleaseCapture();
		SendMessage(Form1->Handle, WM_SYSCOMMAND, SC_DRAGMOVE, 0);
		}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button4Click(TObject *Sender)
{
	if(ADOTable4->Locate("Password",XOR_Crypt(Edit4->Text),TLocateOptions() << loCaseInsensitive))
		{
			UnregisterHotKey(Form1->Handle,0x00F); // ���������� ������� ������
			bool RHKret = RegisterHotKey(Form1->Handle,0x00F, MOD_ALT, VK_RETURN);  // �k� ������� ������
				if (RHKret)
					{
						Label3->Caption="< ������ >";
					}
				else
					{
						Label3->Caption="< ������ >";
					}

			Image5->Visible=true;
			GroupBox1->Visible=true;
				Slee_p(1); //��������
			Image5->Visible=false;                       //access allowed
			Access=1;
			Timer4->Enabled=true;
			OffFiltreFormTwo();
				Report("���� � ���������", "--", "--");

			if(Anim==1)
				{
					while(Panel3->Height>0)
						{
							Form1->Panel3->Height-=20;
							//Form1->Panel3->Top+=4;
							Slee_p(1); //��������
						}
				}
			else
				Panel3->Visible=false;
			Form1->Constraints->MaxHeight=800;
			Form1->Constraints->MinHeight=400;
			Form1->Constraints->MinWidth=379;
			Form1->Constraints->MaxWidth=515;

			if(Minimize==1)
				Button9Click(Sender);
		}
	else
		{
			Image4->Visible=true;
				Slee_p(1000); //��������
			Image4->Visible=false;                                      //access denied
			Edit4->Clear();
			Report("��������� ����", "--", "--");
		}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Edit5Change(TObject *Sender)
{
	if(Edit5->Text!="")
		if(ComboBox1->Text=="Site")
			{
				if(ComboBox1->Text=="Site")
					ADOTable1->Filtered=false;
						ADOTable1->Filter =("[Site] LIKE '"+ Edit5->Text +"%'"); // Search
					ADOTable1->Filtered=true;
			}
	if(Edit5->Text!="")
		if(ComboBox1->Text=="Login" )
			{
				if(ComboBox1->Text=="Login")
					ADOTable1->Filtered=false;
						ADOTable1->Filter =("[Login] LIKE '"+ Edit5->Text +"%'"); // Search
					ADOTable1->Filtered=true;
			}
	if(Edit5->Text=="")
		ADOTable1->Filtered=false;
		Count();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button15Click(TObject *Sender)
{
	Edit5->Clear();
		ADOTable1->Filtered=false;
}
//---------------------------------------------------------------------------


void __fastcall TForm1::ComboBox1Change(TObject *Sender)
{
	Edit5->Clear();
	Edit5Change(Sender);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Edit4KeyPress(TObject *Sender, System::WideChar &Key)
{
	if(Key==13)
	Button4Click(Sender);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button16Click(TObject *Sender)
{
	if(Panel5->Visible!=true)
		{
			Panel5->Height=-10;
			Panel5->Visible=true;
			Image10Click(Sender);
			if(Anim==1)
				for(i=1;i<=145;i=i+Speed_Anim)
					{
						Slee_p(1); //��������
						Panel5->Height=i;
					}
				Panel5->Height=145;
					Panel5->Height=-10;
					Panel5->Visible=true;
					Panel5->Height=145;
				Edit6->SetFocus();
		}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button17Click(TObject *Sender)
{
	if(Panel5->Visible==true)
		{
			if(Anim==1)
				for(i=145;i>=-10;i=i-Speed_Anim)
					{
						Slee_p(1); //��������
						Panel5->Height=i;
					}
			Panel5->Height=-10;
				Panel5->Visible=false;
					Edit6->Clear();
						Edit7->Clear();
							Edit9->Clear();
		}
}
//---------------------------------------------------------------------------


void __fastcall TForm1::Edit6Change(TObject *Sender)
{
	if(Edit6->Text!="")
	if(ADOTable4->Locate("Password",XOR_Crypt(Edit6->Text),TLocateOptions() << loCaseInsensitive))
		{
			Image7->Visible=true;
			Image6->Visible=false;
		}
	else
		{
			Image7->Visible=false;
			Image6->Visible=true;
		}
	else
		{
			Image7->Visible=false;
			Image6->Visible=false;
		}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Edit9Change(TObject *Sender)
{
	if(Edit7->Text==Edit9->Text)
		{
			Image9->Visible=true;
			Image8->Visible=false;
		}
	else
		{
			Image8->Visible=true;
			Image9->Visible=false;
		}
	if(Edit7->Text=="" && Edit9->Text=="")
		{
			Image8->Visible=false;
			Image9->Visible=false;
		}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Edit7Change(TObject *Sender)
{
	Edit9Change(Sender);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button18Click(TObject *Sender)
{
	if(ADOTable4->Locate("Password",XOR_Crypt(Edit6->Text),TLocateOptions() << loCaseInsensitive))
		if(Edit7->Text==Edit9->Text && Edit7->Text!="")
			{
				ADOTable4->Edit();
					ADOTable4->FieldByName("Password")->AsString=XOR_Crypt(Edit9->Text);
				ADOTable4->Post();
					Label15->Visible=true;
						Slee_p(1000); //��������
					Label15->Visible=false;
					Button17Click(Sender);
					Report("����� ������", "", "");
			}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Edit9KeyPress(TObject *Sender, System::WideChar &Key)
{
	if(Key==13)
	Button18Click(Sender);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::SpeedButton1Click(TObject *Sender)
{
	if(SpeedButton1->Flat==true)
		{
			Form1->FormStyle=fsStayOnTop;
				SpeedButton1->Flat=false;
		}
	else
		{
			Form1->FormStyle=fsNormal;
				SpeedButton1->Flat=true;
		}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Image1MouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift,
		  int X, int Y)
{
	if(Button == mbLeft)
		{
			long SC_DRAGMOVE = 0xF012;
			ReleaseCapture();
			SendMessage(Panel4->Handle, WM_SYSCOMMAND, SC_DRAGMOVE, 0);
		}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Image10MouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y)
{
	if(Button == mbLeft)
		{
			long SC_DRAGMOVE = 0xF012;
			ReleaseCapture();
			SendMessage(Panel5->Handle, WM_SYSCOMMAND, SC_DRAGMOVE, 0);
		}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::DBGrid1DblClick(TObject *Sender)
{
if(CheckBox1->Checked==true)
	if(Panel6->Visible!=true)
		{
			edit();
			check_programm_address();
			CheckBox2->Checked=false;
			CheckBox2Click(Sender);
			Panel6->Height=-10;
			Panel6->Visible=true;
			Image11Click(Sender);
			if(Anim==1)
				for(i=1;i<=133;i=i+Speed_Anim)
					{
						Slee_p(1); //��������
						Panel6->Height=i;
					}
				Panel6->Height=133;
			Edit10->SetFocus();
		}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button21Click(TObject *Sender)
{
	if(Panel6->Visible==true)
		{
			if(Anim==1)
				for(i=133;i>=-10;i=i-Speed_Anim)
					{
						Slee_p(1); //��������
						Panel6->Height=i;
					}
			Panel6->Height=-10;
			Panel6->Visible=false;
		}
	CheckBox2->Checked=false;
	SpeedButton5->Glyph=SpeedButton3->Glyph;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::CheckBox2Click(TObject *Sender)
{
	if(CheckBox2->Checked==true)
		{
			Edit12->PasswordChar=Edit1->PasswordChar;
		}
	else
		Edit12->PasswordChar=Edit13->PasswordChar;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Image11MouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y)
{
	if(Button == mbLeft)
		{
			long SC_DRAGMOVE = 0xF012;
			ReleaseCapture();
			SendMessage(Panel6->Handle, WM_SYSCOMMAND, SC_DRAGMOVE, 0);
		}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Image11Click(TObject *Sender)
{
	Panel6->BringToFront();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Image1Click(TObject *Sender)
{
	Panel4->BringToFront();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button22Click(TObject *Sender)
{
	if(ADOTable1->RecordCount!=0)
		{
			Button21Click(Sender);
			OffFiltreFormTwo();
				Report("��������������", Edit11->Text, Edit10->Text);
			ADOTable1->Edit();
				ADOTable1->FieldByName("Site")->AsString=Edit10->Text;
				ADOTable1->FieldByName("Login")->AsString=Edit11->Text;
				ADOTable1->FieldByName("Password")->AsString=XOR_Crypt(Edit12->Text);
				ADOTable1->FieldByName("Note")->AsString=XOR_Crypt(Memo2->Text);
			ADOTable1->Post();
			Memo2->Clear();
		}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button20Click(TObject *Sender)
{
	Edit10->Clear();
		Edit11->Clear();
			Edit12->Clear();
}
//---------------------------------------------------------------------------


void __fastcall TForm1::DBGrid1CellClick(TColumn *Column)
{
	edit();
	check_programm_address();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::DBGrid1KeyDown(TObject *Sender, WORD &Key, TShiftState Shift)
{
	edit();
	check_programm_address();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::DBGrid1KeyUp(TObject *Sender, WORD &Key, TShiftState Shift)
{
	edit();
	check_programm_address();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Image10Click(TObject *Sender)
{
	Panel5->BringToFront();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::CheckBox3Click(TObject *Sender)
{
	if(CheckBox3->Checked==true)
		{
			Edit8->PasswordChar=Edit1->PasswordChar;
		}
	else
		Edit8->PasswordChar=Edit13->PasswordChar;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::TrayIcon1DblClick(TObject *Sender)
{
	Form1->Show();
	Form1->SpeedButton1->Flat=true;
	Form1->FormStyle=fsStayOnTop;
	TrayIcon1->Visible = false;
	SetWindowPos(Form1->Handle, HWND_TOPMOST, 0, 0, 0, 0,SWP_NOMOVE | SWP_NOSIZE);
	SetWindowPos(Form1->Handle, HWND_NOTOPMOST, 0, 0, 0, 0,SWP_NOMOVE | SWP_NOSIZE);

	Access=1;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::CheckBox4Click(TObject *Sender)
{
	ADOTable2->Edit();
		if(CheckBox4->Checked==true)
			{
				ADOTable2->FieldByName("Animation")->AsString=1;
				Anim=1;
				SpeedButton10->Enabled=true;
			}
		else
			{
				ADOTable2->FieldByName("Animation")->AsString=0;
				Anim=0;
				SpeedButton10->Enabled=false;
				Panel8->Visible=false;
			}
	ADOTable2->Post();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::CheckBox5Click(TObject *Sender)
{
	ADOTable2->Edit();
		if(CheckBox5->Checked==true)
			{
				ADOTable2->FieldByName("Minimize")->AsString=1;
				Minimize=1;
			}
		else
			{
				ADOTable2->FieldByName("Minimize")->AsString=0;
				Minimize=0;
			}
	ADOTable2->Post();

}
//---------------------------------------------------------------------------

void __fastcall TForm1::Edit12KeyPress(TObject *Sender, System::WideChar &Key)
{
	if(Key==13)
		Button22Click(Sender);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::CheckBox6Click(TObject *Sender)
{
	if(CheckBox4->Checked==true)
		{
			Delete=1;
		}
	else
		{
			Delete=0;
		}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button24Click(TObject *Sender)
{
	if(Panel7->Visible==true)
		{
			if(Anim==1)
				for(i=95;i>=-10;i=i-Speed_Anim)
					{
						Slee_p(1); //��������
						Panel7->Height=i;
					}
			Panel7->Height=-10;
			Panel7->Visible=false;
		}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button23Click(TObject *Sender)
{
	if(ADOTable1->FieldByName("Login")->AsString!="Test" &&
	ADOTable1->FieldByName("Site")->AsString!="Test" &&
	ADOTable1->FieldByName("Password")->AsString!="Test")
		{
		 Button6Click(Sender);  //���������� ������� � �������
			Button24Click(Sender);
			OffFiltreFormTwo();
				Report("��������", ADOTable1->FieldByName("Login")->AsString,
			ADOTable1->FieldByName("Site")->AsString);
			ADOTable1->Delete();
				Numb();
				Count();
        }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Panel7Click(TObject *Sender)
{
	Panel7->BringToFront();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::CheckBox1Click(TObject *Sender)
{
	CheckBox2->Checked=false;
	CheckBox2Click(Sender);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Image12MouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y)
{
	if(Button == mbLeft)
		{
			long SC_DRAGMOVE = 0xF012;
			ReleaseCapture();
			SendMessage(Panel7->Handle, WM_SYSCOMMAND, SC_DRAGMOVE, 0);
		}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::DBGrid1MouseMove(TObject *Sender, TShiftState Shift, int X,
          int Y)
{
	if(ADOTable1->FieldByName("Note")->AsString=="")
		DBGrid1->Hint="����������: ����������";
	else
		DBGrid1->Hint="����������: "+XOR_Crypt(ADOTable1->FieldByName("Note")->AsString);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::FormResize(TObject *Sender)
{
	if(Form1->WindowState == wsMinimized)
		{
			Form1->Hide();
			TrayIcon1->Visible = true;
			TrayIcon1->BalloonTitle = "PraiD-INDUSTRIES";
			TrayIcon1->BalloonHint = "AutoLogin by Alex-[PraiD]";
			TrayIcon1->ShowBalloonHint();

		Access=0;
		}
	else
		{
			Access=1;
		}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::SpeedButton2Click(TObject *Sender)
{
	if(Panel4->Height==133)
		{
			SpeedButton2->Glyph=SpeedButton4->Glyph;
			Panel4->Height=173;
		}
	else
		{
			SpeedButton2->Glyph=SpeedButton3->Glyph;
			Panel4->Height=133;
		}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::SpeedButton5Click(TObject *Sender)
{
	if(Panel6->Height==133)
		{
			SpeedButton5->Glyph=SpeedButton4->Glyph;
			Panel6->Height=173;
		}
	else
		{
			SpeedButton5->Glyph=SpeedButton3->Glyph;
			Panel6->Height=133;
		}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button2Click(TObject *Sender)
{
	if(Panel4->Visible!=true)
		{
			Panel4->Height=-10;
			Panel4->Visible=true;
			CheckBox3->Checked=false;
			CheckBox3Click(Sender);
			Image1Click(Sender);
			if(Anim==1)
				for(i=1;i<=135;i=i+Speed_Anim)
					{
						Slee_p(1);
						Panel4->Height=i;
					}
			else
				{
					Panel4->Visible=true;
					Edit1->SetFocus();
				}
			Panel4->Height=133;
		}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::ProgressBar2MouseDown(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y)
{
	Slee_p(350);
		Form1->Close();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::ProgressBar1MouseDown(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y)
{
	Slee_p(350);
	Form1->Hide();
		TrayIcon1->Visible = true;
		TrayIcon1->BalloonTitle = "PraiD-INDUSTRIES";
		TrayIcon1->BalloonHint = "AutoLogin by Alex-[PraiD]";
		TrayIcon1->ShowBalloonHint();

		Access=0;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Timer3Timer(TObject *Sender)
{
	if(!FileExists("ALog.mdb"))
		Form1->Close();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::DBGrid1TitleClick(TColumn *Column)
{
	if((ADOTable1->Sort.Pos(Column->FieldName) > 0) && (ADOTable1->Sort.Pos("ASC") > 0))
		ADOTable1->Sort = Column->FieldName + " DESC";
	else ADOTable1->Sort = Column->FieldName + " ASC";
}
//---------------------------------------------------------------------------

void __fastcall TForm1::DBGrid2TitleClick(TColumn *Column)
{
  /*	if((ADOTable1->Sort.Pos(Column->FieldName) > 0) && (ADOTable1->Sort.Pos("ASC") > 0))
			ADOTable1->Sort = Column->FieldName + " DESC";
	else ADOTable1->Sort = Column->FieldName + " ASC";
	TForm1::Edit5Change(0);   */
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Timer4Timer(TObject *Sender)
{
	int next=0;

	AnsiString now_prog, now_prog2;                      //������������ ��� �������� ����
			HWND fore = ::GetForegroundWindow();
			TCHAR szTitle[MAX_PATH] = {0};
			::SendMessage(fore, WM_GETTEXT, MAX_PATH, LPARAM(szTitle));
			now_prog = String(szTitle);

	now_prog2=now_prog;
	if(now_prog.Length()>8)
		{
			now_prog.Delete(1, now_prog.Length()-8);
				if(now_prog==" � Opera")
					now_prog2.Delete(now_prog2.Length()-7,8 );
		}

	now_prog=now_prog2;
	if(now_prog.Length()>16)
		{
			now_prog.Delete(1, now_prog.Length()-16);
				if(now_prog==" - Google Chrome")
					now_prog2.Delete(now_prog2.Length()-15,16 );
		}

	now_prog=now_prog2;
	if(now_prog.Length()>18)
		{
			now_prog.Delete(1, now_prog.Length()-18);
				if(now_prog==" ?- Microsoft Edge")
					now_prog2.Delete(now_prog2.Length()-17,18 );
		}

	now_prog=now_prog2;
	if(now_prog.Length()>18)
		{
			now_prog.Delete(1, now_prog.Length()-18);
				if(now_prog==" - Mozilla Firefox")
					now_prog2.Delete(now_prog2.Length()-17,18 );
		}


		ADOTable3->Active=false;
		ADOTable3->Active=true;
		ADOTable3->First();
			if((ADOTable3->Locate("Programm", now_prog2,TLocateOptions() << loCaseInsensitive)) ||
			(ADOTable3->Locate("Programm2", now_prog2,TLocateOptions() << loCaseInsensitive)) ||
			(ADOTable3->Locate("Programm3", now_prog2,TLocateOptions() << loCaseInsensitive)))
				if(now_prog2!=""){
					ComboBox1->Text="Site";
					Edit5->Text=ADOTable3->FieldByName("Site")->AsString;
				}

}
//---------------------------------------------------------------------------

void __fastcall TForm1::CheckBox7Click(TObject *Sender)
{
	CheckBox8->Checked=CheckBox7->Checked;
	if(CheckBox7->Checked==false)
		{
			Timer4->Enabled=false;
		}
	else
		{
			Timer4->Enabled=true;
		}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::CheckBox8Click(TObject *Sender)
{
	CheckBox7->Checked=CheckBox8->Checked;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Timer5Timer(TObject *Sender)
{
	sek2++;
		if(sek2==3)
			{
				Form3->RadioButton1->Checked==false;
				Form3->RadioButton2->Checked==false;
				Form3->RadioButton3->Checked==false;

				Form3->Show();

				Timer5->Enabled=false;
				sek2=0;
			}
		if(sek2>3)
			{
			Timer5->Enabled=false;
				sek2=0;
			}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Timer6Timer(TObject *Sender)
{
	GroupBox2->Height=Form1->Height-55;
	GroupBox4->Top=Form1->Height-48;   // ������� � ���� � �����
	Label5->Left=Form1->Width-205;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button25Click(TObject *Sender)
{
	if(Panel4->Visible!=true)
		{
			check_programm_address();
			Panel1Click(Sender);
			Panel1->Height=-10;
			Panel1->Visible=true;
			if(Anim==1)
				for(i=1;i<=133;i=i+Speed_Anim)
					{
						Slee_p(1); //��������
						Panel1->Height=i;
					}
		}
	else
		Panel1->Visible=true;

	Panel1->Height=133;
	DBGrid1->SetFocus();

}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button28Click(TObject *Sender)
{
	if(Panel1->Visible==true)
		{
			if(Anim==1)
				for(i=145;i>=-10;i=i-Speed_Anim)
					{
						Slee_p(1); //��������
						Panel1->Height=i;
					}
			Panel1->Height=-10;
				Panel1->Visible=false;
		}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button27Click(TObject *Sender)
{
	Edit14->Clear();
		Edit15->Clear();
			Edit16->Clear();
			check_programm_address();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::SpeedButton7Click(TObject *Sender)
{
	Edit14->Clear();
	check_programm_address();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::SpeedButton8Click(TObject *Sender)
{
	Edit15->Clear();
	check_programm_address();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::SpeedButton9Click(TObject *Sender)
{
	Edit16->Clear();
	check_programm_address();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button26Click(TObject *Sender)
{
	ADOTable1->Edit();
		ADOTable1->FieldByName("Programm")->AsString=Edit14->Text;
		ADOTable1->FieldByName("Programm2")->AsString=Edit15->Text;
		ADOTable1->FieldByName("Programm3")->AsString=Edit16->Text;
	ADOTable1->Post();
	DBGrid1->SetFocus();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::SpeedButton10Click(TObject *Sender)
{
	if(Panel8->Visible==false)
		{
			Panel8->Height=-1;
			TrackBar1->Position=(Speed_Anim-3)*(-1);
			Panel8->Visible=true;
			if(Anim==1)
				for(i=Panel8->Height;i<=106;i=i+5)
					{
						Slee_p(1); //��������
						Panel8->Height=i;
					}
			Panel8->Height=106;
			TrackBar1->SetFocus();
		}
	else
		{
			TrackBar1->Position=(Speed_Anim-3)*(-1);
			if(Anim==1)
				for(i=Panel8->Height;i>=106;i=i-5)
					{
						Slee_p(1); //��������
						Panel8->Height=i;
					}
				Panel8->Height=106;
				Panel8->Visible=false;
		}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::TrackBar1Change(TObject *Sender)
{
	ADOTable2->Edit();
		Speed_Anim=(TrackBar1->Position-3)*(-1);
		ADOTable2->FieldByName("Speed_Anim")->AsString=(Speed_Anim+3)*(-1);
 	ADOTable2->Post();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Panel1Enter(TObject *Sender)
{
	if(Edit14->Text=="")
		SpeedButton7->Enabled=false;
	else
		SpeedButton7->Enabled=true;

	if(Edit15->Text=="")
		SpeedButton8->Enabled=false;
	else
		SpeedButton8->Enabled=true;

	if(Edit16->Text=="")
		SpeedButton9->Enabled=false;
	else
		SpeedButton9->Enabled=true;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Image13Click(TObject *Sender)
{
	Panel1->BringToFront();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Image13MouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y)
{
	if(Button == mbLeft)
		{
			long SC_DRAGMOVE = 0xF012;
			ReleaseCapture();
			SendMessage(Panel1->Handle, WM_SYSCOMMAND, SC_DRAGMOVE, 0);
		}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Panel1Click(TObject *Sender)
{
	Panel1->BringToFront();
}
//---------------------------------------------------------------------------











