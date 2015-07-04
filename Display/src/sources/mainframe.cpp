#include "mainframe.h"
#include <wx/textctrl.h>
#include <wx/stattext.h>
#include <wx/button.h>
#include <wx/radiobut.h>
#include <wx/colour.h>
#include <wx/datetime.h>
#include <wx/regex.h>



/*
 * MainFrame type definition
 */	

IMPLEMENT_CLASS(MainFrame, wxDialog)

/*
 * MainFrame event table definition
 */	

BEGIN_EVENT_TABLE(MainFrame, wxDialog)
	EVT_TIMER(wxID_TIMER, MainFrame::OnTimer)
	EVT_PAINT(MainFrame::OnPaint)
	EVT_TEXT_ENTER(wxID_PIDKP, MainFrame::OnTextEnterKp)
	EVT_BUTTON(wxID_RUN, MainFrame::OnClickRun)
END_EVENT_TABLE()

/*
 * MainFrame construtors
 */	

MainFrame::MainFrame(const wxString& title)
			: wxDialog(NULL, wxID_ANY, title, wxDefaultPosition, wxDefaultSize, wxDEFAULT_DIALOG_STYLE), m_timer(this, wxID_TIMER)
{
	/* initial internal variables */
	this->Init();
	/* Create windows */
	this->Create();
	/* refresh data from member variables to controls */
	this->updateDataFromVariableToCtrl();
	/* Start timer and time interval is 0.5s */
	m_timer.Start(500);

}

/*
 * Variables Initialization
 */	

 void MainFrame::Init()
 {
 	m_Kp = 1.6; 		/* proportion */
	m_Ti = 0.03; 		/* integration */
	m_Td = 2.0; 		/* differential */
	
	m_CtlPeriod = 5.0;	/* Control Period */
	m_K = 0.25;			/* Gain factor  */
	m_SV = 1.5;			/* Setting Value */
	
	m_Tp = 50;			/* Time constant */
	m_delay = 20;		/* Time delay */
	m_DisPeriod = 1.0;	/* Discrete period */
	m_Kg = 1.0;			/* Plant Gain */
	
	m_MH = 3.0;     	/* upper limit */
	m_ML = 0;     		/* lower limit */

 	/* initial internal timer */
//	m_timer = new wxTimer(this, wxID_TIMER);
 }


/*
 * Windows Creation
 */	

