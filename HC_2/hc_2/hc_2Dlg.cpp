
// hc_2Dlg.cpp : 实现文件
#include <iostream>
#include <string>
#include "stdafx.h"
#include "hc_2.h"
#include "hc_2Dlg.h"
#include "afxdialogex.h"
#include <stdio.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif
using namespace std;

char pre_cmd[12];
char nex_cmd[12];
static int cmd=0x00;
static int P=0;
/*
//添加校验位判断函数
long int check(char *str)
{
    unsigned int  i, j;
    long int ucRlst = 0;
	//unsigned char b[6]={0xA1,0x06,0x10,0x40,0x00,0};
	char *pucData=str;
	unsigned int uiLen=11;

    for (i = 0; i < uiLen; i++)	{
        for (j = 0; j < 8; j++) {
            ucRlst <<= 1;
            ucRlst ^= ((((pucData[i] << j) ^ ucRlst) & 0x80) ? 0x9 : 0);
        }
    }
	ucRlst = ucRlst & 0x7F;
    return ucRlst;				
}
*/
///////////////////////////////////////////////////////////////////////////////////
/////////////////字符串转化成16进制数//////////////////////////
///////////////////////////////////////////////////////////////////////////////////
char ConvertHexChar(char ch) 
{
	if((ch>='0')&&(ch<='9'))
		return ch-0x30;
	else if((ch>='A')&&(ch<='F'))
		return ch-'A'+10;
	else if((ch>='a')&&(ch<='f'))
		return ch-'a'+10;
	else 
		return (-1);
}
 

int String2Hex(CString str, CByteArray &senddata)
{
	int hexdata,lowhexdata;
	int hexdatalen=0;
	int len=str.GetLength();
	senddata.SetSize(len);
	for(int i=0;i<len;)
	{
		char lstr,hstr=str[i];
		if(hstr==' ')
		{
			i++;
			continue;
		}
		i++;
		if(i>=len)
			break;
		lstr=str[i];		
		hexdata=ConvertHexChar(hstr);
		lowhexdata=ConvertHexChar(lstr);

		if((hexdata==16)||(lowhexdata==16))
			break;
		else 
			hexdata=hexdata*16+lowhexdata;
		i++;
		senddata[hexdatalen]=(char)hexdata;
		hexdatalen++;

	}
	senddata.SetSize(hexdatalen);
	return hexdatalen;
}



/////////////////////////////////////////////////////////////////////////////

// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnTimer(UINT_PTR nIDEvent);
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
//	ON_WM_TIMER()
END_MESSAGE_MAP()


// Chc_2Dlg 对话框




Chc_2Dlg::Chc_2Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(Chc_2Dlg::IDD, pParent)
	, m_EditReceive(_T(""))
	, m_Editsend(_T(""))
	, m_radio_MIC(0)
	, m_radio_RES(0)
	, m_radio_VID(0)
	, m_radio_HEX(0)
	, m_radio_disp(0)
	, m_Edit_Time(0)
	, m_Select_File(0)
	, m_Event_Time(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void Chc_2Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_Rev, m_EditReceive);
	DDX_Text(pDX, IDC_EDIT_Send, m_Editsend);
	DDX_Control(pDX, IDC_COMBO2, m_comb1);
	DDX_Control(pDX, IDC_COMBO3, m_comb2);
	DDX_Control(pDX, IDC_MSCOMM1, m_mscom);
	DDX_Control(pDX, IDC_EDIT_Rev, m_Edit);
	DDX_Radio(pDX, IDC_RADIO1, m_radio_MIC);
	DDX_Radio(pDX, IDC_RADIO4, m_radio_RES);
	DDX_Radio(pDX, IDC_RADIO7, m_radio_VID);
	DDX_Radio(pDX, IDC_RADIO10, m_radio_HEX);
	DDX_Radio(pDX, IDC_RADIO12, m_radio_disp);
	DDX_Text(pDX, IDC_EDIT_TIME, m_Edit_Time);
	//  DDX_Radio(pDX, IDC_RADIO14, m_Event_Time);
	DDX_Radio(pDX, IDC_RADIO17, m_Select_File);
	DDX_Radio(pDX, IDC_RADIO14, m_Event_Time);
}

