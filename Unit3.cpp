//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit3.h"
#include "Unit1.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm3 *Form3;
//---------------------------------------------------------------------------
__fastcall TForm3::TForm3(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TForm3::Button1Click(TObject *Sender)
{
Form1->ADOTable1->Edit();
		{
			if(RadioButton1->Checked==true)
				Form1->ADOTable1->FieldByName("Programm")->AsString=Edit1->Text;
			if(RadioButton2->Checked==true)
				Form1->ADOTable1->FieldByName("Programm2")->AsString=Edit1->Text;
			if(RadioButton3->Checked==true)
				Form1->ADOTable1->FieldByName("Programm3")->AsString=Edit1->Text;
		}
	Form1->ADOTable1->Post();
	Form3->Close();
}
//---------------------------------------------------------------------------
void __fastcall TForm3::Button2Click(TObject *Sender)
{
Form3->Close();
}
//---------------------------------------------------------------------------

void __fastcall TForm3::FormCreate(TObject *Sender)
{
	if((RadioButton1->Checked==false) &&
	(RadioButton2->Checked==false) &&
	(RadioButton3->Checked==false))
		Button1->Enabled=false;
}
//---------------------------------------------------------------------------

void __fastcall TForm3::RadioButton1Click(TObject *Sender)
{
	Button1->Enabled=true;
}
//---------------------------------------------------------------------------

void __fastcall TForm3::RadioButton2Click(TObject *Sender)
{
	Button1->Enabled=true;
}
//---------------------------------------------------------------------------

void __fastcall TForm3::RadioButton3Click(TObject *Sender)
{
	Button1->Enabled=true;
}
//---------------------------------------------------------------------------

