#include "Cexcel.h"
#include <AtlBase.h>
#include <atlconv.h>
using namespace SimpleXlsx;

typedef struct item_excel_s
{
    std::string name_item;
    std::string	num_base_sys;
    int size;
}item_exce_t;

item_exce_t item_excel[] = { {"File name",		"ASCII",16},
                        {"Format Rev.",	"HEX",2},
                        {"Total size",		"UINT32",4},
                        {"USB PID",		"HEX",2},
                        {"Reserved",		"HEX",40},
                        {"Category",		"ASCII",16},
                        {"Category ID",	"HEX",2},
                        {"Format Rev.",	"HEX",2},
                        {"Toltal size",	"UINT32",4},
                        {"Reserved",		"HEX",8},
                        {"Model",			"ASCII",32},
                        {"Serial number 1","ASCII",12},
                        {"Serial number 2","ASCII",12},
                        {"SoftWare version","ASCII",64},
                        {"Boot version",	"ASCII",16},
                        {"Set timer",		"INT64",8},
                        {"Eapsed time",	"INT64",8},
                        {"DipSW設定",		"HEX",2},
                        {"オプション設定",	"HEX",4} };

CEXCEL::CEXCEL()
{

}

CEXCEL::~CEXCEL()
{

}

std::wstring CEXCEL::convert_str_to_wstring(std::string str)
{
    CA2W ca2w(str.c_str());
    std::wstring w = ca2w;
    return w;
}

int CEXCEL::write_file(std::string dir,std::string data_excel)
{ 
    setlocale(LC_ALL, "");
    time_t CurTime = time(NULL);

    CWorkbook book("Incognito");
    std::vector<ColumnWidth> ColWidth;
    ColWidth.push_back(ColumnWidth(0, 3, 25));
    CWorksheet& Sheet = book.AddSheet("DATA", ColWidth);

    Style style;
    style.horizAlign = ALIGN_H_CENTER;
    style.font.attributes = FONT_BOLD;
    const size_t CenterStyleIndex = book.AddStyle(style);

    Font TmpFont = book.GetFonts().front();
    TmpFont.attributes = FONT_ITALIC;

    std::string item_name;
    std::string item_data;
    std::string str_tg;
    char* c_tg = new char[254];
    unsigned long sum = 0;
    unsigned long trung_gian = 0;
    int size_last = 0;
    // sure file open

    for (int j = 0; j < 19; j++)
    {
        item_name = "";
        item_data = "";
        item_name = item_excel[j].name_item;
        if (item_excel[j].num_base_sys == "HEX")
        {
            item_data += "0x";
            for (int i = size_last; i < item_excel[j].size + size_last; i++)
            {
                sprintf_s(c_tg, 254, "%x", data_excel[i]);
                str_tg = c_tg;
                item_data += str_tg;
            }

        }
        else if (item_excel[j].num_base_sys == "ASCII")
        {
            for (int i = size_last; i < item_excel[j].size + size_last; i++)
            {
                item_data += data_excel[i];
            }
        }
        else
        {
            sum = 0;
            for (int i = size_last; i < item_excel[j].size + size_last; i++)
            {
                trung_gian = (unsigned char)data_excel[i];
                sum = sum + (trung_gian << (8 * (3 - i + size_last)));
                //TRACE(sum);
            }
            sprintf_s(c_tg, 254, "%ld", sum);
            str_tg = c_tg;
            item_data += str_tg;
        }
        size_last += item_excel[j].size;
        Sheet.BeginRow().AddCell(convert_str_to_wstring(item_name)).AddCell(item_data).EndRow();
    }


    if (book.Save(dir))
    {

    }
    else
    {
        return CEXCEL_FAIL;
    }
    return CEXCEL_OK;
}


int CEXCEL::main()
{
    setlocale(LC_ALL, "");
    time_t CurTime = time(NULL);

    CWorkbook book("Incognito");
    std::vector<ColumnWidth> ColWidth;
    ColWidth.push_back(ColumnWidth(0, 3, 25));
    CWorksheet& Sheet = book.AddSheet("Unicode", ColWidth);

    Style style;
    style.horizAlign = ALIGN_H_CENTER;
    style.font.attributes = FONT_BOLD;
    const size_t CenterStyleIndex = book.AddStyle(style);

    Sheet.BeginRow();
    Sheet.AddCell("Common test of Unicode support", CenterStyleIndex);
    Sheet.MergeCells(CellCoord(1, 0), CellCoord(1, 3));
    Sheet.EndRow();

    /*Font TmpFont = book.GetFonts().front();
    TmpFont.attributes = FONT_ITALIC;*/

    Sheet.BeginRow().AddCell("English language").AddCell("English language").EndRow();


    if (book.Save("Simple.xlsx"))
    {

    }
    else
    {
        return CEXCEL_FAIL;
    }
    return CEXCEL_OK;
}
