#pragma once

#include <iostream>
#include <string>
#include <fstream>

#define header_file_standard "JCM DEV LOG"
#define LEN_FILE				254

#define COM_OK		0    // not error
#define COM_FAIL	1	// error

typedef struct item_s
{
	std::string name_item;
	std::string	num_base_sys;
	int size;
}item_t;

// class file
class ComFile
{
public:
	ComFile();  // contructor
	~ComFile(); // destructor
	std::string data_text;
	char *data_text1;
	int open(CString dir_file);    // open file
	int read(); // read from file
	int read1();
	int write(std::string data); // write to file
	int write_csv(std::string data);
	int write_csv(char *data);
	int check_header_file();
	int check_size_file();
	void close();    // open file
	void reset();	// reset 
	void create_file(CString dir_out_file);  // create file
private:
	std::fstream fs;       // object
	CString dir_in_file;  // 

	int cmp_string(std::string a, std::string b, int len);

	
};
