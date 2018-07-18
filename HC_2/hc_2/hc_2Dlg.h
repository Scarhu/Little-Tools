
// hc_2Dlg.h : 头文件
//

#pragma once
#include "afxwin.h"
#include "mscomm1.h"


// Chc_2Dlg 对话框
class Chc_2Dlg : public CDialogEx
{
// 构造
public:
	Chc_2Dlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_HC_2_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnEnChangeEditSend();
private:
	CString m_EditReceive;
	CString m_Editsend;
	CComboBox m_comb1;
	CComboBox m_comb2;
public:
	CMscomm1 m_mscom;
	afx_msg void OnBnClickedButtonOpen();
	afx_msg void OnBnClickedButtoSend();
	afx_msg void OnBnClickedButtonClean();
	afx_msg void OnBnClickedButtonClose();
	DECLARE_EVENTSINK_MAP()
	void OnCommMscomm1();
	afx_msg void OnEnChangeEditRev();
	CEdit m_Edit;
	afx_msg void OnBnClickedButton8();
	afx_msg void OnBnClickedButton17();
	afx_msg void OnBnClickedButtonMenu();
	afx_msg void OnBnClickedButton29();
	//afx_msg void OnBnClickedButtonHome();
	afx_msg void OnBnClickedButtonPauseRecord();
	afx_msg void OnBnClickedButtonUp();
	afx_msg void OnBnClickedButtonFormat();
//	afx_msg void OnBnClickedButtonResolution();
	afx_msg void OnBnClickedButtonMain();
	afx_msg void OnBnClickedButtonRestore();
//	afx_msg void OnBnClickedButtonUpdate();
	afx_msg void OnBnClickedButtonDown();
	afx_msg void OnBnClickedButtonLeft();
	afx_msg void OnBnClickedButtonRight();
	afx_msg void OnBnClickedButtonPrevpage();
	afx_msg void OnBnClickedButtonNextpage();
	afx_msg void OnBnClickedButtonGengralRecord();
	afx_msg void OnBnClickedButtonPauseRecord2();
	afx_msg void OnBnClickedButtonEmergencyRecord();
	afx_msg void OnBnClickedButtonGenaralBrown();
	afx_msg void OnBnClickedButtonEmergencyBrown();
	afx_msg void OnBnClickedButtonRiskBrown();
	afx_msg void OnBnClickedButtonPhotoBrown();
	afx_msg void OnBnClickedButtonExitBrown();
	afx_msg void OnBnClickedButtonCapture();
	afx_msg void OnBnClickedButtonDelfile();
	afx_msg void OnBnClickedButtonDelall();
	afx_msg void OnBnClickedButtonPlay();
	afx_msg void OnBnClickedButtonPause();
	afx_msg void OnBnClickedButtonPlayprev();
	afx_msg void OnBnClickedButtonPlaynext();
	afx_msg void OnBnClickedButtonExitplay();
	afx_msg void OnBnClickedButtonMove();
//	afx_msg void OnBnClickedButtonTapset4();
	afx_msg void OnBnClickedResolution1();
	afx_msg void OnBnClickedResolution2();
	afx_msg void OnBnClickedButtonCycleRecord1();
	afx_msg void OnBnClickedButtonCycleRecord2();
	afx_msg void OnBnClickedButtonCycleRecord3();
	afx_msg void OnBnClickedButtonMoveToEmergency();
	afx_msg void OnBnClickedButtonMicOn();
	afx_msg void OnBnClickedButtonMicOff();
	afx_msg void OnBnClickedButtonLeft2();
	int m_radio_MIC;
	afx_msg void OnBnClickedRadio1();
	afx_msg void OnBnClickedRadio2();
	afx_msg void OnBnClickedRadio4();
	int m_radio_RES;
	afx_msg void OnBnClickedRadio5();
	int m_radio_VID;
	afx_msg void OnBnClickedRadio7();
	afx_msg void OnBnClickedRadio8();
	afx_msg void OnBnClickedRadio9();
	afx_msg void OnBnClickedButton1();
	int m_radio_HEX;
	int m_radio_disp;
	afx_msg void OnBnClickedRadio10();
	afx_msg void OnBnClickedRadio11();
	afx_msg void OnBnClickedRadio12();
	afx_msg void OnBnClickedRadio13();
	afx_msg void OnBnClickedButtonTimer();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnBnClickedButtoAutoSend();
	afx_msg void OnBnClickedButtonAutosend();
	int m_Edit_Time;
	afx_msg void OnBnClickedButtonRestore2();
	afx_msg void OnBnClickedRadio14();
	afx_msg void OnBnClickedRadio15();
	afx_msg void OnBnClickedRadio16();
	
	afx_msg void OnBnClickedRadio17();
	afx_msg void OnBnClickedRadio18();
	afx_msg void OnBnClickedRadio19();
	afx_msg void OnBnClickedRadio20();
	afx_msg void OnBnClickedRadio21();
	afx_msg void OnBnClickedRadio22();

//	int m_Event_Time;
	int m_Select_File;
	afx_msg void OnBnClickedButtonRestore3();
	int m_Event_Time;
};
