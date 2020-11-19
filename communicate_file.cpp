#include "pch.h"
#include "communicate_file.h"
#include <cstdio>

item_t item[] = {		{"File name,",		"ASCII",16},
						{"Format Rev.,",	"HEX",2},
						{"Total size,",		"UINT32",4},
						{"USB PID,",		"HEX",2},
						{"Reserved,",		"HEX",40},
						{"Category,",		"ASCII",16},
						{"Category ID,",	"HEX",2},
						{"Format Rev.,",	"HEX",2},
						{"Toltal size,",	"UINT32",4},
						{"Reserved,",		"HEX",8},
						{"Model,",			"ASCII",32},
						{"Serial number 1,","ASCII",12},
						{"Serial number 2,","ASCII",12},
						{"SoftWare version,","ASCII",64},
						{"Boot version,",	"ASCII",16},
						{"Set timer,",		"INT64",8},
						{"Eapsed time,",	"INT64",8},
						{"DipSWê›íË,",		"HEX",2},
						{"ÉIÉvÉVÉáÉìê›íË,",	"HEX",4} };

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
	while(fs.read(data_text1, 254))
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
	std::string item_name;
	std::string item_data;
	std::string str_tg;
	char* c_tg = new char[254];
	unsigned long sum = 0;
	unsigned long trung_gian = 0;
	int size_last = 0;
	// sure file open
	if (!fs.is_open())
	{
		return COM_FAIL;
	}

	for (int j = 0; j < 19; j++)
	{
		item_name = "";
		item_data = "";
		item_name = item[j].name_item;
		if (item[j].num_base_sys == "HEX")
		{
			item_data += "0x";
			for (int i = size_last; i < item[j].size + size_last; i++)
			{
				sprintf_s(c_tg, 254, "%x", data[i]);
				str_tg = c_tg;
				item_data += str_tg;
			}
			
		}
		else if (item[j].num_base_sys == "ASCII")
		{
			for (int i = size_last; i < item[j].size + size_last; i++)
			{
				item_data += data[i];
			}
		}
		else
		{
			sum = 0;
			for (int i = size_last; i < item[j].size + size_last; i++)
			{
				trung_gian = (unsigned char)data[i];
				sum = sum + (trung_gian << (8 * (3 - i + size_last)));
				//TRACE(sum);
			}
			sprintf_s(c_tg, 254, "%ld", sum);
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
	if (data_text.size() != LEN_FILE)
	{
		return 1;
	}
	return COM_OK;
}

void ComFile::reset()
{
	dir_in_file = "";
	data_text.clear();
}

int ComFile::create_file_csv(CString dir_out_file)
{
	std::ofstream create_file(dir_out_file);

	create_file.close();
	return 0;
}