bool MainFrame::Create()
{
	wxColour col1;
  	col1.Set(wxT("#4f0049"));

	wxBoxSizer* topSizer = new wxBoxSizer(wxHORIZONTAL);

	wxBoxSizer* settingSizer = new wxBoxSizer(wxVERTICAL);

	wxStaticBox* staticBoxPidSetting = new wxStaticBox(this, wxID_ANY, wxT("PID参数设置"));
	wxStaticBoxSizer* PidSettingStaticSizer = new wxStaticBoxSizer(staticBoxPidSetting, wxVERTICAL);

	wxGridSizer* PidSettingGridSizer = new wxGridSizer(3, 4, 0, 0);
//	SetSizer(PidSettingGridSizer);

	wxStaticText* staticTextKp = new wxStaticText(this, wxID_ANY, wxT("比例Kp"), wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT);
	wxTextCtrl* textCtlKp = new wxTextCtrl(this, wxID_PIDKP, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER);
	wxStaticText* staticTextTi = new wxStaticText(this, wxID_ANY, wxT("积分Ti"), wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT);
	wxTextCtrl* textCtlTi = new wxTextCtrl(this, wxID_PIDKI, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER);
	wxStaticText* staticTextTd = new wxStaticText(this, wxID_ANY, wxT("微分Td"), wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT);
	wxTextCtrl* textCtlTd = new wxTextCtrl(this, wxID_PIDKD, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER);
	wxStaticText* staticTextT = new wxStaticText(this, wxID_ANY, wxT("控制周期T"), wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT);
	wxTextCtrl* textCtlT = new wxTextCtrl(this, wxID_PIDT, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER);
	wxStaticText* staticTextK = new wxStaticText(this, wxID_ANY, wxT("增益系数K"), wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT);
	wxTextCtrl* textCtlK = new wxTextCtrl(this, wxID_PIDK, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER);
	wxStaticText* staticTextSV = new wxStaticText(this, wxID_ANY, wxT("给定值SV"), wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT);
	wxTextCtrl* textCtlSV = new wxTextCtrl(this, wxID_PIDSV, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER);
	
	PidSettingGridSizer->Add(staticTextKp, 0, wxALIGN_CENTER_HORIZONTAL | wxALIGN_CENTER_VERTICAL | wxALL, 5);
	PidSettingGridSizer->Add(textCtlKp, 0, wxALIGN_CENTER_HORIZONTAL | wxALIGN_CENTER_VERTICAL | wxALL, 5);
	PidSettingGridSizer->Add(staticTextTi, 0, wxALIGN_CENTER_HORIZONTAL | wxALIGN_CENTER_VERTICAL | wxALL, 5);
	PidSettingGridSizer->Add(textCtlTi, 0, wxALIGN_CENTER_HORIZONTAL | wxALIGN_CENTER_VERTICAL | wxALL, 5);
	PidSettingGridSizer->Add(staticTextTd, 0, wxALIGN_CENTER_HORIZONTAL | wxALIGN_CENTER_VERTICAL | wxALL, 5);
	PidSettingGridSizer->Add(textCtlTd, 0, wxALIGN_CENTER_HORIZONTAL | wxALIGN_CENTER_VERTICAL | wxALL, 5);
	PidSettingGridSizer->Add(staticTextT, 0, wxALIGN_CENTER_HORIZONTAL | wxALIGN_CENTER_VERTICAL | wxALL, 5);
	PidSettingGridSizer->Add(textCtlT, 0, wxALIGN_CENTER_HORIZONTAL | wxALIGN_CENTER_VERTICAL | wxALL, 5);
	PidSettingGridSizer->Add(staticTextK, 0, wxALIGN_CENTER_HORIZONTAL | wxALIGN_CENTER_VERTICAL | wxALL, 5);
	PidSettingGridSizer->Add(textCtlK, 0, wxALIGN_CENTER_HORIZONTAL | wxALIGN_CENTER_VERTICAL | wxALL, 5);
	PidSettingGridSizer->Add(staticTextSV, 0, wxALIGN_CENTER_HORIZONTAL | wxALIGN_CENTER_VERTICAL | wxALL, 5);
	PidSettingGridSizer->Add(textCtlSV, 0, wxALIGN_CENTER_HORIZONTAL | wxALIGN_CENTER_VERTICAL | wxALL, 5);

	PidSettingStaticSizer->Add(PidSettingGridSizer, 0, wxALIGN_CENTER_HORIZONTAL | wxALIGN_CENTER_VERTICAL | wxALL, 5);

    wxStaticBox* staticBoxObjetting = new wxStaticBox(this, wxID_ANY, wxT("对象参数设置"));
	wxStaticBoxSizer* ObjettingStaticSizer = new wxStaticBoxSizer(staticBoxObjetting, wxVERTICAL);

	wxGridSizer* ObjSettingGridSizer = new wxGridSizer(2, 4, 0, 0);
//	SetSizer(ObjSettingGridSizer);

	wxStaticText* staticTextTp = new wxStaticText(this, wxID_ANY, wxT("时间常数Tp"), wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT);
	wxTextCtrl* textCtlTp = new wxTextCtrl(this, wxID_OBJTP, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER);
	wxStaticText* staticTextL = new wxStaticText(this, wxID_ANY, wxT("延迟L"), wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT);
	wxTextCtrl* textCtlL = new wxTextCtrl(this, wxID_OBJL, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER);
	wxStaticText* staticTextTs = new wxStaticText(this, wxID_ANY, wxT("离散周期Ts"), wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT);
	wxTextCtrl* textCtlTs = new wxTextCtrl(this, wxID_OBJTS, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER);
	wxStaticText* staticTextKg = new wxStaticText(this, wxID_ANY, wxT("增益Kp"), wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT);
	wxTextCtrl* textCtlKg = new wxTextCtrl(this, wxID_OBJKG, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER);
	
	ObjSettingGridSizer->Add(staticTextTp, 0, wxALIGN_CENTER_HORIZONTAL | wxALIGN_CENTER_VERTICAL | wxALL, 5);
	ObjSettingGridSizer->Add(textCtlTp, 0, wxALIGN_CENTER_HORIZONTAL | wxALIGN_CENTER_VERTICAL | wxALL, 5);
	ObjSettingGridSizer->Add(staticTextL, 0, wxALIGN_CENTER_HORIZONTAL | wxALIGN_CENTER_VERTICAL | wxALL, 5);
	ObjSettingGridSizer->Add(textCtlL, 0, wxALIGN_CENTER_HORIZONTAL | wxALIGN_CENTER_VERTICAL | wxALL, 5);
	ObjSettingGridSizer->Add(staticTextTs, 0, wxALIGN_CENTER_HORIZONTAL | wxALIGN_CENTER_VERTICAL | wxALL, 5);
	ObjSettingGridSizer->Add(textCtlTs, 0, wxALIGN_CENTER_HORIZONTAL | wxALIGN_CENTER_VERTICAL | wxALL, 5);
	ObjSettingGridSizer->Add(staticTextKg, 0, wxALIGN_CENTER_HORIZONTAL | wxALIGN_CENTER_VERTICAL | wxALL, 5);
	ObjSettingGridSizer->Add(textCtlKg, 0, wxALIGN_CENTER_HORIZONTAL | wxALIGN_CENTER_VERTICAL | wxALL, 5);

	ObjettingStaticSizer->Add(ObjSettingGridSizer, 0, wxALIGN_CENTER_HORIZONTAL | wxALIGN_CENTER_VERTICAL | wxALL, 5);

	wxBoxSizer* subLevelSizer = new wxBoxSizer(wxHORIZONTAL);

	wxBoxSizer* subLevelSizer1 = new wxBoxSizer(wxVERTICAL);

	wxPanel* subPanel1 = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxSize(200, 250));

	wxStaticBox* staticBoxLimit = new wxStaticBox(subPanel1, wxID_ANY, wxT("限幅处理"),wxDefaultPosition,wxSize(100,80));
	wxStaticBoxSizer* staticSizerLimit = new wxStaticBoxSizer(staticBoxLimit, wxVERTICAL);

	wxGridSizer* LimitGridSizer = new wxGridSizer(2, 2, 0, 0);
