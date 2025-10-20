#pragma once

#include <vector>
#include <string>
#include "UIsUtility.h"
#include "Table/Cell/TableCell.h"
#include "Table/Row/TableRow.h"
#include "Table/Table.h"
#include "TxtBox.h"
#include "CrsrCtrl.h"

class TableDiv
{
public:
    enum class Mode{View=0 , Search};

private:
    static void printPage(const int page,const int total_pages,CursorCtrl &crsrCntrl)
    {
        //display pages
        crsrCntrl.output("\n\t\t\t\t\t\t   page (");
        crsrCntrl.output(Output::getInPos(5,std::to_string(page),Output::Center));
        crsrCntrl.output(" of ");
        crsrCntrl.output(Output::getInPos(5,std::to_string(total_pages),Output::Center));
        crsrCntrl.output(")");
    }

    static void printGuid(const Mode current_mode,const bool &search_enabled,CursorCtrl &cursorCntrl)
    {
        cursorCntrl.output(UIsUtulity::setTxtColor("\n [Esc] exite",UIsUtulity::FntRed));
        switch(current_mode)
        {
            case Mode::View:
            {
                cursorCntrl.output(UIsUtulity::setTxtColor("\n [right arrow] next page - [left  arrow] previous page ",UIsUtulity::FntYallow));
                if (search_enabled)
                { 
                    cursorCntrl.output(UIsUtulity::setTxtColor("\n [F] search\n",UIsUtulity::FntSkyly));
                }
            }
        }

    }

    static void printTableTitle(const Table &table,int &start_idex,const int end_index,CursorCtrl &crsrCntrl,int title_index)
    {
        if (title_index < 0 || title_index >= table.getRows().size()) 
            return;
        table.print(true,title_index,title_index,crsrCntrl);
        if (start_idex < end_index) start_idex++;
    }

    static void printTableBody(const Table &table,int start_idex,const int end_index,CursorCtrl &crsrCntrl)
    {
        table.print(true,start_idex,end_index,crsrCntrl);
    }

    static void calculateIndexs(int &start_index,int &end_index, int &page,const int rows_per_page,const int table_size)
    {
        start_index = (page-1)*rows_per_page;
        end_index = std::min(start_index+rows_per_page-1,table_size-1);
    }

    static void initializeAllowedKeys(std::vector<KeyboardInput::Key> &allowedKeys,const bool search_enabled)
    {
        allowedKeys = {KeyboardInput::ArrLeft,KeyboardInput::ArrRight,KeyboardInput::Esc};
        if (search_enabled)
        {
            allowedKeys.push_back(KeyboardInput::f);
            allowedKeys.push_back(KeyboardInput::F);
        }
    }

    static void startSearch(TxtBox &search_box,Table &t_to_print,Table &org_t,int proprity_to_search_by_index)
    {
        KeyboardInput::Key keypressed;

        keypressed = search_box.startStdCapturingMode({KeyboardInput::Enter});

        t_to_print.clear();

        std::string boxTxt = clsString::LowerAllString(search_box.getValue());
        std::string cellTxt = "";

        if (boxTxt.empty())
        {
            t_to_print = org_t;
            return;
        }
            

        for (TableRow &r : org_t.getRows())
        {
            cellTxt =  clsString::LowerAllString(r.getCell(proprity_to_search_by_index).getTxt());
            if ( cellTxt.find(boxTxt) != std::string::npos) t_to_print.addRow(r);
        }
    }

    static void performKeyAction(KeyboardInput::Key &keyPressed,int &page,const int total_pages,Table &table_to_print, Table &org_table,const int proprity_to_search_by_index,TxtBox &search_box,const bool search_enabled)
    {            
        switch (keyPressed)
        {
            case KeyboardInput::ArrRight:
            {
                if (page < total_pages) page++;
                break;
            }
            case KeyboardInput::ArrLeft:
            {
                if (page > 1) page--;
                break;
            }
            case KeyboardInput::f:
            case KeyboardInput::F:
            {
                if (search_enabled) 
                {
                    startSearch(search_box,table_to_print,org_table,proprity_to_search_by_index);
                    page = 1;
                    keyPressed = KeyboardInput::Key::Enter;
                }
                break;
            }
        }        
    }

public:
    static void display(Table &table,const int rows_per_page,const int title_index = 0,const bool search_eanbled=false,int proprite_to_search_by_index = -1,bool enter_loop=true)
    {
        if (table.getRows().size() == 0)
        {
            Output::print(UIsUtulity::setTxtColor("\n\n\t\t\t\t\t\t! you dont have any data to display !\n\n\n",UIsUtulity::FntYallow),true);
            return;
        }

        Table tToPrint = table;

        std::string modeString[2] = {"View","Search"};

        KeyboardInput::Key keyPressed = KeyboardInput::None;
        int tToPrintSize = tToPrint.getRows().size();

        int page = 1;
        int totalPages = std::ceil((double)tToPrintSize/rows_per_page);
        int startIdex=0;
        int endIndex=0;
        std::vector <KeyboardInput::Key> allowedKeys;
        Mode currentMode = Mode::View;

        CursorCtrl cursorCtrl;

        TxtBox searchBox = TxtBox(50,"press (F) to start search",UIsUtulity::BgBrightWhite,UIsUtulity::FntBrightBlack,Output::Center,"",UIsUtulity::BgBrightWhite,UIsUtulity::FntBlack,Output::Left,1,"<-",UIsUtulity::BgBlack,UIsUtulity::FntWhite,&cursorCtrl);
        
        initializeAllowedKeys(allowedKeys,search_eanbled);

        do
        {            
            Output::clearScreen();

            //print usage guide
            if (enter_loop) printGuid(currentMode,search_eanbled,cursorCtrl);

            tToPrintSize = tToPrint.getRows().size();

            totalPages = std::ceil((double)(tToPrintSize == 0 ? 1 : tToPrintSize)/rows_per_page);

            //calculate start and end index by page
            calculateIndexs(startIdex,endIndex,page,rows_per_page,tToPrintSize);
            
            //print table
            if (tToPrintSize == 0) Output::print(UIsUtulity::setTxtColor("\n\n\t\t\t\t\t\t! no data with indentifier match your search input !\n\n\n",UIsUtulity::FntYallow),true);
            else
            {
                printTableTitle(table,startIdex,endIndex,cursorCtrl,title_index);
                printTableBody(tToPrint,startIdex,endIndex,cursorCtrl);
            }

            if (!enter_loop) break;
            
            //display pages
            printPage(page,totalPages,cursorCtrl);

            cursorCtrl.output("\n\n\n\t\t\t");

            if (search_eanbled) searchBox.displayOnScreen();

            //wait user to presse any one of keys allowed to take action
            keyPressed = KeyboardInput::waitToPressAnyOf(allowedKeys);

            //performe key action
            performKeyAction(keyPressed,page,totalPages,tToPrint,table,proprite_to_search_by_index,searchBox,search_eanbled);
        

        } while (keyPressed != KeyboardInput::Esc);
        
    }
};