BEGIN_MESSAGE_MAP(Chc_2Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_OPEN, &Chc_2Dlg::OnBnClickedButtonOpen)
	ON_BN_CLICKED(IDC_BUTTO_SEND, &Chc_2Dlg::OnBnClickedButtoSend)
	ON_BN_CLICKED(IDC_BUTTON_CLEAN, &Chc_2Dlg::OnBnClickedButtonClean)
	ON_BN_CLICKED(IDC_BUTTON_CLOSE, &Chc_2Dlg::OnBnClickedButtonClose)
	ON_EN_CHANGE(IDC_EDIT_Rev, &Chc_2Dlg::OnEnChangeEditRev)
	ON_BN_CLICKED(IDC_BUTTON_MENU, &Chc_2Dlg::OnBnClickedButtonMenu)
	ON_BN_CLICKED(IDC_BUTTON_UP, &Chc_2Dlg::OnBnClickedButtonUp)
	ON_BN_CLICKED(IDC_BUTTON_FORMAT, &Chc_2Dlg::OnBnClickedButtonFormat)

	//ON_BN_CLICKED(IDC_BUTTON_RESOLUTION, &Chc_2Dlg::OnBnClickedButtonResolution)
	ON_BN_CLICKED(IDC_BUTTON_MAIN, &Chc_2Dlg::OnBnClickedButtonMain)
	ON_BN_CLICKED(IDC_BUTTON_RESTORE, &Chc_2Dlg::OnBnClickedButtonRestore)
	//ON_BN_CLICKED(IDC_BUTTON_UPDATE, &Chc_2Dlg::OnBnClickedButtonUpdate)
	ON_BN_CLICKED(IDC_BUTTON_DOWN, &Chc_2Dlg::OnBnClickedButtonDown)
	ON_BN_CLICKED(IDC_BUTTON_RIGHT, &Chc_2Dlg::OnBnClickedButtonRight)

	ON_BN_CLICKED(IDC_BUTTON_PREVPAGE, &Chc_2Dlg::OnBnClickedButtonPrevpage)
	ON_BN_CLICKED(IDC_BUTTON_NEXTPAGE, &Chc_2Dlg::OnBnClickedButtonNextpage)
	ON_BN_CLICKED(IDC_BUTTON_GENGRAL_RECORD, &Chc_2Dlg::OnBnClickedButtonGengralRecord)
	ON_BN_CLICKED(IDC_BUTTON_PAUSE_RECORD_2, &Chc_2Dlg::OnBnClickedButtonPauseRecord2)
	ON_BN_CLICKED(IDC_BUTTON_EMERGENCY_RECORD, &Chc_2Dlg::OnBnClickedButtonEmergencyRecord)
	ON_BN_CLICKED(IDC_BUTTON_GENARAL_BROWN, &Chc_2Dlg::OnBnClickedButtonGenaralBrown)
	ON_BN_CLICKED(IDC_BUTTON_EMERGENCY_BROWN, &Chc_2Dlg::OnBnClickedButtonEmergencyBrown)
	ON_BN_CLICKED(IDC_BUTTON_RISK_BROWN, &Chc_2Dlg::OnBnClickedButtonRiskBrown)
	ON_BN_CLICKED(IDC_BUTTON_PHOTO_BROWN, &Chc_2Dlg::OnBnClickedButtonPhotoBrown)
	ON_BN_CLICKED(IDC_BUTTON_EXIT_BROWN, &Chc_2Dlg::OnBnClickedButtonExitBrown)
	ON_BN_CLICKED(IDC_BUTTON_CAPTURE, &Chc_2Dlg::OnBnClickedButtonCapture)
	ON_BN_CLICKED(IDC_BUTTON_DELFILE, &Chc_2Dlg::OnBnClickedButtonDelfile)
	ON_BN_CLICKED(IDC_BUTTON_DELALL, &Chc_2Dlg::OnBnClickedButtonDelall)
	ON_BN_CLICKED(IDC_BUTTON_PLAY, &Chc_2Dlg::OnBnClickedButtonPlay)
	ON_BN_CLICKED(IDC_BUTTON_PAUSE, &Chc_2Dlg::OnBnClickedButtonPause)
	ON_BN_CLICKED(IDC_BUTTON_PLAYPREV, &Chc_2Dlg::OnBnClickedButtonPlayprev)
	ON_BN_CLICKED(IDC_BUTTON_PLAYNEXT, &Chc_2Dlg::OnBnClickedButtonPlaynext)
	ON_BN_CLICKED(IDC_BUTTON_EXITPLAY, &Chc_2Dlg::OnBnClickedButtonExitplay)
	ON_BN_CLICKED(IDC_RESOLUTION_2, &Chc_2Dlg::OnBnClickedResolution2)
	ON_BN_CLICKED(IDC_BUTTON_CYCLE_RECORD_1, &Chc_2Dlg::OnBnClickedButtonCycleRecord1)

	ON_BN_CLICKED(IDC_BUTTON_MOVE_TO_EMERGENCY, &Chc_2Dlg::OnBnClickedButtonMoveToEmergency)
	ON_BN_CLICKED(IDC_BUTTON_LEFT_2, &Chc_2Dlg::OnBnClickedButtonLeft2)
	ON_BN_CLICKED(IDC_RADIO1, &Chc_2Dlg::OnBnClickedRadio1)
	ON_BN_CLICKED(IDC_RADIO2, &Chc_2Dlg::OnBnClickedRadio2)
	ON_BN_CLICKED(IDC_RADIO4, &Chc_2Dlg::OnBnClickedRadio4)
	ON_BN_CLICKED(IDC_RADIO5, &Chc_2Dlg::OnBnClickedRadio5)
	ON_BN_CLICKED(IDC_RADIO7, &Chc_2Dlg::OnBnClickedRadio7)
	ON_BN_CLICKED(IDC_RADIO8, &Chc_2Dlg::OnBnClickedRadio8)
	ON_BN_CLICKED(IDC_RADIO9, &Chc_2Dlg::OnBnClickedRadio9)
	ON_BN_CLICKED(IDC_RADIO10, &Chc_2Dlg::OnBnClickedRadio10)
	ON_BN_CLICKED(IDC_RADIO11, &Chc_2Dlg::OnBnClickedRadio11)
	ON_BN_CLICKED(IDC_RADIO12, &Chc_2Dlg::OnBnClickedRadio12)
	ON_BN_CLICKED(IDC_RADIO13, &Chc_2Dlg::OnBnClickedRadio13)
	//ON_BN_CLICKED(IDC_BUTTON_TIMER, &Chc_2Dlg::OnBnClickedButtonTimer)
	ON_WM_TIMER()
	//ON_BN_CLICKED(IDC_BUTTO_AUTO_SEND, &Chc_2Dlg::OnBnClickedButtoAutoSend)
	ON_BN_CLICKED(IDC_BUTTON_AUTOSEND, &Chc_2Dlg::OnBnClickedButtonAutosend)
	ON_BN_CLICKED(IDC_BUTTON_RESTORE2, &Chc_2Dlg::OnBnClickedButtonRestore2)
	ON_BN_CLICKED(IDC_RADIO14, &Chc_2Dlg::OnBnClickedRadio14)
	ON_BN_CLICKED(IDC_RADIO15, &Chc_2Dlg::OnBnClickedRadio15)
	ON_BN_CLICKED(IDC_RADIO16, &Chc_2Dlg::OnBnClickedRadio16)
	ON_BN_CLICKED(IDC_RADIO17, &Chc_2Dlg::OnBnClickedRadio17)
	ON_BN_CLICKED(IDC_RADIO18, &Chc_2Dlg::OnBnClickedRadio18)
	ON_BN_CLICKED(IDC_RADIO19, &Chc_2Dlg::OnBnClickedRadio19)
	ON_BN_CLICKED(IDC_RADIO20, &Chc_2Dlg::OnBnClickedRadio20)
	ON_BN_CLICKED(IDC_RADIO21, &Chc_2Dlg::OnBnClickedRadio21)
	ON_BN_CLICKED(IDC_RADIO22, &Chc_2Dlg::OnBnClickedRadio22)
	ON_BN_CLICKED(IDC_BUTTON_RESTORE3, &Chc_2Dlg::OnBnClickedButtonRestore3)
