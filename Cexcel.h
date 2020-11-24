#pragma once


#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <vector>
//#include "pch.h"
#include "lib_excel/Xlsx/Workbook.h"
#include <windows.h>


#define CEXCEL_OK	0
#define CEXCEL_FAIL	1

class CEXCEL
{
public:
	CEXCEL();
	~CEXCEL();
	int main();
	int write_file(std::string dir, std::string data_excel);
private:

protected:

};