//	SetSizer(LimitGridSizer);

	wxStaticText* staticTextUp = new wxStaticText(subPanel1, wxID_ANY, wxT("输出上限MH"), wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT);
	wxTextCtrl* textCtlMH = new wxTextCtrl(subPanel1, wxID_LIMITMH, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER);
	wxStaticText* staticTextLow = new wxStaticText(subPanel1, wxID_ANY, wxT("输出下限ML"), wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT);
	wxTextCtrl* textCtlML = new wxTextCtrl(subPanel1, wxID_LIMITML, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER);

	LimitGridSizer->Add(staticTextUp, 0, wxALIGN_CENTER_HORIZONTAL | wxALIGN_CENTER_VERTICAL | wxALL, 5);
	LimitGridSizer->Add(textCtlMH, 0, wxALIGN_CENTER_HORIZONTAL | wxALIGN_CENTER_VERTICAL | wxALL, 5);
	LimitGridSizer->Add(staticTextLow, 0, wxALIGN_CENTER_HORIZONTAL | wxALIGN_CENTER_VERTICAL | wxALL, 5);
	LimitGridSizer->Add(textCtlML, 0, wxALIGN_CENTER_HORIZONTAL | wxALIGN_CENTER_VERTICAL | wxALL, 5);

	staticSizerLimit->Add(LimitGridSizer, 0, wxALIGN_CENTER_HORIZONTAL | wxALIGN_CENTER_VERTICAL | wxALL, 5);

	wxStaticBox* staticBoxStatSwitch = new wxStaticBox(subPanel1, wxID_ANY, wxT("状态切换"),wxDefaultPosition,wxSize(100,80));
	wxStaticBoxSizer* staticSizerStatSwitch = new wxStaticBoxSizer(staticBoxStatSwitch, wxHORIZONTAL);

	wxRadioButton* radioManual = new wxRadioButton(subPanel1, wxID_RADMAN, wxT(" 手动  "), wxDefaultPosition, wxDefaultSize, wxRB_GROUP);
	wxRadioButton* radioAuto = new wxRadioButton(subPanel1, wxID_RADAUTO, wxT(" 自动  "));
	radioAuto->SetValue(true);

	wxBoxSizer* StatusBoxSizer1 = new wxBoxSizer(wxVERTICAL);
	StatusBoxSizer1->Add(radioManual, 0, wxALIGN_CENTER_HORIZONTAL | wxALL, 5);
	StatusBoxSizer1->Add(radioAuto, 0, wxALIGN_CENTER_HORIZONTAL | wxALL, 5);

	wxTextCtrl* textCtlManualVal = new wxTextCtrl(subPanel1, wxID_MANVAL, wxEmptyString, wxDefaultPosition, wxDefaultSize);
	wxButton* buttonOK1 = new wxButton(subPanel1, wxID_OK1, wxT("确定"), wxDefaultPosition,wxDefaultSize);
	wxBoxSizer* StatusBoxSizer2 = new wxBoxSizer(wxVERTICAL);
	StatusBoxSizer2->Add(textCtlManualVal, 0, wxALIGN_CENTER_HORIZONTAL | wxALL, 5);
	StatusBoxSizer2->Add(buttonOK1, 0, wxALIGN_CENTER_HORIZONTAL | wxALL, 5);

	staticSizerStatSwitch->Add(StatusBoxSizer1, 0, wxALIGN_CENTER_HORIZONTAL | wxALIGN_CENTER_VERTICAL | wxALL, 5);
	staticSizerStatSwitch->Add(StatusBoxSizer2, 0, wxALIGN_CENTER_HORIZONTAL | wxALIGN_CENTER_VERTICAL | wxALL, 5);

	subLevelSizer1->Add(staticSizerLimit, 0, wxALIGN_LEFT | wxALL, 5);
	subLevelSizer1->Add(staticSizerStatSwitch, 0, wxALIGN_LEFT | wxALL, 5);

	subPanel1->SetSizer(subLevelSizer1);

	wxBoxSizer* subLevelSizer2 = new wxBoxSizer(wxVERTICAL);

	wxPanel* subPanel2 = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxSize(200, 250));