END_MESSAGE_MAP()


// Chc_2Dlg 消息处理程序

BOOL Chc_2Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	// 串口选择组合框
	CString str;
	int i;
	for(i=0;i<64;i++)
	{
		str.Format(_T("com %d"),i+1);
		m_comb1.InsertString(i,str);
	}
	m_comb1.SetCurSel(0);//预置COM口

	//波特率选择组合框 
	CString str1[]={_T("300"),_T("600"),_T("1200"),_T("2400"),_T("4800"),_T("9600"),_T("19200"),_T("38400"),_T("43000"),_T("56000"),_T("57600"),_T("115200")};
	for(int i=0;i<12;i++)
	{
		int judge_tf=m_comb2.AddString(str1[i]);
		if((judge_tf==CB_ERR)||(judge_tf==CB_ERRSPACE))
			MessageBox(_T("build baud error!"));
	}
	m_comb2.SetCurSel(5);//预置波特率为"9600"
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void Chc_2Dlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void Chc_2Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR Chc_2Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void Chc_2Dlg::OnBnClickedButtonOpen()
{
	// TODO: 在此添加控件通知处理程序代码
	CString str,str1,str2,n;         //定义字符串
	GetDlgItemText(IDC_BUTTON_OPEN,str);
	CWnd *h1,*h2;
	h1=GetDlgItem(IDC_BUTTON_OPEN);   //指向控件的caption
	h2=GetDlgItem(IDC_BUTTON_AUTOSEND);   //指向控件的caption
	if(!m_mscom.get_PortOpen())
	{
		m_comb2.GetLBText(m_comb2.GetCurSel(),str1);//取得所选的字符串，并存放在str1里面
		str1=str1+','+'e'+','+'8'+','+'1';    //这句话很关键

		m_mscom.put_CommPort((m_comb1.GetCurSel()+1)); //选择串口
		m_mscom.put_InputMode(1);   //设置输入方式为二进制方式
		m_mscom.put_Settings(str1);  //波特率为（波特率组Á合框）偶校验，8数据位，1个停止位
		m_mscom.put_InputLen(1024);  //设置当前接收区数据长度为1024
		m_mscom.put_RThreshold(1);   //缓冲区一个字符引发事件
		m_mscom.put_RTSEnable(1);    //设置RT允许

		m_mscom.put_PortOpen(true);   //打开串口

		if(m_mscom.get_PortOpen())
		{
			str=_T("关闭串口");
			UpdateData(true);
			h1->SetWindowText(str);   //改变按钮名称为‘’关闭串口”
		}
	}
	else
	{
		m_mscom.put_PortOpen(false);
		if(str!=_T("打开串口"))
		{
			str=_T("打开串口");
			UpdateData(true);
			h1->SetWindowText(str);      //改变按钮名称为打开串口
		}

		str2=_T("自动发送");
		UpdateData(true);
		h2->SetWindowText(str2);   //改变按钮名称为‘’自动发送”
		KillTimer(1);
		P=0;
	}
}


void Chc_2Dlg::OnBnClickedButtoSend()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(true);             //更新控件数据
	CByteArray hexdata;
	int   iRadioButton;
	iRadioButton=GetCheckedRadioButton(IDC_RADIO10,IDC_RADIO11); 
	int len=String2Hex(m_Editsend,hexdata); //此处返回的len可以用于计算发送了多少个十六进制数
	if(iRadioButton ==IDC_RADIO10)
		m_mscom.put_Output(COleVariant(hexdata));//把发送编辑框的数据发送出去	16进制发送
	else
		m_mscom.put_Output(COleVariant(m_Editsend));//把发送编辑框的数据发送出去   字符发送
	m_Editsend="";
	UpdateData(false);//发送之后将发送输入框清空
}


void Chc_2Dlg::OnBnClickedButtonClean()
{
	// TODO: 在此添加控件通知处理程序代码
	m_EditReceive=_T(""); //给接收编辑框发送空格符
	UpdateData(false);    //更新数据
}


void Chc_2Dlg::OnBnClickedButtonClose()
{
	// TODO: 在此添加控件通知处理程序代码
	if(m_mscom.get_PortOpen())
		m_mscom.put_PortOpen(false);
	CDialogEx::OnCancel();
}
BEGIN_EVENTSINK_MAP(Chc_2Dlg, CDialogEx)
	ON_EVENT(Chc_2Dlg, IDC_MSCOMM1, 1, Chc_2Dlg::OnCommMscomm1, VTS_NONE)
END_EVENTSINK_MAP()

////////////////////////////////////////////////////
CString Dec2Hex(unsigned int intDec)
{
    CString strHex;
    char charHex[255];
    sprintf(charHex,"%x",intDec);
    strHex=charHex;
    if(strHex.GetLength()==1)
        strHex=_T("0")+strHex;
    return strHex;
}
void Chc_2Dlg::OnCommMscomm1()
{
	// TODO: 在此处添加消息处理程序代码
	int   iRadioButton;
	static int capacity=0;
	iRadioButton=GetCheckedRadioButton(IDC_RADIO12,IDC_RADIO13); 
	if(m_mscom.get_CommEvent()==2)
	{
		char str[1024]={0};
		long k,len; 
		CString strtemp;
		CString temp;
		COleSafeArray safearray_inp;
		VARIANT InputData=m_mscom.get_Input(); //读缓冲区
		safearray_inp=InputData; ///变量转换
		len=safearray_inp.GetOneDimSize();//得到有效的数据长度

		for(k=0;k<len;k++)
		{
			safearray_inp.GetElement(&k,str+k); //转换为BYTE型数组
		}
		if(iRadioButton ==IDC_RADIO12)
		{
			for(k=0;k<len;k++,capacity++)
			{ 
				BYTE bt = *(char*)(str+k);//字符型
				short int intDec=(int)bt;
				CString strtemp=Dec2Hex(intDec);
				m_EditReceive+=strtemp;//加入接收编辑框对应字符串
				CString temp=_T(" "); //空格 
				m_EditReceive+=temp; 
			}
			if(capacity>8*1024)     
			{
				m_EditReceive=_T(""); //给接收编辑框发送空格符
				capacity=0;
			}
		}
		else
		{
			capacity=capacity+k;
			m_EditReceive+=str;      // 接收到编辑框里面
			if(capacity>20*1024)     
			{
				m_EditReceive=_T(""); //给接收编辑框发送空格符
				capacity=0;
			}
		}
		//UpdateData(false);
		GetDlgItem(IDC_EDIT_Rev)->SetWindowTextW(m_EditReceive) ;//只刷新IDC_EDIT_Rev的内容
		m_Edit.SendMessage(WM_VSCROLL, MAKEWPARAM(SB_BOTTOM,0),0);
	}
}


