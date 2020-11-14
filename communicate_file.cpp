#include "pch.h"
#include "communicate_file.h"
#include <cstdio>

item_t item[] = { {"File name,","ASCII",16},
						{"Format Rev.,","ASCII",2},
						{"Total size,","ASCII",4},
						{"USB PID,","ASCII",2},
						{"Reserved,","ASCII",40},
						{"Category,","ASCII",16},
						{"Category ID,","ASCII",2},
						{"Format Rev.,","ASCII",2},
						{"Toltal size,","ASCII",4},
						{"Reserved,","ASCII",8},
						{"Model,","ASCII",32},
						{"Serial number 1,","ASCII",12},
						{"Serial number 2,","ASCII",12},
						{"SoftWare version,","ASCII",64},
						{"Boot version,","ASCII",16},
						{"Set timer,","ASCII",8},
						{"Eapsed time,","ASCII",2},
						{"DipSWê›íË,","ASCII",2},
						{"ÉIÉvÉVÉáÉìê›íË,","ASCII",4} };

// contructor :
ComFile::ComFile()
{
	data_text1 = new char[254];
}

// destructor :
ComFile::~ComFile()
{

}

int ComFile::open(CString dir_file)
{
	fs.open(dir_file);
	if (!fs.is_open())
	{
		return COM_FAIL;
	}
	dir_in_file = dir_file;
	//TRACE(dir_file);
	return COM_OK;
}

void ComFile::close()
{
	fs.close();
}


int ComFile::read1()
{
	if (!fs.is_open())
	{
		return COM_FAIL;
	}
	fs.read(data_text1, LEN_FILE);
	//TRACE(data_text1);
	return COM_OK;
}

int ComFile::read()
{
	std::string temp;
	if (!fs.is_open())
	{
		return COM_FAIL;
	}
	while (getline(fs, temp))
	{
		data_text += temp;
	}

	//TRACE(data_show);
	return COM_OK;
}

int ComFile::write(std::string data)
{
	
	if (!fs.is_open())
	{
		return COM_FAIL;
	}
	
	fs << data;
	return COM_OK;
}

int ComFile::write_csv(std::string data)
{
	// sure file open
	if (!fs.is_open())
	{
		return COM_FAIL;
	}
	

	
	//sprintf_s(b,254,"a = %x",a[0]);

	std::string item_name;
	std::string item_data;
	std::string str_tg;
	char* c_tg = new char[254];

	int size_last = 0;

	for (int j = 0; j < 19; j++)
	{
		item_name = "";
		item_data = "";
		item_name = item[j].name_item;

		for (int i = size_last; i < item[j].size + size_last; i++)
		{
			sprintf_s(c_tg, 254, "%x-", data[i]);
			str_tg = c_tg;
			item_data += str_tg;
		}
		size_last += item[j].size;
		item_data += "\n";

		fs << item_name;
		fs << item_data;
	}
	
	return COM_OK;
}

int ComFile::write_csv(char *data)
{
	
	return COM_OK;
}

int ComFile::cmp_string(std::string a, std::string b,int len)
{
	for (int i = 0; i < len;i++)
	{
		if (a[i] != b[i])
		{
			//cout << "error " << b[i] << endl;
			return COM_FAIL;
		}
	}
	return 0;
}

int ComFile::check_header_file()
{
	std::string header_file;
	for (int i = 0; i < 12;i++)
	{
		header_file += data_text[i];
	}

	//cout << header_file << endl;
	if (cmp_string(header_file, header_file_standard, 12) != 0)
	{
		return COM_FAIL;
	}
	return COM_OK;
}

int ComFile::check_size_file()
{
	if (data_text.length() != LEN_FILE)
	{
		return COM_FAIL;
	}
	return COM_OK;
}

void ComFile::reset()
{
	dir_in_file = "";
	data_text.clear();
}