//	wxPanel* subPanelTime = new wxPanel(subPanel2, wxID_ANY, wxDefaultPosition, wxSize(80, 30));

//	subPanelTime->SetBackgroundColour(col1);
//	wxStaticText* staticTextTime = new wxStaticText(subPanelTime, wxID_SHOWTIME, wxT("time "), wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT);
	
	wxTextCtrl* textTime = new wxTextCtrl(subPanel2, wxID_SHOWTIME, wxEmptyString, wxDefaultPosition, wxDefaultSize); 
	wxButton* buttonOK2 = new wxButton(subPanel2, wxID_OK2, wxT("确定"), wxDefaultPosition,wxDefaultSize);
	wxButton* buttonCancel = new wxButton(subPanel2, wxID_CAN, wxT("取消"), wxDefaultPosition,wxDefaultSize);
	wxButton* buttonRun = new wxButton(subPanel2, wxID_RUN, wxT("运行"), wxDefaultPosition,wxDefaultSize);
	wxButton* buttonPause = new wxButton(subPanel2, wxID_PAU, wxT("暂停"), wxDefaultPosition,wxDefaultSize);

	subLevelSizer2->Add(textTime, 0, wxALIGN_CENTER_HORIZONTAL | wxALL, 5);
	subLevelSizer2->Add(buttonOK2, 0, wxALIGN_CENTER_HORIZONTAL | wxALL, 5);
	subLevelSizer2->Add(buttonCancel, 0, wxALIGN_CENTER_HORIZONTAL | wxALL, 5);
	subLevelSizer2->AddStretchSpacer(1);
	subLevelSizer2->Add(buttonRun, 0, wxALIGN_CENTER_HORIZONTAL | wxALL, 5);
	subLevelSizer2->Add(buttonPause, 0, wxALIGN_CENTER_HORIZONTAL | wxALL, 5);

	subPanel2->SetSizer(subLevelSizer2);


	subLevelSizer->Add(subPanel1,  0, wxALIGN_LEFT | wxALL, 5);
	subLevelSizer->Add(subPanel2,  0, wxALIGN_RIGHT | wxALL, 5);

	settingSizer->Add(PidSettingStaticSizer, 0, wxALIGN_CENTER_HORIZONTAL | wxALL, 5);
	settingSizer->Add(ObjettingStaticSizer, 0, wxALIGN_CENTER_HORIZONTAL | wxALL, 5);
	settingSizer->Add(subLevelSizer, 0, wxALIGN_CENTER_HORIZONTAL | wxALL, 5);


	wxStaticBox* staticBoxCurve = new wxStaticBox(this, wxID_ANY, wxT("曲线显示"));
	wxStaticBoxSizer* staticSizerCurve = new wxStaticBoxSizer(staticBoxCurve, wxVERTICAL);

	wxPanel* curvePanel = new wxPanel(this, wxID_CURVEPANEL, wxDefaultPosition, wxSize(630,520));

	staticSizerCurve->Add(curvePanel, 0, wxALIGN_CENTER_HORIZONTAL | wxALL, 5);

	wxStaticText* LabelSV = new wxStaticText(curvePanel, wxID_ANY, wxT(" 给定值SV"), wxPoint(80, 10), wxDefaultSize, wxALIGN_LEFT);
	wxStaticText* LabelPV = new wxStaticText(curvePanel, wxID_ANY, wxT(" 被控量PV"), wxPoint(260, 10), wxDefaultSize, wxALIGN_LEFT);
	wxStaticText* LabelMV = new wxStaticText(curvePanel, wxID_ANY, wxT(" 控制量MV"), wxPoint(440, 10), wxDefaultSize, wxALIGN_LEFT);
	

	wxPanel* coordPanel = new wxPanel(curvePanel, wxID_COORDPANEL, wxPoint(15, 50), wxSize(600, 455));
	coordPanel->SetBackgroundColour(*wxLIGHT_GREY);



	topSizer->Add(settingSizer, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5);
	topSizer->Add(staticSizerCurve, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5);

	this->SetSizer(topSizer);

	topSizer->Fit(this);

	topSizer->SetSizeHints(this);

	return true;
}