void Chc_2Dlg::OnEnChangeEditRev()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}

void Chc_2Dlg::OnBnClickedButtonMenu()
{
	// TODO: 在此添加控件通知处理程序代码
	int i;
	int   iRadioButton;
	CByteArray sendArr;
	sendArr.RemoveAll();
	sendArr.SetSize(50);
	char HEX[8];
	iRadioButton=GetCheckedRadioButton(IDC_RADIO1,IDC_RADIO2); 
	HEX[0]=0x58;
	HEX[1]=0x5A;
	HEX[2]=0x08;
	HEX[3]=0x40;
	HEX[4]=0x01;
	if(iRadioButton ==IDC_RADIO2)
	{
		HEX[5]=0x01;
		HEX[6]=0x95;
		HEX[7]=0x34;
	}
	else
	{
		HEX[5]=0x02;
		HEX[6]=0xA5;
		HEX[7]=0x57;
	}
	for(i =0;i<8;i++)
	{
		sendArr.SetAt(i,HEX[i]);
	}
	m_mscom.put_Output(COleVariant(sendArr));

}

void Chc_2Dlg::OnBnClickedButtonUp()
{
	// TODO: 在此添加控件通知处理程序代码
	int i;
	CByteArray sendArr;
	sendArr.RemoveAll();
	sendArr.SetSize(50);
	char HEX[8];

	HEX[0]=0x58;
	HEX[1]=0x5A;
	HEX[2]=0x08;
	HEX[3]=0x61;
	HEX[4]=0x01;
	HEX[5]=0x01;
	HEX[6]=0x24;
	HEX[7]=0xC2;

	for(i =0;i<8;i++)
	{
		sendArr.SetAt(i,HEX[i]);
	}
	m_mscom.put_Output(COleVariant(sendArr));
}


void Chc_2Dlg::OnBnClickedButtonFormat()
{
	// TODO: 在此添加控件通知处理程序代码
	int i;
	CByteArray sendArr;
	sendArr.RemoveAll();
	sendArr.SetSize(50);
	char HEX[7];

	HEX[0]=0x58;
	HEX[1]=0x5A;
	HEX[2]=0x07;
	HEX[3]=0x45;
	HEX[4]=0x00;
	HEX[5]=0x7D;
	HEX[6]=0x26;

	for(i =0;i<7;i++)
	{
		sendArr.SetAt(i,HEX[i]);
	}
	m_mscom.put_Output(COleVariant(sendArr));

}


//void Chc_2Dlg::OnBnClickedButtonResolution()
//{
//	// TODO: 在此添加控件通知处理程序代码
//}


void Chc_2Dlg::OnBnClickedButtonMain()
{
	// TODO: 在此添加控件通知处理程序代码
	int i;
	CByteArray sendArr;
	sendArr.RemoveAll();
	sendArr.SetSize(50);
	char HEX[8];

	HEX[0]=0x58;
	HEX[1]=0x5A;
	HEX[2]=0x08;
	HEX[3]=0x60;
	HEX[4]=0x01;
	HEX[5]=0x01;
	HEX[6]=0x13;
	HEX[7]=0xF2;

	for(i =0;i<8;i++)
	{
		sendArr.SetAt(i,HEX[i]);
	}
	m_mscom.put_Output(COleVariant(sendArr));
}


void Chc_2Dlg::OnBnClickedButtonRestore()
{
	// TODO: 在此添加控件通知处理程序代码
	int i;
	CByteArray sendArr;
	sendArr.RemoveAll();
	sendArr.SetSize(50);
	char HEX[7];

	HEX[0]=0x58;
	HEX[1]=0x5A;
	HEX[2]=0x07;
	HEX[3]=0x46;
	HEX[4]=0x00;
	HEX[5]=0x28;
	HEX[6]=0x75;

	for(i =0;i<7;i++)
	{
		sendArr.SetAt(i,HEX[i]);
	}
	m_mscom.put_Output(COleVariant(sendArr));

}


//void Chc_2Dlg::OnBnClickedButtonUpdate()
//{
//	// TODO: 在此添加控件通知处理程序代码
//}


void Chc_2Dlg::OnBnClickedButtonDown()
{
	// TODO: 在此添加控件通知处理程序代码
	int i;
	CByteArray sendArr;
	sendArr.RemoveAll();
	sendArr.SetSize(50);
	char HEX[8];

	HEX[0]=0x58;
	HEX[1]=0x5A;
	HEX[2]=0x08;
	HEX[3]=0x61;
	HEX[4]=0x01;
	HEX[5]=0x02;
	HEX[6]=0x14;
	HEX[7]=0xA1;

	for(i =0;i<8;i++)
	{
		sendArr.SetAt(i,HEX[i]);
	}
	m_mscom.put_Output(COleVariant(sendArr));
}


