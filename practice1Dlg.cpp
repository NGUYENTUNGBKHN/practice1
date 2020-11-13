
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
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void Cpractice1Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_MFCEDITBROWSE1, input_binary);
	DDX_Text(pDX, IDC_MFCEDITBROWSE2, output_csv);
	DDX_Text(pDX, IDC_EDIT1, str_show);
}

BEGIN_MESSAGE_MAP(Cpractice1Dlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_SHOW, &Cpractice1Dlg::OnBnClickedButtonShow)
	ON_BN_CLICKED(IDC_BUTTON_SAVE, &Cpractice1Dlg::OnBnClickedButtonSave)
END_MESSAGE_MAP()


// Cpractice1Dlg メッセージ ハンドラー

BOOL Cpractice1Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// このダイアログのアイコンを設定します。アプリケーションのメイン ウィンドウがダイアログでない場合、
	//  Framework は、この設定を自動的に行います。
	SetIcon(m_hIcon, TRUE);			// 大きいアイコンの設定
	SetIcon(m_hIcon, FALSE);		// 小さいアイコンの設定

	// TODO: 初期化をここに追加します。

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


ComFile f;
void Cpractice1Dlg::OnBnClickedButtonShow()
{
	// TODO: ここにコントロール通知ハンドラー コードを追加します。
	this->UpdateData();
	
	
	f.open(input_binary);
	f.read();
	//TRACE(f.data.c_str());
	str_show = CString(f.data_show);
	// check header
	if (f.check_header_file() != 0)
	{
		f.reset();
		MessageBox(NULL, L"ERROR HEADER", 0);
	}

	//check size file



	f.close();
	
	this->UpdateData(FALSE);
}




void Cpractice1Dlg::OnBnClickedButtonSave()
{
	// TODO: ここにコントロール通知ハンドラー コードを追加します。
	this->UpdateData();

	f.open(output_csv);
	if (f.write() == 0)
	{
		MessageBox(NULL, L"DONE", 0);
	}
	f.close();


	this->UpdateData(FALSE);
}
