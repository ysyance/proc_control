#ifndef __MAINFRAME_H__
#define __MAINFRAME_H__

#include <wx/wx.h>


#define wxID_OK1 	10001
#define wxID_OK2 	10002
#define wxID_CAN 	10003
#define wxID_RUN 	10004
#define wxID_PAU 	10005

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



};





#endif


