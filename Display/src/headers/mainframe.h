#ifndef __MAINFRAME_H__
#define __MAINFRAME_H__

#include <wx/wx.h>


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
	float m_Ki; 		/* integration */
	float m_Kd; 		/* differential */
	/* Gain factor  */
	float m_K;
	/* Setting Value */
	float m_SV;
	/* Time constant */
	float m_Tp;
	/* Time delay */
	float m_delay;
	/* Discrete period */
	float m_Period;
	/* Plant Gain */
	float m_Kg;
	/* Controller output limit */
	float m_MH;     	/* upper limit */
	float m_ML;     	/* lower limit */



};


#endif


