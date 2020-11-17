
// practice1Dlg.cpp : 実装ファイル
//

#include "pch.h"
#include "framework.h"
#include "practice1.h"
#include "practice1Dlg.h"
#include "afxdialogex.h"
#include "communicate_file.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// Cpractice1Dlg ダイアログ



Cpractice1Dlg::Cpractice1Dlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_PRACTICE1_DIALOG, pParent)
	, output_csv(_T(""))
	, str_show(_T(""))
	, m_cb1(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void Cpractice1Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_MFCEDITBROWSE1, input_binary);
	DDX_Text(pDX, IDC_MFCEDITBROWSE2, output_csv);
	DDX_Text(pDX, IDC_EDIT1, str_show);
	DDX_Control(pDX, IDC_COMBO1, c_cb1);
	DDX_CBString(pDX, IDC_COMBO1, m_cb1);
	DDX_Control(pDX, IDC_MFCEDITBROWSE2, c_editbrowe);
	DDX_Control(pDX, IDC_BUTTON_SAVE, c_btn_save);
}

BEGIN_MESSAGE_MAP(Cpractice1Dlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_SHOW, &Cpractice1Dlg::OnBnClickedButtonShow)
	ON_BN_CLICKED(IDC_BUTTON_SAVE, &Cpractice1Dlg::OnBnClickedButtonSave)
	ON_CBN_SELCHANGE(IDC_COMBO1, &Cpractice1Dlg::OnSelchangeCombo1)
	ON_WM_TIMER()
//	ON_EN_CHANGE(IDC_EDIT1, &Cpractice1Dlg::OnEnChangeEdit1)
//	ON_EN_CHANGE(IDC_EDIT2, &Cpractice1Dlg::OnEnChangeEdit2)
ON_BN_CLICKED(IDOK, &Cpractice1Dlg::OnBnClickedOk)
END_MESSAGE_MAP()

CString typeStruct[] = { L"ASCII",L"HEX",L"DEC",L"OCT",L"BIN" };
// Cpractice1Dlg メッセージ ハンドラー

BOOL Cpractice1Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// このダイアログのアイコンを設定します。アプリケーションのメイン ウィンドウがダイアログでない場合、
	//  Framework は、この設定を自動的に行います。
	SetIcon(m_hIcon, TRUE);			// 大きいアイコンの設定
	SetIcon(m_hIcon, FALSE);		// 小さいアイコンの設定

	// TODO: 初期化をここに追加します。
	for (int i = 0; i < sizeof(typeStruct)/sizeof(CString); i++) {
	
		c_cb1.AddString(typeStruct[i]);
	}
	//m_cb1 = "ASCII";
	return TRUE;  // フォーカスをコントロールに設定した場合を除き、TRUE を返します。
}

// ダイアログに最小化ボタンを追加する場合、アイコンを描画するための
//  下のコードが必要です。ドキュメント/ビュー モデルを使う MFC アプリケーションの場合、
//  これは、Framework によって自動的に設定されます。

void Cpractice1Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 描画のデバイス コンテキスト

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// クライアントの四角形領域内の中央
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// アイコンの描画
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// ユーザーが最小化したウィンドウをドラッグしているときに表示するカーソルを取得するために、
//  システムがこの関数を呼び出します。
HCURSOR Cpractice1Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

std::string __data;
volatile bool v_show;

void Cpractice1Dlg::OnBnClickedButtonShow()
{
	// TODO: ここにコントロール通知ハンドラー コードを追加します。
	this->UpdateData();

	//check box 
	if (input_binary == "")
	{
		MessageBoxW((LPCWSTR)L"Please select file .bin", (LPCWSTR)L"SHOW FILE", MB_ICONASTERISK);
		this->UpdateData(FALSE);
		return;
	}

	// check value of combo1 != NULL
	if (m_cb1 == "")
	{
		MessageBoxW((LPCWSTR)L"Please select Base number.\n Ex: ACSII, DEC, HEX ...v..v", (LPCWSTR)L"SHOW FILE", MB_ICONASTERISK);
		this->UpdateData(FALSE);
		return;
	}

	ComFile f;

	f.open(input_binary);  /// open input file binary
	f.read();				// read file binary
	//TRACE(f.data.c_str());
	__data = f.data_text;
	v_show = 1;
	change_hs(m_cb1);
	
	
	// check header
	if (f.check_header_file() != 0)
	{
		f.reset();
		str_show = "";
		MessageBoxW((LPCWSTR)L"Header file is incorrect.", (LPCWSTR)L"SHOW FILE", MB_ICONWARNING);
	}

	//check size file
	if (f.check_size_file() != 0)
	{
		f.reset();
		str_show = "";
		MessageBoxW((LPCWSTR)L"Size file is incorrect.", (LPCWSTR)L"SHOW FILE", MB_ICONWARNING);
	}
	
	//TRACE("done");
	f.close();
	
	this->UpdateData(FALSE);
}


