#include "../../UI.h"
#include "../../../ProccessObjcts/Bank.h"
#include "../../Table/Table.h"
#include "../../Table/Row/TableRow.h"
#include "../../Table/Cell/TableCell.h"
#include "../../TableDiv.h"

class TotalBalancesUI : UI
{
private:
    Bank &bank;

public:
    TotalBalancesUI(Bank &bank) : bank(bank){}

    void printTable()
    {        
        const int cols = 5;
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
        baseRow.setCellsTxt(0,0,"first name");
        baseRow.setCellsTxt(1,1,"last name");
        baseRow.setCellsTxt(2,2,"account number");
        baseRow.setCellsTxt(3,3,"pin code");
        baseRow.setCellsTxt(4,4,"balance");
        table.addRow(baseRow);

        //set base row (row of values) proprite
        baseRow.setCellsDelimBgColor(UIsUtulity::BgSkyly);
        baseRow.setCellsDelimFntColor(UIsUtulity::FntBlack);
        baseCell = TableCell(initialTxt,UIsUtulity::FntWhite,UIsUtulity::BgBlue,cellWidth,txtPos);
        baseRow.setAllCells(baseCell);

        //add values rows
        for (const Client &c : bank.getClients())
        {
            baseRow.setCellsTxt(0,0,c.getFirstName());
            baseRow.setCellsTxt(1,1,c.getLastName());
            baseRow.setCellsTxt(2,2,c.getAccountNumber());
            baseRow.setCellsTxt(3,3,c.getPinCode());
            baseRow.setCellsTxt(4,4,std::to_string(c.getBalance()));
            table.addRow(baseRow);
        }

        Output::print("\n\n\n",true);
        
        TableDiv::display(table,table.getRows().size(),true,0,false);
    }

    void show()
    {
        float totalBalances=0;
        for (const Client &c : bank.getClients()){totalBalances+=c.getBalance();};

        Output::clearScreen();
        printScreenHeader("balances table",UIsUtulity::BgSkyly,UIsUtulity::FntWhite,UIsUtulity::FntWhite,'*',50);

        printTable();
        Output::print("\n balances total :"+std::to_string(totalBalances),true);

        Output::pressAnyKeyToContinue();
    }
};