void Chc_2Dlg::OnBnClickedButtonRight()
{
	// TODO: 在此添加控件通知处理程序代码
	int i;
	CByteArray sendArr;
	sendArr.RemoveAll();
	sendArr.SetSize(50);
	char HEX[8];

	HEX[0]=0x58;
	HEX[1]=0x5A;
	HEX[2]=0x08;
	HEX[3]=0x61;
	HEX[4]=0x01;
	HEX[5]=0x04;
	HEX[6]=0x74;
	HEX[7]=0x67;

	for(i =0;i<8;i++)
	{
		sendArr.SetAt(i,HEX[i]);
	}
	m_mscom.put_Output(COleVariant(sendArr));
}

void Chc_2Dlg::OnBnClickedButtonPrevpage()
{
	// TODO: 在此添加控件通知处理程序代码
	int i;
	CByteArray sendArr;
	sendArr.RemoveAll();
	sendArr.SetSize(50);
	char HEX[8];

	HEX[0]=0x58;
	HEX[1]=0x5A;
	HEX[2]=0x08;
	HEX[3]=0x61;
	HEX[4]=0x01;
	HEX[5]=0x05;
	HEX[6]=0x64;
	HEX[7]=0x46;

	for(i =0;i<8;i++)
	{
		sendArr.SetAt(i,HEX[i]);
	}
	m_mscom.put_Output(COleVariant(sendArr));
}


void Chc_2Dlg::OnBnClickedButtonNextpage()
{
	// TODO: 在此添加控件通知处理程序代码
	int i;
	CByteArray sendArr;
	sendArr.RemoveAll();
	sendArr.SetSize(50);
	char HEX[8];

	HEX[0]=0x58;
	HEX[1]=0x5A;
	HEX[2]=0x08;
	HEX[3]=0x61;
	HEX[4]=0x01;
	HEX[5]=0x06;
	HEX[6]=0x54;
	HEX[7]=0x25;

	for(i =0;i<8;i++)
	{
		sendArr.SetAt(i,HEX[i]);
	}
	m_mscom.put_Output(COleVariant(sendArr));
}


void Chc_2Dlg::OnBnClickedButtonGengralRecord()
{
	// TODO: 在此添加控件通知处理程序代码
	int i;
	CByteArray sendArr;
	sendArr.RemoveAll();
	sendArr.SetSize(50);
	char HEX[8];

	HEX[0]=0x58;
	HEX[1]=0x5A;
	HEX[2]=0x08;
	HEX[3]=0x62;
	HEX[4]=0x01;
	HEX[5]=0x01;
	HEX[6]=0x7D;
	HEX[7]=0x92;

	for(i =0;i<8;i++)
	{
		sendArr.SetAt(i,HEX[i]);
	}
	m_mscom.put_Output(COleVariant(sendArr));
}


void Chc_2Dlg::OnBnClickedButtonPauseRecord2()
{
	// TODO: 在此添加控件通知处理程序代码
	int i;
	CByteArray sendArr;
	sendArr.RemoveAll();
	sendArr.SetSize(50);
	char HEX[8];

	HEX[0]=0x58;
	HEX[1]=0x5A;
	HEX[2]=0x08;
	HEX[3]=0x62;
	HEX[4]=0x01;
	HEX[5]=0x02;
	HEX[6]=0x4D;
	HEX[7]=0xF1;

	for(i =0;i<8;i++)
	{
		sendArr.SetAt(i,HEX[i]);
	}
	m_mscom.put_Output(COleVariant(sendArr));
}


void Chc_2Dlg::OnBnClickedButtonEmergencyRecord()
{
	// TODO: 在此添加控件通知处理程序代码
	int i;
	CByteArray sendArr;
	sendArr.RemoveAll();
	sendArr.SetSize(50);
	char HEX[8];

	HEX[0]=0x58;
	HEX[1]=0x5A;
	HEX[2]=0x08;
	HEX[3]=0x62;
	HEX[4]=0x01;
	HEX[5]=0x03;
	HEX[6]=0x5D;
	HEX[7]=0xD0;

	for(i =0;i<8;i++)
	{
		sendArr.SetAt(i,HEX[i]);
	}
	m_mscom.put_Output(COleVariant(sendArr));
}


void Chc_2Dlg::OnBnClickedButtonGenaralBrown()
{
	// TODO: 在此添加控件通知处理程序代码
	int i;
	CByteArray sendArr;
	sendArr.RemoveAll();
	sendArr.SetSize(50);
	char HEX[8];

	HEX[0]=0x58;
	HEX[1]=0x5A;
	HEX[2]=0x08;
	HEX[3]=0x62;
	HEX[4]=0x01;
	HEX[5]=0x04;
	HEX[6]=0x2D;
	HEX[7]=0x37;

	for(i =0;i<8;i++)
	{
		sendArr.SetAt(i,HEX[i]);
	}
	m_mscom.put_Output(COleVariant(sendArr));
}


void Chc_2Dlg::OnBnClickedButtonEmergencyBrown()
{
	// TODO: 在此添加控件通知处理程序代码
	int i;
	CByteArray sendArr;
	sendArr.RemoveAll();
	sendArr.SetSize(50);
	char HEX[8];

	HEX[0]=0x58;
	HEX[1]=0x5A;
	HEX[2]=0x08;
	HEX[3]=0x62;
	HEX[4]=0x01;
	HEX[5]=0x05;
	HEX[6]=0x3D;
	HEX[7]=0x16;

	for(i =0;i<8;i++)
	{
		sendArr.SetAt(i,HEX[i]);
	}
	m_mscom.put_Output(COleVariant(sendArr));
}


void Chc_2Dlg::OnBnClickedButtonRiskBrown()
{
	// TODO: 在此添加控件通知处理程序代码
	int i;
	CByteArray sendArr;
	sendArr.RemoveAll();
	sendArr.SetSize(50);
	char HEX[8];

	HEX[0]=0x58;
	HEX[1]=0x5A;
	HEX[2]=0x08;
	HEX[3]=0x62;
	HEX[4]=0x01;
	HEX[5]=0x06;
	HEX[6]=0x0D;
	HEX[7]=0x75;

	for(i =0;i<8;i++)
	{
		sendArr.SetAt(i,HEX[i]);
	}
	m_mscom.put_Output(COleVariant(sendArr));
}


