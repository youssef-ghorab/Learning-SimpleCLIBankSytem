#include "../../UI.h"
#include "../../Table/Table.h"
#include "../../../ProccessObjcts/PObictsIncludes.h"
#include "../../TableDiv.h"

class TransferLogUI : UI
{
public:
    TransferLogUI(){}

    void printTable()
    {        
        const int cols = 7;
        std::string initialTxt = "txt";
        const UIsUtulity::FntColor cellTxtColor = UIsUtulity::FntBlack;
        const UIsUtulity::BgColor cellBgColor = UIsUtulity::BgRed;
        const int cellWidth = 22;
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
        baseRow.setCellsTxt(0,0,"Aate-Time");
        baseRow.setCellsTxt(1,1,"S.Acc Number");
        baseRow.setCellsTxt(2,2,"R.Acc number");
        baseRow.setCellsTxt(3,3,"Amout");
        baseRow.setCellsTxt(4,4,"S.Balance Aftr-Trnsfr");
        baseRow.setCellsTxt(5,5,"R.Balance Aftr-Trnsfr");
        baseRow.setCellsTxt(6,6,"Username");
        table.addRow(baseRow);

        //set base row (row of values) proprite
        baseRow.setCellsDelimBgColor(UIsUtulity::BgSkyly);
        baseRow.setCellsDelimFntColor(UIsUtulity::FntBlack);
        baseCell = TableCell(initialTxt,UIsUtulity::FntWhite,UIsUtulity::BgBlue,cellWidth,txtPos);
        baseRow.setAllCells(baseCell);

        //add values rows
        loger::TransferLog log;

        for (const std::string &line : loger::getLog(loger::transferLogFileName))
        {
            log = loger::stringToTransferLog(line);
            baseRow.setCellsTxt(0,0,log.time);
            baseRow.setCellsTxt(1,1,log.senderAccNum);
            baseRow.setCellsTxt(2,2,log.receiverAccNum);
            baseRow.setCellsTxt(3,3,log.amount);
            baseRow.setCellsTxt(4,4,log.sndrBlncAftrTrnsfr);
            baseRow.setCellsTxt(5,5,log.rcvrBlncAftrTrnsfr);
            baseRow.setCellsTxt(6,6,log.username);
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