/*
 * @name : updateDataFromVariableToCtrl
 * @para : none
 * @berif: refresh data from member variables to controls
 */	

void MainFrame::updateDataFromVariableToCtrl()
{
	wxString str;		/* temp variable */

	/* refresh PID parameters from member variables to controls */
	wxTextCtrl* textCtlKp = (wxTextCtrl*)FindWindow(wxID_PIDKP);
	textCtlKp->SetValue(str.Format("%.2f",m_Kp));
	wxTextCtrl* textCtlTi = (wxTextCtrl*)FindWindow(wxID_PIDKI);
	textCtlTi->SetValue(str.Format("%.2f",m_Ti));
	wxTextCtrl* textCtlTd = (wxTextCtrl*)FindWindow(wxID_PIDKD);
	textCtlTd->SetValue(str.Format("%.2f",m_Td));
	wxTextCtrl* textCtlT = (wxTextCtrl*)FindWindow(wxID_PIDT);
	textCtlT->SetValue(str.Format("%.2f",m_CtlPeriod));
	wxTextCtrl* textCtlK = (wxTextCtrl*)FindWindow(wxID_PIDK);
	textCtlK->SetValue(str.Format("%.2f",m_K));
	wxTextCtrl* textCtlSV = (wxTextCtrl*)FindWindow(wxID_PIDSV);
	textCtlSV->SetValue(str.Format("%.2f",m_SV));

	/* refresh object parameters from member variables to controls */
	wxTextCtrl* textCtlTp = (wxTextCtrl*)FindWindow(wxID_OBJTP);
	textCtlTp->SetValue(str.Format("%.2f",m_Tp));
	wxTextCtrl* textCtlL = (wxTextCtrl*)FindWindow(wxID_OBJL);
	textCtlL->SetValue(str.Format("%.2f",m_delay));
	wxTextCtrl* textCtlTs = (wxTextCtrl*)FindWindow(wxID_OBJTS);
	textCtlTs->SetValue(str.Format("%.2f",m_DisPeriod));
	wxTextCtrl* textCtlKg = (wxTextCtrl*)FindWindow(wxID_OBJKG);
	textCtlKg->SetValue(str.Format("%.2f",m_Kg));

	/* refresh limit parameters from member variables to controls */
	wxTextCtrl* textCtlMH = (wxTextCtrl*)FindWindow(wxID_LIMITMH);
	textCtlMH->SetValue(str.Format("%.2f",m_MH));
	wxTextCtrl* textCtlML = (wxTextCtrl*)FindWindow(wxID_LIMITML);
	textCtlML->SetValue(str.Format("%.2f",m_ML));


}