void Chc_2Dlg::OnBnClickedButtonPhotoBrown()
{
	// TODO: 在此添加控件通知处理程序代码
	int i;
	CByteArray sendArr;
	sendArr.RemoveAll();
	sendArr.SetSize(50);
	char HEX[8];

	HEX[0]=0x58;
	HEX[1]=0x5A;
	HEX[2]=0x08;
	HEX[3]=0x62;
	HEX[4]=0x01;
	HEX[5]=0x07;
	HEX[6]=0x1D;
	HEX[7]=0x54;

	for(i =0;i<8;i++)
	{
		sendArr.SetAt(i,HEX[i]);
	}
	m_mscom.put_Output(COleVariant(sendArr));
}


void Chc_2Dlg::OnBnClickedButtonExitBrown()
{
	// TODO: 在此添加控件通知处理程序代码
	int i;
	CByteArray sendArr;
	sendArr.RemoveAll();
	sendArr.SetSize(50);
	char HEX[8];

	HEX[0]=0x58;
	HEX[1]=0x5A;
	HEX[2]=0x08;
	HEX[3]=0x62;
	HEX[4]=0x01;
	HEX[5]=0x08;
	HEX[6]=0xEC;
	HEX[7]=0xBB;

	for(i =0;i<8;i++)
	{
		sendArr.SetAt(i,HEX[i]);
	}
	m_mscom.put_Output(COleVariant(sendArr));
}


void Chc_2Dlg::OnBnClickedButtonCapture()
{
	// TODO: 在此添加控件通知处理程序代码
	int i;
	CByteArray sendArr;
	sendArr.RemoveAll();
	sendArr.SetSize(50);
	char HEX[8];

	HEX[0]=0x58;
	HEX[1]=0x5A;
	HEX[2]=0x08;
	HEX[3]=0x62;
	HEX[4]=0x01;
	HEX[5]=0x09;
	HEX[6]=0xFC;
	HEX[7]=0x9A;

	for(i =0;i<8;i++)
	{
		sendArr.SetAt(i,HEX[i]);
	}
	m_mscom.put_Output(COleVariant(sendArr));}


void Chc_2Dlg::OnBnClickedButtonDelfile()
{
	// TODO: 在此添加控件通知处理程序代码
	int i;
	CByteArray sendArr;
	sendArr.RemoveAll();
	sendArr.SetSize(50);
	char HEX[8];

	HEX[0]=0x58;
	HEX[1]=0x5A;
	HEX[2]=0x08;
	HEX[3]=0x62;
	HEX[4]=0x01;
	HEX[5]=0x0B;
	HEX[6]=0xDC;
	HEX[7]=0xD8;

	for(i =0;i<8;i++)
	{
		sendArr.SetAt(i,HEX[i]);
	}
	m_mscom.put_Output(COleVariant(sendArr));
}


void Chc_2Dlg::OnBnClickedButtonDelall()
{
	// TODO: 在此添加控件通知处理程序代码
	int i;
	CByteArray sendArr;
	sendArr.RemoveAll();
	sendArr.SetSize(50);
	char HEX[8];

	HEX[0]=0x58;
	HEX[1]=0x5A;
	HEX[2]=0x08;
	HEX[3]=0x62;
	HEX[4]=0x01;
	HEX[5]=0x0C;
	HEX[6]=0xAC;
	HEX[7]=0x3F;

	for(i =0;i<8;i++)
	{
		sendArr.SetAt(i,HEX[i]);
	}
	m_mscom.put_Output(COleVariant(sendArr));
}


void Chc_2Dlg::OnBnClickedButtonPlay()
{
	// TODO: 在此添加控件通知处理程序代码
	int i;
	CByteArray sendArr;
	sendArr.RemoveAll();
	sendArr.SetSize(50);
	char HEX[8];

	HEX[0]=0x58;
	HEX[1]=0x5A;
	HEX[2]=0x08;
	HEX[3]=0x62;
	HEX[4]=0x01;
	HEX[5]=0x0D;
	HEX[6]=0xBC;
	HEX[7]=0x1E;

	for(i =0;i<8;i++)
	{
		sendArr.SetAt(i,HEX[i]);
	}
	m_mscom.put_Output(COleVariant(sendArr));
}


void Chc_2Dlg::OnBnClickedButtonPause()
{
	// TODO: 在此添加控件通知处理程序代码
	int i;
	CByteArray sendArr;
	sendArr.RemoveAll();
	sendArr.SetSize(50);
	char HEX[8];

	HEX[0]=0x58;
	HEX[1]=0x5A;
	HEX[2]=0x08;
	HEX[3]=0x62;
	HEX[4]=0x01;
	HEX[5]=0x0E;
	HEX[6]=0x8C;
	HEX[7]=0x7D;

	for(i =0;i<8;i++)
	{
		sendArr.SetAt(i,HEX[i]);
	}
	m_mscom.put_Output(COleVariant(sendArr));
}


void Chc_2Dlg::OnBnClickedButtonPlayprev()
{
	// TODO: 在此添加控件通知处理程序代码
	int i;
	CByteArray sendArr;
	sendArr.RemoveAll();
	sendArr.SetSize(50);
	char HEX[8];

	HEX[0]=0x58;
	HEX[1]=0x5A;
	HEX[2]=0x08;
	HEX[3]=0x62;
	HEX[4]=0x01;
	HEX[5]=0x0F;
	HEX[6]=0x9C;
	HEX[7]=0x5C;

	for(i =0;i<8;i++)
	{
		sendArr.SetAt(i,HEX[i]);
	}
	m_mscom.put_Output(COleVariant(sendArr));
}


