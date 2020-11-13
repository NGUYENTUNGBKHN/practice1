#include "pch.h"
#include "communicate_file.h"


// contructor :
ComFile::ComFile()
{

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
		return 1;
	}
	dir_in_file = dir_file;
	//TRACE(dir_file);
	return 0;
}

void ComFile::close()
{
	fs.close();
}


int ComFile::read()
{
	if (!fs.is_open())
	{
		return 1;
	}
	while (getline(fs, data))
	{
		
	}

	for (int i = 0; i < data.length();i++)
	{
		if (data[i] == 0x00)
		{
			data_show += " ";
		}
		else
		{
			data_show += data[i];
		}
	}
	//TRACE(data_show);
	return 0;
}

int ComFile::write()
{
	
	if (!fs.is_open())
	{
		return 1;
	}
	
	fs << data;
	return 0;
}

int ComFile::cmp_string(std::string a, std::string b,int len)
{
	for (int i = 0; i < len;i++)
	{
		if (a[i] != b[i])
		{
			//cout << "error " << b[i] << endl;
			return 1;
		}
	}
	return 0;
}

int ComFile::check_header_file()
{
	std::string header_file;
	for (int i = 0; i < 12;i++)
	{
		header_file += data[i];
	}

	//cout << header_file << endl;
	if (cmp_string(header_file, header_file_standard, 12) != 0)
	{
		return 1;
	}
	return 0;
}

int ComFile::check_size_file()
{
	if (data.length() != 254)
	{
		return 1;
	}
	return 0;
}

void ComFile::reset()
{
	dir_in_file = "";
	data = "";
	data_show = "";
}