/*
 * @name : updateDataFromCtlToVariable
 * @para : none
 * @berif: refresh data from controls to member variables
 */

void MainFrame::updateDataFromCtlToVariable()
{
	/* refresh PID parameters from controls to member variables */
	wxTextCtrl* textCtlKp = (wxTextCtrl*)FindWindow(wxID_PIDKP);
	m_Kp = wxAtof(textCtlKp->GetValue());
	wxTextCtrl* textCtlTi = (wxTextCtrl*)FindWindow(wxID_PIDKI);
	m_Ti = wxAtof(textCtlTi->GetValue());
	wxTextCtrl* textCtlTd = (wxTextCtrl*)FindWindow(wxID_PIDKD);
	m_Td = wxAtof(textCtlTd->GetValue());
	wxTextCtrl* textCtlT = (wxTextCtrl*)FindWindow(wxID_PIDT);
	m_CtlPeriod = wxAtof(textCtlT->GetValue());
	wxTextCtrl* textCtlK = (wxTextCtrl*)FindWindow(wxID_PIDK);
	m_K = wxAtof(textCtlK->GetValue());
	wxTextCtrl* textCtlSV = (wxTextCtrl*)FindWindow(wxID_PIDSV);
	m_SV = wxAtof(textCtlSV->GetValue());

	/* refresh object parameters from controls to member variables */
	wxTextCtrl* textCtlTp = (wxTextCtrl*)FindWindow(wxID_OBJTP);
	m_Tp = wxAtof(textCtlTp->GetValue());
	wxTextCtrl* textCtlL = (wxTextCtrl*)FindWindow(wxID_OBJL);
	m_delay = wxAtof(textCtlL->GetValue());
	wxTextCtrl* textCtlTs = (wxTextCtrl*)FindWindow(wxID_OBJTS);
	m_DisPeriod = wxAtof(textCtlTs->GetValue());
	wxTextCtrl* textCtlKg = (wxTextCtrl*)FindWindow(wxID_OBJKG);
	m_Kg = wxAtof(textCtlKg->GetValue());

	/* refresh limit parameters from controls to member variables */
	wxTextCtrl* textCtlMH = (wxTextCtrl*)FindWindow(wxID_LIMITMH);
	m_MH = wxAtof(textCtlMH->GetValue());
	wxTextCtrl* textCtlML = (wxTextCtrl*)FindWindow(wxID_LIMITML);
	m_ML = wxAtof(textCtlML->GetValue());
}


/*
 * @name : OnTimer
 * @para : wxTimerEvent
 * @berif: m_timer event handler
 */

void MainFrame::OnTimer(wxTimerEvent& event)
{
	wxDateTime now = wxDateTime::Now();
	wxTextCtrl* textTime = (wxTextCtrl*)FindWindow(wxID_SHOWTIME);
	textTime->SetValue(now.Format(wxT("%X")));
}