void Chc_2Dlg::OnBnClickedButtonPlaynext()
{
	// TODO: 在此添加控件通知处理程序代码
	int i;
	CByteArray sendArr;
	sendArr.RemoveAll();
	sendArr.SetSize(50);
	char HEX[8];

	HEX[0]=0x58;
	HEX[1]=0x5A;
	HEX[2]=0x08;
	HEX[3]=0x62;
	HEX[4]=0x01;
	HEX[5]=0x10;
	HEX[6]=0x7F;
	HEX[7]=0x82;

	for(i =0;i<8;i++)
	{
		sendArr.SetAt(i,HEX[i]);
	}
	m_mscom.put_Output(COleVariant(sendArr));
}


void Chc_2Dlg::OnBnClickedButtonExitplay()
{
	// TODO: 在此添加控件通知处理程序代码
	int i;
	CByteArray sendArr;
	sendArr.RemoveAll();
	sendArr.SetSize(50);
	char HEX[8];

	HEX[0]=0x58;
	HEX[1]=0x5A;
	HEX[2]=0x08;
	HEX[3]=0x62;
	HEX[4]=0x01;
	HEX[5]=0x11;
	HEX[6]=0x6F;
	HEX[7]=0xA3;

	for(i =0;i<8;i++)
	{
		sendArr.SetAt(i,HEX[i]);
	}
	m_mscom.put_Output(COleVariant(sendArr));
}


//void Chc_2Dlg::OnBnClickedButtonTapset4()
//{
//	// TODO: 在此添加控件通知处理程序代码
//}

void Chc_2Dlg::OnBnClickedResolution2()
{
	// TODO: 在此添加控件通知处理程序代码
	int i;
	int   iRadioButton;
	CByteArray sendArr;
	sendArr.RemoveAll();
	sendArr.SetSize(50);
	char HEX[8];
	iRadioButton=GetCheckedRadioButton(IDC_RADIO4,IDC_RADIO5); 
	HEX[0]=0x58;
	HEX[1]=0x5A;
	HEX[2]=0x08;
	HEX[3]=0x41;
	HEX[4]=0x01;
	if(iRadioButton ==IDC_RADIO4)
	{
		HEX[5]=0x02;
		HEX[6]=0x92;
		HEX[7]=0x67;
	}
	else
	{
		HEX[5]=0x01;
		HEX[6]=0xA2;
		HEX[7]=0x04;
	}
	for(i =0;i<8;i++)
	{
		sendArr.SetAt(i,HEX[i]);
	}
	m_mscom.put_Output(COleVariant(sendArr));
}


void Chc_2Dlg::OnBnClickedButtonCycleRecord1()
{
	// TODO: 在此添加控件通知处理程序代码
	int i;
	int   iRadioButton;
	CByteArray sendArr;
	sendArr.RemoveAll();
	sendArr.SetSize(50);
	char HEX[8];
	iRadioButton=GetCheckedRadioButton(IDC_RADIO7,IDC_RADIO9);  
	HEX[0]=0x58;
	HEX[1]=0x5A;
	HEX[2]=0x08;
	HEX[3]=0x42;
	HEX[4]=0x01;
	if(iRadioButton ==IDC_RADIO7)
	{
		HEX[5]=0x01;
		HEX[6]=0xFB;
		HEX[7]=0x54;
	}
	else if(iRadioButton ==IDC_RADIO8)
	{
		HEX[5]=0x02;
		HEX[6]=0xCB;
		HEX[7]=0x37;
	}
	else
	{
		HEX[5]=0x03;
		HEX[6]=0xDB;
		HEX[7]=0x16;
	}
	for(i =0;i<8;i++)
	{
		sendArr.SetAt(i,HEX[i]);
	}
	m_mscom.put_Output(COleVariant(sendArr));

}

void Chc_2Dlg::OnBnClickedButtonMoveToEmergency()
{
	// TODO: 在此添加控件通知处理程序代码
	int i;
	CByteArray sendArr;
	sendArr.RemoveAll();
	sendArr.SetSize(50);
	char HEX[8];

	HEX[0]=0x58;
	HEX[1]=0x5A;
	HEX[2]=0x08;
	HEX[3]=0x62;
	HEX[4]=0x01;
	HEX[5]=0x0A;
	HEX[6]=0xCC;
	HEX[7]=0xF9;

	for(i =0;i<8;i++)
	{
		sendArr.SetAt(i,HEX[i]);
	}
	m_mscom.put_Output(COleVariant(sendArr));
}

void Chc_2Dlg::OnBnClickedButtonLeft2()
{
	// TODO: 在此添加控件通知处理程序代码
	int i;
	CByteArray sendArr;
	sendArr.RemoveAll();
	sendArr.SetSize(50);
	char HEX[8];

	HEX[0]=0x58;
	HEX[1]=0x5A;
	HEX[2]=0x08;
	HEX[3]=0x61;
	HEX[4]=0x01;
	HEX[5]=0x03;
	HEX[6]=0x04;
	HEX[7]=0x80;

	for(i =0;i<8;i++)
	{
		sendArr.SetAt(i,HEX[i]);
	}
	m_mscom.put_Output(COleVariant(sendArr));
}


void Chc_2Dlg::OnBnClickedRadio1()
{
	// TODO: 在此添加控件通知处理程序代码
	m_radio_MIC=0;
}


void Chc_2Dlg::OnBnClickedRadio2()
{
	// TODO: 在此添加控件通知处理程序代码
	m_radio_MIC=1;
}


void Chc_2Dlg::OnBnClickedRadio4()
{
	// TODO: 在此添加控件通知处理程序代码
	m_radio_RES=0;
}


void Chc_2Dlg::OnBnClickedRadio5()
{
	// TODO: 在此添加控件通知处理程序代码
	m_radio_RES=1;
}


void Chc_2Dlg::OnBnClickedRadio7()
{
	// TODO: 在此添加控件通知处理程序代码
	m_radio_VID=0;
}


void Chc_2Dlg::OnBnClickedRadio8()
{
	// TODO: 在此添加控件通知处理程序代码
	m_radio_VID=1;
}


void Chc_2Dlg::OnBnClickedRadio9()
{
	// TODO: 在此添加控件通知处理程序代码
	m_radio_VID=2;
}



void Chc_2Dlg::OnBnClickedRadio10()
{
	// TODO: 在此添加控件通知处理程序代码
	m_radio_HEX=0;
}


