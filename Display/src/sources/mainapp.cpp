#include "mainapp.h"
#include "mainframe.h"


DECLARE_APP(MainApp)

IMPLEMENT_APP(MainApp)


bool MainApp::OnInit()
{
	MainFrame *frame = new MainFrame(wxT("Process RealTime Control "));

	frame->Show(true);

	return true;
}