/*
 * @name : OnTextEnterKp
 * @para : wxCommandEvent
 * @berif: Change text context and press enter event handler 
 */

void MainFrame::OnTextEnterKp(wxCommandEvent& event)
{
//	wxString str = ""
/*	wxRegEx reDigital = wxT("^[+-]?([0-9]*[:.:]?[0-9]+|[0-9]+[:.:]?[0-9]*)$");
	wxTextCtrl* textCtlKp = (wxTextCtrl*)FindWindow(wxID_PIDKP);
	wxString text = textCtlKp->GetValue();
	if(reDigital.Matches(text))
	{
		m_Kp = wxAtof(text);
	}
	else
	{
		if(wxYES == wxMessageBox(wxT("illegal input, please input numbers"), wxT("Input Error"), wxYES | wxICON_INFORMATION, this))
		{
			
		}
	}*/
	wxMessageBox(wxT("illegal input, please input numbers"), wxT("Input Error"), wxOK | wxICON_INFORMATION, this);
	
}

/*
 * @name : OnClickRun
 * @para : wxCommandEvent
 * @berif: Click the Run Button event handler
 */

void MainFrame::OnClickRun(wxCommandEvent& event)
{
	wxPanel* coordPanel = (wxPanel*)FindWindow(wxID_COORDPANEL);
	wxClientDC dc(coordPanel);

	wxPen pen(*wxBLACK, 2);
	dc.SetPen(pen);
	/* Draw coorderate */
	wxCoord x1 = 20, y1 = 435;
  	wxCoord x2 = 580, y2 = 435;
  	wxCoord x3 = 20, y3 = 20;
  	/* Draw x axis */
  	dc.DrawLine(x1-20, y1 , x2, y2);
  	dc.DrawLine(wxPoint(580, 435),wxPoint(570, 430));
  	dc.DrawLine(wxPoint(580, 435),wxPoint(570, 440));
  	/* Draw y axis */
  	dc.DrawLine(x1, y1+15, x3, y3);
  	dc.DrawLine(wxPoint(20, 20),wxPoint(15, 30));
  	dc.DrawLine(wxPoint(20, 20),wxPoint(25, 30));

  	pen.SetWidth(1);
  	dc.SetPen(pen);
  	/* Draw Grid */
  	for(int i=1; i<=20; i++)
  		dc.DrawLine(x1, y1-20*i , x2, y2-20*i);
  	for(int i=1; i<=27; i++)
  		dc.DrawLine(x1+20*i, y1 , x3+20*i, y3);

  	wxStaticText* LabelOrigin = new wxStaticText(coordPanel, wxID_ANY, wxT("0"), wxPoint(23, 438), wxDefaultSize, wxALIGN_LEFT);
  	wxStaticText* LabelX = new wxStaticText(coordPanel, wxID_ANY, wxT("t"), wxPoint(580, 438), wxDefaultSize, wxALIGN_LEFT);
  	wxStaticText* LabelY = new wxStaticText(coordPanel, wxID_ANY, wxT("V"), wxPoint(0, 25), wxDefaultSize, wxALIGN_LEFT);

}


/*
 * @name : OnPaint
 * @para : wxPaintEvent
 * @berif: repaint event handler
 */

void MainFrame::OnPaint(wxPaintEvent& event)
{
	wxPanel* curvePanel = (wxPanel*)FindWindow(wxID_CURVEPANEL);
  	wxClientDC dc1(curvePanel);

	wxPen pen1(*wxGREEN, 2);
	dc1.SetPen(pen1);
	dc1.DrawLine(wxPoint(40, 20),wxPoint(70, 20));
	pen1.SetColour(*wxBLUE);
	dc1.SetPen(pen1);
	dc1.DrawLine(wxPoint(220, 20),wxPoint(250, 20));
	pen1.SetColour(*wxRED);
	dc1.SetPen(pen1);
	dc1.DrawLine(wxPoint(400, 20),wxPoint(430, 20));
}