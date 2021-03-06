#ifndef __MAINFRAME_H__
#define __MAINFRAME_H__

#include <wx/wx.h>
#include <wx/timer.h>

/* ID of the buttons */
#define wxID_OK1 		10001
#define wxID_OK2 		10002
#define wxID_CAN 		10003
#define wxID_RUN 		10004
#define wxID_PAU 		10005

/* ID of the textctrl of PID parameters */
#define wxID_PIDKP		10006
#define wxID_PIDKI		10007
#define wxID_PIDKD		10008
#define wxID_PIDT		10009
#define wxID_PIDK		10010
#define wxID_PIDSV		10011

/* ID of the textctrl of object parameters */
#define wxID_OBJTP		10012
#define wxID_OBJL		10013
#define wxID_OBJTS		10014
#define wxID_OBJKG		10015

/* ID of the textctrl of Limit parameters */
#define wxID_LIMITMH	10016
#define wxID_LIMITML	10017

/* ID of the textctrl of Manual control value parameters */
#define wxID_MANVAL		10018

/* ID of the radiobutton of status */
#define wxID_RADMAN 	10019
#define wxID_RADAUTO	10020

/* ID of the internal timer */
#define wxID_TIMER		10021

/* ID of the current time static text */
#define wxID_SHOWTIME	10022

/* ID of curve panel */
#define wxID_CURVEPANEL	10023
#define wxID_COORDPANEL 10024



/*
 * MainFrame class declaration
 */
class MainFrame : public wxDialog
{
	DECLARE_CLASS(MainFrame)
	DECLARE_EVENT_TABLE();
public:
	/* constructor */
	MainFrame(const wxString& title);
	/* initial internal variables */
	void Init();
	/* Create windows */
	bool Create();
	/* refresh data from controls to member variables */
	void updateDataFromCtlToVariable();
	/* refresh data from member variables to controls */	
	void updateDataFromVariableToCtrl();
	/* timer event handler */	
	void OnTimer(wxTimerEvent& event);
	/* Change text context and press enter event handler */
	void OnTextEnterKp(wxCommandEvent& event);
	/* Click the Run Button event handler */
	void OnClickRun(wxCommandEvent& event);
	/* repaint event handler */
	void OnPaint(wxPaintEvent& event);
	
	/* PID  parameters */
	float m_Kp; 		/* proportion */
	float m_Ti; 		/* integration */
	float m_Td; 		/* differential */
	/* Control Period */
	float m_CtlPeriod;
	/* Gain factor  */
	float m_K;
	/* Setting Value */
	float m_SV;
	/* Time constant */
	float m_Tp;
	/* Time delay */
	float m_delay;
	/* Discrete period */
	float m_DisPeriod;
	/* Plant Gain */
	float m_Kg;
	/* Controller output limit */
	float m_MH;     	/* upper limit */
	float m_ML;     	/* lower limit */
	/* Controller output limit */
	float m_ManVal;

private:
	/* internal timer */
	wxTimer m_timer;

};





#endif


