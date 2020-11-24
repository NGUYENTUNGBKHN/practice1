
// practice1Dlg.h : ヘッダー ファイル
//

#pragma once


// Cpractice1Dlg ダイアログ
class Cpractice1Dlg : public CDialogEx
{
// コンストラクション
public:
	Cpractice1Dlg(CWnd* pParent = nullptr);	// 標準コンストラクター

// ダイアログ データ
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_PRACTICE1_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV サポート


// 実装
protected:
	HICON m_hIcon;

	// 生成された、メッセージ割り当て関数
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CString input_binary;
	CString output_csv;
	afx_msg void OnBnClickedButtonShow();
	CString str_show;
	afx_msg void OnBnClickedButtonSave();
	CComboBox c_cb1;
	CString m_cb1;
	afx_msg void OnSelchangeCombo1();
	void edit_box_show_data(char* data);
	void edit_box_show_data(CString data);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
//	afx_msg void OnEnChangeEdit1();
//	afx_msg void OnEnChangeEdit2();
	CMFCEditBrowseCtrl c_editbrowe;
	void update_data_show(CString cb, bool status_btn_show);
	CButton c_btn_save;
	afx_msg void OnBnClickedOk();
//	afx_msg void OnBnClickedBtnTest();
	CString Split_string(CString str, const char c);
};