void Chc_2Dlg::OnBnClickedRadio11()
{
	// TODO: 在此添加控件通知处理程序代码
	m_radio_HEX=1;
}


void Chc_2Dlg::OnBnClickedRadio12()
{
	// TODO: 在此添加控件通知处理程序代码
	m_radio_disp=0;
}


void Chc_2Dlg::OnBnClickedRadio13()
{
	// TODO: 在此添加控件通知处理程序代码
	m_radio_disp=1;
}


void Chc_2Dlg::OnTimer(UINT_PTR nIDEvent)
{
	int i;
	CByteArray sendArr;
	sendArr.RemoveAll();
	sendArr.SetSize(50);
	for(i =0;i<12;i++)
	{
		sendArr.SetAt(i,pre_cmd[i]);
	}
	m_mscom.put_Output(COleVariant(sendArr));

	for(i =0;i<12;i++)
	{
		sendArr.SetAt(i,nex_cmd[i]);
	}
	m_mscom.put_Output(COleVariant(sendArr));

}

void Chc_2Dlg::OnBnClickedButtonAutosend()
{
	// TODO: 在此添加控件通知处理程序代码
	CString str;
	CWnd *h1;
	h1=GetDlgItem(IDC_BUTTON_AUTOSEND);   //指向控件的caption
	if(P==0)
	{
		str=_T("停止发送");
		UpdateData(true);
		h1->SetWindowText(str);   //改变按钮名称为‘’停止发送”

		SetTimer(1,1000*m_Edit_Time,NULL);
		P=1;
	}
	else
	{
		str=_T("自动发送");
		UpdateData(true);
		h1->SetWindowText(str);   //改变按钮名称为‘’自动发送”

		KillTimer(1);
		P=0;
	}
}


void Chc_2Dlg::OnBnClickedButtonRestore2()
{
	// TODO: 在此添加控件通知处理程序代码
	int i;
	int   iRadioButton;
	CByteArray sendArr;
	sendArr.RemoveAll();
	sendArr.SetSize(50);
	char HEX[8];
	iRadioButton=GetCheckedRadioButton(IDC_RADIO14,IDC_RADIO16);  
	HEX[0]=0x58;
	HEX[1]=0x5A;
	HEX[2]=0x08;
	HEX[3]=0x43;
	HEX[4]=0x01;
	if(m_Event_Time ==1)
	{
		HEX[5]=0x01;
		HEX[6]=0xCC;
		HEX[7]=0x64;
	}

	else if(m_Event_Time ==3)
	{
		HEX[5]=0x03;
		HEX[6]=0xEC;
		HEX[7]=0x26;
	}
	else 
	{
		HEX[5]=0x02;
		HEX[6]=0xFC;
		HEX[7]=0x07;
	}
	for(i =0;i<8;i++)
	{
		sendArr.SetAt(i,HEX[i]);
	}
	m_mscom.put_Output(COleVariant(sendArr));
}


void Chc_2Dlg::OnBnClickedRadio14()
{
	// TODO: 在此添加控件通知处理程序代码
	m_Event_Time=1;
	
}


void Chc_2Dlg::OnBnClickedRadio15()
{
	// TODO: 在此添加控件通知处理程序代码
	m_Event_Time=2;

}


void Chc_2Dlg::OnBnClickedRadio16()
{
	// TODO: 在此添加控件通知处理程序代码
	m_Event_Time=3;
	
}


void Chc_2Dlg::OnBnClickedRadio17()
{
	// TODO: 在此添加控件通知处理程序代码
	m_Select_File=1;
}


void Chc_2Dlg::OnBnClickedRadio18()
{
	// TODO: 在此添加控件通知处理程序代码
	m_Select_File=2;
}


void Chc_2Dlg::OnBnClickedRadio19()
{
	// TODO: 在此添加控件通知处理程序代码
	m_Select_File=3;
}


void Chc_2Dlg::OnBnClickedRadio20()
{
	// TODO: 在此添加控件通知处理程序代码
	m_Select_File=4;
}


void Chc_2Dlg::OnBnClickedRadio21()
{
	// TODO: 在此添加控件通知处理程序代码
	m_Select_File=5;
}


void Chc_2Dlg::OnBnClickedRadio22()
{
	// TODO: 在此添加控件通知处理程序代码
	m_Select_File=6;
}


void Chc_2Dlg::OnBnClickedButtonRestore3()
{
	// TODO: 在此添加控件通知处理程序代码
	int i;
	int   iRadioButton;
	CByteArray sendArr;
	sendArr.RemoveAll();
	sendArr.SetSize(50);
	char HEX[8];
	iRadioButton=GetCheckedRadioButton(IDC_RADIO17,IDC_RADIO22);  
	HEX[0]=0x58;
	HEX[1]=0x5A;
	HEX[2]=0x08;
	HEX[3]=0x63;
	HEX[4]=0x01;
	if(iRadioButton ==IDC_RADIO17)
	{
		HEX[5]=0x01;
		HEX[6]=0x4A;
		HEX[7]=0xA2;
	}
	else if(iRadioButton ==IDC_RADIO18)
	{
		HEX[5]=0x02;
		HEX[6]=0x7A;
		HEX[7]=0xC1;
	}
	else if(iRadioButton ==IDC_RADIO19)
	{
		HEX[5]=0x03;
		HEX[6]=0x6A;
		HEX[7]=0xE0;
	}
	else if(iRadioButton ==IDC_RADIO20)
	{
		HEX[5]=0x04;
		HEX[6]=0x1A;
		HEX[7]=0x07;
	}
	else if(iRadioButton ==IDC_RADIO21)
	{
		HEX[5]=0x05;
		HEX[6]=0x0A;
		HEX[7]=0x26;
	}
	else
	{
		HEX[5]=0x06;
		HEX[6]=0x3A;
		HEX[7]=0x45;
	}
	for(i =0;i<8;i++)
	{
		sendArr.SetAt(i,HEX[i]);
	}
	m_mscom.put_Output(COleVariant(sendArr));
}
