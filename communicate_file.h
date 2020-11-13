#pragma once

#include <iostream>
#include <string>
#include <fstream>

#define header_file_standard "JCM DEV LOG"
#define LEN_FILE				254

#define COM_OK		0    // not error
#define COM_FAIL	1	// error

// class file
class ComFile
{
public:
	ComFile();  // contructor
	~ComFile(); // destructor
	std::string data_text;
	CString data_show;
	int open(CString dir_file);    // open file
	int read(); // read from file
	int write(std::string data); // write to file
	int check_header_file();
	int check_size_file();
	void close();    // open file
	void reset();
private:
	std::fstream fs;       // object
	CString dir_in_file;  // 
	int cmp_string(std::string a, std::string b, int len);

	
};
