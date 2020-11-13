
// practice1.h : PROJECT_NAME アプリケーションのメイン ヘッダー ファイルです
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH に対してこのファイルをインクルードする前に 'pch.h' をインクルードしてください"
#endif

#include "resource.h"		// メイン シンボル


// Cpractice1App:
// このクラスの実装については、practice1.cpp を参照してください
//

class Cpractice1App : public CWinApp
{
public:
	Cpractice1App();

// オーバーライド
public:
	virtual BOOL InitInstance();

// 実装

	DECLARE_MESSAGE_MAP()
};

extern Cpractice1App theApp;
