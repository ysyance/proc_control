#include "mainframe.h"
#include "wx/textctrl.h"
#include "wx/stattext.h"
#include "wx/button.h"
#include "wx/radiobut.h"
#include "wx/colour.h"


/*
 * MainFrame type definition
 */	

IMPLEMENT_CLASS(MainFrame, wxDialog)

/*
 * MainFrame event table definition
 */	

BEGIN_EVENT_TABLE(MainFrame, wxDialog)
	
END_EVENT_TABLE()

/*
 * MainFrame construtors
 */	

MainFrame::MainFrame(const wxString& title)
			: wxDialog(NULL, wxID_ANY, title, wxDefaultPosition, wxDefaultSize, wxDEFAULT_DIALOG_STYLE)	
{
	this->Init();
	this->Create();
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
 }


/*
 * Windows Creation
 */	

bool MainFrame::Create()
{
	wxColour col1;
  	col1.Set(wxT("#4f5049"));

	wxBoxSizer* topSizer = new wxBoxSizer(wxHORIZONTAL);

	wxBoxSizer* settingSizer = new wxBoxSizer(wxVERTICAL);

	wxStaticBox* staticBoxPidSetting = new wxStaticBox(this, wxID_ANY, wxT("PID参数设置"));
	wxStaticBoxSizer* PidSettingStaticSizer = new wxStaticBoxSizer(staticBoxPidSetting, wxVERTICAL);

	wxGridSizer* PidSettingGridSizer = new wxGridSizer(3, 4, 0, 0);
//	SetSizer(PidSettingGridSizer);

	wxStaticText* staticTextKp = new wxStaticText(this, wxID_ANY, wxT("比例Kp"), wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT);
	wxTextCtrl* textCtlKp = new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize);
	wxStaticText* staticTextTi = new wxStaticText(this, wxID_ANY, wxT("积分Ti"), wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT);
	wxTextCtrl* textCtlTi = new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize);
	wxStaticText* staticTextTd = new wxStaticText(this, wxID_ANY, wxT("微分Td"), wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT);
	wxTextCtrl* textCtlTd = new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize);
	wxStaticText* staticTextT = new wxStaticText(this, wxID_ANY, wxT("控制周期T"), wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT);
	wxTextCtrl* textCtlT = new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize);
	wxStaticText* staticTextK = new wxStaticText(this, wxID_ANY, wxT("增益系数K"), wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT);
	wxTextCtrl* textCtlK = new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize);
	wxStaticText* staticTextSV = new wxStaticText(this, wxID_ANY, wxT("给定值SV"), wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT);
	wxTextCtrl* textCtlSV = new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize);
	
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
	wxTextCtrl* textCtlTp = new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize);
	wxStaticText* staticTextL = new wxStaticText(this, wxID_ANY, wxT("延迟L"), wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT);
	wxTextCtrl* textCtlL = new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize);
	wxStaticText* staticTextTs = new wxStaticText(this, wxID_ANY, wxT("离散周期Ts"), wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT);
	wxTextCtrl* textCtlTs = new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize);
	wxStaticText* staticTextKg = new wxStaticText(this, wxID_ANY, wxT("增益Kp"), wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT);
	wxTextCtrl* textCtlKg = new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize);
	
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
	wxTextCtrl* textCtlMH = new wxTextCtrl(subPanel1, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize);
	wxStaticText* staticTextLow = new wxStaticText(subPanel1, wxID_ANY, wxT("输出下限ML"), wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT);
	wxTextCtrl* textCtlML = new wxTextCtrl(subPanel1, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize);

	LimitGridSizer->Add(staticTextUp, 0, wxALIGN_CENTER_HORIZONTAL | wxALIGN_CENTER_VERTICAL | wxALL, 5);
	LimitGridSizer->Add(textCtlMH, 0, wxALIGN_CENTER_HORIZONTAL | wxALIGN_CENTER_VERTICAL | wxALL, 5);
	LimitGridSizer->Add(staticTextLow, 0, wxALIGN_CENTER_HORIZONTAL | wxALIGN_CENTER_VERTICAL | wxALL, 5);
	LimitGridSizer->Add(textCtlML, 0, wxALIGN_CENTER_HORIZONTAL | wxALIGN_CENTER_VERTICAL | wxALL, 5);

	staticSizerLimit->Add(LimitGridSizer, 0, wxALIGN_CENTER_HORIZONTAL | wxALIGN_CENTER_VERTICAL | wxALL, 5);

	wxStaticBox* staticBoxStatSwitch = new wxStaticBox(subPanel1, wxID_ANY, wxT("状态切换"),wxDefaultPosition,wxSize(100,80));
	wxStaticBoxSizer* staticSizerStatSwitch = new wxStaticBoxSizer(staticBoxStatSwitch, wxHORIZONTAL);

	wxRadioButton* radioManual = new wxRadioButton(subPanel1, wxID_ANY, wxT(" 手动  "), wxDefaultPosition, wxDefaultSize, wxRB_GROUP);
	wxRadioButton* radioAuto = new wxRadioButton(subPanel1, wxID_ANY, wxT(" 自动  "));
	radioAuto->SetValue(true);

	wxBoxSizer* StatusBoxSizer1 = new wxBoxSizer(wxVERTICAL);
	StatusBoxSizer1->Add(radioManual, 0, wxALIGN_CENTER_HORIZONTAL | wxALL, 5);
	StatusBoxSizer1->Add(radioAuto, 0, wxALIGN_CENTER_HORIZONTAL | wxALL, 5);

	wxTextCtrl* textCtlManualVal = new wxTextCtrl(subPanel1, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize);
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

	wxPanel* subPanelTime = new wxPanel(subPanel2, wxID_ANY, wxDefaultPosition, wxSize(80, 30));

	subPanelTime->SetBackgroundColour(col1);
	wxStaticText* staticTextTime = new wxStaticText(subPanelTime, wxID_ANY, wxT(" "), wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT);
	
	wxButton* buttonOK2 = new wxButton(subPanel2, wxID_OK2, wxT("确定"), wxDefaultPosition,wxDefaultSize);
	wxButton* buttonCancel = new wxButton(subPanel2, wxID_CAN, wxT("取消"), wxDefaultPosition,wxDefaultSize);
	wxButton* buttonRun = new wxButton(subPanel2, wxID_RUN, wxT("运行"), wxDefaultPosition,wxDefaultSize);
	wxButton* buttonPause = new wxButton(subPanel2, wxID_PAU, wxT("暂停"), wxDefaultPosition,wxDefaultSize);

	subLevelSizer2->Add(subPanelTime, 0, wxALIGN_CENTER_HORIZONTAL | wxALL, 5);
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

	wxPanel* curvePanel = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxSize(600,520));

	staticSizerCurve->Add(curvePanel, 0, wxALIGN_CENTER_HORIZONTAL | wxALL, 5);



	topSizer->Add(settingSizer, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5);
	topSizer->Add(staticSizerCurve, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5);

	this->SetSizer(topSizer);

	topSizer->Fit(this);

	topSizer->SetSizeHints(this);


	return true;
}
