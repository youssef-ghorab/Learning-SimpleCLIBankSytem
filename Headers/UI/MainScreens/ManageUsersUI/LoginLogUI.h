#include "../../UI.h"
#include "../../Table/Table.h"
#include "../../../ProccessObjcts/PObictsIncludes.h"
#include "../../TableDiv.h"

class LoginLogUI : UI
{
public:
    LoginLogUI(){}

    void printTable()
    {        
        const int cols = 3;
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
        baseRow.setCellsTxt(0,0,"date-time");
        baseRow.setCellsTxt(1,1,"username");
        baseRow.setCellsTxt(2,2,"permissions");
        table.addRow(baseRow);

        //set base row (row of values) proprite
        baseRow.setCellsDelimBgColor(UIsUtulity::BgSkyly);
        baseRow.setCellsDelimFntColor(UIsUtulity::FntBlack);
        baseCell = TableCell(initialTxt,UIsUtulity::FntWhite,UIsUtulity::BgBlue,cellWidth,txtPos);
        baseRow.setAllCells(baseCell);

        //add values rows
        std::vector<std::string> lineParts;

        for (const std::string &line : loger::getLog(loger::loginLogFileName))
        {
            lineParts = clsString::Split(line,loger::delimiter);
            baseRow.setCellsTxt(0,0,lineParts[0]);
            baseRow.setCellsTxt(1,1,lineParts[1]);
            baseRow.setCellsTxt(2,2,lineParts[2]);
            table.addRow(baseRow);
        }

        Output::print("\n\n\n",true);
        
        TableDiv::display(table,table.getRows().size(),true,0,false);
    }

    void show()
    {

        Output::clearScreen();
        printScreenHeader("balances table",UIsUtulity::BgSkyly,UIsUtulity::FntWhite,UIsUtulity::FntWhite,'*',screen_width);

        printTable();

        Output::pressAnyKeyToContinue();
    }
};