void Cpractice1Dlg::OnBnClickedButtonSave()
{
	// TODO: ここにコントロール通知ハンドラー コードを追加します。
	this->UpdateData();

	if (output_csv == "")
	{
		MessageBoxW((LPCWSTR)L"Please select file csv", (LPCWSTR)L"SAVE FILE", MB_ICONASTERISK);
		this->UpdateData(FALSE);
		return;
	}

	if ((__data == "") || (str_show == ""))
	{
		MessageBoxW((LPCWSTR)L"Data empty !", (LPCWSTR)L"SAVE FILE", MB_ICONERROR);
		this->UpdateData(FALSE);
		return;
	}

	ComFile f;
	
	if (f.open(output_csv) != COM_OK)// open file csv
	{
		
		int selected_user = MessageBoxW((LPCWSTR)L"FILE NOT EXITS \n Do you want to create new file", 
										(LPCWSTR)L"CREATE FILE", 
										MB_YESNO | MB_ICONQUESTION);
		if (selected_user == IDYES)
		{
			f.create_file_csv(output_csv);
		}
		else
		{
			return;
		}
		f.open(output_csv);
	}

	if (f.write_csv(__data) == COM_OK)       // write into file csv
	{
		MessageBoxW((LPCWSTR)L"DONE", (LPCWSTR)L"SAVE FILE", MB_ICONASTERISK);
	}
	f.close();
	this->UpdateData(FALSE);
}


void Cpractice1Dlg::OnSelchangeCombo1()
{
	// TODO: Add your control notification handler code here
	SetTimer(1,100,NULL);  // timer on interrupt change data show 
}

void Cpractice1Dlg::edit_box_show_data(char *data)
{
	c_editbrowe.EnableWindow();
	c_btn_save.EnableWindow();
	str_show = data;
}

void Cpractice1Dlg::edit_box_show_data(CString data)
{

	c_editbrowe.EnableWindow();
	c_btn_save.EnableWindow();
	str_show = data;
}

void Cpractice1Dlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: Add your message handler code here and/or call default
	this->UpdateData();
	
	change_hs(m_cb1);
	
	CDialogEx::OnTimer(nIDEvent);
	KillTimer(1);                   /// timer stop
	this->UpdateData(FALSE); 
}

//void Cpractice1Dlg::OnEnChangeEdit1()
//{
//	// TODO:  If this is a RICHEDIT control, the control will not
//	// send this notification unless you override the CDialogEx::OnInitDialog()
//	// function and call CRichEditCtrl().SetEventMask()
//	// with the ENM_CHANGE flag ORed into the mask.
//
//	// TODO:  Add your control notification handler code here
//	m_cb1 = header_type;
//}

//void Cpractice1Dlg::OnEnChangeEdit2()
//{
//	// TODO:  If this is a RICHEDIT control, the control will not
//	// send this notification unless you override the CDialogEx::OnInitDialog()
//	// function and call CRichEditCtrl().SetEventMask()
//	// with the ENM_CHANGE flag ORed into the mask.
//
//	// TODO:  Add your control notification handler code here
//}

void Cpractice1Dlg::change_hs(CString cb)
{
	CString tg;
	CString edit1_data;
	if (str_show != "" || v_show == 1)
	{
		v_show = 0;
		if (m_cb1 == "HEX")
		{
			for (int i = 0; i < __data.length(); i++)
			{
				tg.Format(_T("%x"), __data[i]);
				edit1_data += tg;
				edit1_data += " ";
			}
			edit_box_show_data(edit1_data);
			edit1_data = "";
			//str_show = edit1_data;
		}
		else if (m_cb1 == "DEC")
		{
			for (int i = 0; i < __data.length(); i++)
			{
				tg.Format(_T("%d"), __data[i]);
				edit1_data += tg;
				edit1_data += " ";
			}
			edit_box_show_data(edit1_data);
			edit1_data = "";
		}
		else if (m_cb1 == "OCT")
		{
			for (int i = 0; i < __data.length(); i++)
			{
				tg.Format(_T("%o"), __data[i]);
				edit1_data += tg;
				edit1_data += " ";
			}
			edit_box_show_data(edit1_data);
			edit1_data = "";
		}
		else if (m_cb1 == "ASCII")
		{
			for (int i = 0; i < __data.length(); i++)
			{
				tg.Format(_T("%c"), __data[i]);
				edit1_data += tg;
				//edit1_data += " ";
			}
			edit_box_show_data(edit1_data);
			edit1_data = "";
		}
		else  // bin
		{

		}
	}
}


void Cpractice1Dlg::OnBnClickedOk()
{
	// TODO: ここにコントロール通知ハンドラー コードを追加します。
	int select_user = MessageBoxW((LPCWSTR)L"Do you want to quit ?",(LPCWSTR)L"課題①ーMFC", MB_ICONQUESTION | MB_YESNO);
	if (select_user == IDYES)
	{

	}
	else
	{
		return;
	}

	CDialogEx::OnOK();
}
