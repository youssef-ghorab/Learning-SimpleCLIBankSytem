#pragma once

#include "../UI.h"
#include "../../ProccessObjcts/Bank.h"
#include "../UIsUtility.h"
#include "../../IO/IOIncludes.h"
#include "../Table/Table.h"
#include <cmath>
#include "../TableDiv.h"
#include "../Global.h"

class ClientsListUI : public UI
{
private:
    const Bank &bank;

public:
    ClientsListUI(const Bank &bank) : bank(bank){}

    void printTable()
    {
        const int clientsPerPage = 10 ;//clients to display for each page  
        const int cols = 7; //cols of table (cells per row)
        std::string initialTxt = "txt";//initil cells txt
        const UIsUtulity::FntColor cellTxtColor = UIsUtulity::FntBlack;//cells txt color
        const UIsUtulity::BgColor cellBgColor = UIsUtulity::BgRed;//cells background color
        const int cellWidth = 20;//celss width
        const Output::posType txtPos = Output::Center;//txt ancher

        //table to storage info for display
        Table table;

        //row used to add rows to table
        TableRow baseRow;

        //cells of title
        TableCell baseCell(initialTxt,cellTxtColor,cellBgColor,cellWidth,txtPos);

        //add cell of title by initial values
        baseRow.addCell(cols,baseCell);

        //set row of titles
        baseRow.setCellsDelim("|");
        baseRow.setCellsDelimAmount(1);
        baseRow.setCellsDelimBgColor(UIsUtulity::BgBlack);
        baseRow.setCellsDelimFntColor(UIsUtulity::FntWhite);

        //set title row by valide txt
        baseRow.setCellsTxt(0,0,"first name");
        baseRow.setCellsTxt(1,1,"last name");
        baseRow.setCellsTxt(2,2,"email");
        baseRow.setCellsTxt(3,3,"phone number");
        baseRow.setCellsTxt(4,4,"account number");
        baseRow.setCellsTxt(5,5,"pin code");
        baseRow.setCellsTxt(6,6,"balance");

        //add row of titiles
        table.addRow(baseRow);

        //set row of values
        baseRow.setCellsDelimBgColor(UIsUtulity::BgSkyly);
        baseRow.setCellsDelimFntColor(UIsUtulity::FntBlack);

        //set cell of values 
        baseCell = TableCell(initialTxt,UIsUtulity::FntWhite,UIsUtulity::BgBlue,cellWidth,txtPos);

        //set all cells in row values to cell of values
        baseRow.setAllCells(baseCell);

        //add all info of each client to each row rows
        for (const Client &c : bank.getClients())
        {
            //add client info to cells of each row 
            baseRow.setCellsTxt(0,0,c.getFirstName());
            baseRow.setCellsTxt(1,1,c.getLastName());
            baseRow.setCellsTxt(2,2,c.getEmail());
            baseRow.setCellsTxt(3,3,c.getPhoneNumber());
            baseRow.setCellsTxt(4,4,c.getAccountNumber());
            baseRow.setCellsTxt(5,5,c.getPinCode());
            baseRow.setCellsTxt(6,6,std::to_string(c.getBalance()));

            //add row of client info to table
            table.addRow(baseRow);
        }

        //print new lines for format
        Output::print("\n\n\n",true);
        
        //pass the table to display
        TableDiv::display(table,clientsPerPage,0);
    }

    void show()
    {
        if (!currentUser::instance().getUser().getPermissions().hasPermission(Permissions::PermissionTypes::ClientsList))
        {
            UIsUtulity::showAccessDeclineScreen();
            return;
        } 

        Output::clearScreen();
        printScreenHeader("clients table",UIsUtulity::BgSkyly,UIsUtulity::FntWhite,UIsUtulity::FntWhite,'*',screen_width);
        printTable();
        Output::print("\n\n\npress any key to continue...");
        UIsUtulity::printUserCursor(UIsUtulity::Ready,true);
        KeyboardInput::waitToPressAnyKey();
    }
};