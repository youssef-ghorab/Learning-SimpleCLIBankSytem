#include "../../UI.h"
#include "../../../ProccessObjcts/Bank.h"
#include "../../Table/Table.h"
#include "../../Table/Row/TableRow.h"
#include "../../Table/Cell/TableCell.h"
#include "../../TableDiv.h"
#include "../../../ProccessObjcts/Currency.h"

class CurrencyTableUI : UI
{
private:
    Bank &bank;

public:
    CurrencyTableUI(Bank &bank) : bank(bank){}

    void printTable()
    {        
        const int cols = 4;
        std::string initialTxt = "txt";
        const UIsUtulity::FntColor cellTxtColor = UIsUtulity::FntBlack;
        const UIsUtulity::BgColor cellBgColor = UIsUtulity::BgRed;
        const int cellWidth = 30;
        const Output::posType txtPos = Output::Center;

        Table table;
        TableRow baseRow;
        TableCell baseCell(initialTxt,cellTxtColor,cellBgColor,cellWidth,txtPos);

        baseRow.addCell(cols,baseCell);

        //set base row (row of title) proprite
        baseRow.setCellsDelim("|");
        baseRow.setCellsDelimAmount(1);
        baseRow.setCellsDelimBgColor(UIsUtulity::BgBlack);
        baseRow.setCellsDelimFntColor(UIsUtulity::FntWhite);

        //add title row
        baseRow.setCellsTxt(0,0,"Country");
        baseRow.setCellsTxt(1,1,"Code");
        baseRow.setCellsTxt(2,2,"Name");
        baseRow.setCellsTxt(3,3,"Rate");
        table.addRow(baseRow);

        //set base row (row of values) proprite
        baseRow.setCellsDelimBgColor(UIsUtulity::BgSkyly);
        baseRow.setCellsDelimFntColor(UIsUtulity::FntBlack);
        baseCell = TableCell(initialTxt,UIsUtulity::FntWhite,UIsUtulity::BgBlue,cellWidth,txtPos);
        baseRow.setAllCells(baseCell);

        //add values rows
        for (const Currency &c : bank.getCurrencies())
        {
            baseRow.setCellsTxt(0,0,c.getCountry());
            baseRow.setCellsTxt(1,1,c.getCode());
            baseRow.setCellsTxt(2,2,c.getName());
            baseRow.setCellsTxt(3,3,std::to_string(c.getRate()));
            table.addRow(baseRow);
        }

        Output::print("\n\n\n",true);
        
        TableDiv::display(table,10,0,true,0,true);
    }

    void show()
    {
        Output::clearScreen();
        printScreenHeader("Currencies table",UIsUtulity::BgSkyly,UIsUtulity::FntWhite,UIsUtulity::FntWhite,'*',50);

        printTable();

        Output::pressAnyKeyToContinue();
    }
};