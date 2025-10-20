#pragma once

#include "../Cell/TableCell.h"
#include "../../ScreenIO/Input.h"
#include "../../CrsrCtrl.h"

class TableRow
{
private:
    struct Segment
    {
        enum type{ Margin , Padding , Delim , Side};
        int order;
        int amount;
        TableCell cell;
    };

    //cells of row
    std::vector <TableCell> cells;
    std::vector <Segment> segments;

    //bg color of row
    UIsUtulity::BgColor bgColor;

    int rightMargin;
    int leftMargin;

    UIsUtulity::BgColor cellsDelimBgColor;
    UIsUtulity::FntColor cellsDelimFntColor;

    int DelimCellAmount;

    std::string cellsDelim;

public:
    //constarcors
    TableRow(const std::vector <TableCell> &cells,const int left_margin,const int right_margin,const UIsUtulity::BgColor bg_color)
    : cells(cells),leftMargin(left_margin),rightMargin(right_margin),bgColor(bg_color){}

    TableRow(const int left_margin,const int right_margin,const UIsUtulity::BgColor bg_color) 
    : leftMargin(left_margin),rightMargin(right_margin),bgColor(bg_color){}

    TableRow() 
    : leftMargin(0),rightMargin(0),bgColor(UIsUtulity::BgBlack){}

    //setters methods
    void setCellsTxtColor(const int start , const int end,const UIsUtulity::FntColor new_val)
    {
        for (int i=start ; i <= end ; i++) cells[i].setTxtColor(new_val);
    }

    void setCellsBgColor(const int start , const int end,const UIsUtulity::BgColor new_val)
    {
        for (int i=start ; i <= end ; i++) cells[i].setBgColor(new_val);
    }

    void setCellsWidth(const int start , const int end,const int new_val)
    {
        for (int i =start ; i <= end ; i++) cells[i].setWidth(new_val);
    }

    void setCellsTxtPos(const int start , const int end,const Output::posType new_val)
    {
        for (int i=start ; i <= end ; i++) cells[i].setTxtPos(new_val);
    }

    void setAllCellsTxt(const std::string& new_val)
    {
        setCellsTxt(0,cells.size()-1,new_val);
    }

    void setAllCellsTxtColor(const UIsUtulity::FntColor new_val)
    {
        setCellsTxtColor(0,cells.size()-1,new_val);
    }

    void setAllCellsBgColor(const UIsUtulity::BgColor new_val)
    {
        setCellsBgColor(0,cells.size()-1,new_val);
    }

    void setAllCellsWidth(const int new_val)
    {
        setCellsWidth(0,cells.size()-1,new_val);
    }

    void setAllCellsTxtPos(const Output::posType new_val)
    {
        setCellsTxtPos(0,cells.size()-1,new_val);
    }

    void setCell(const int cell_index,const TableCell &new_cell)
    {
        cells[cell_index] = new_cell;
    }

    //setters members
    void setCells(const std::vector <TableCell> &cells)
    {
        this->cells = cells;
    }

    void setLeftMargin(const int left_margin) 
    {
        this->leftMargin = left_margin;
    }

    void setRightMargin(const int right_margin) 
    {
        this->rightMargin = right_margin;
    }

    void setBgColor(const UIsUtulity::BgColor bg_color) 
    {
        this->bgColor = bg_color;
    }

    void setCellsDelimBgColor(const UIsUtulity::BgColor new_val)
    {
        cellsDelimBgColor = new_val;
    }

    void setCellsDelimFntColor(const UIsUtulity::FntColor &new_val)
    {
        cellsDelimFntColor = new_val;
    }

    void setCellsDelimAmount(const int new_val)
    {DelimCellAmount = new_val;}

    void setCellsDelim(const std::string &new_val)
    {cellsDelim = new_val;}

    void setAllCells(const TableCell &new_c)
    {
        for (TableCell &c : cells) c = new_c;
    }

    //getters
    const std::vector<TableCell> &getCells() const
    {return cells;}

    int getLeftMargin() const
    {return leftMargin;}

    int getRightMargin() const
    {return rightMargin;}

    UIsUtulity::BgColor getBgColor() const
    {return bgColor;}

    TableCell &getCell(const int cell_index)
    {
        return cells[cell_index];
    }

    UIsUtulity::BgColor getCellsDelimBgColor() const
    {
        return cellsDelimBgColor;
    }

    UIsUtulity::FntColor getCellsDelimFntColor() const
    {return cellsDelimFntColor;}

    int getCellsDelimAmount() const
    {return DelimCellAmount;}

    std::string getCellsDelim() const
    {return cellsDelim;}

    //methods
    void print() const
    {
        if (cells.size() == 0) return;

        UIsUtulity::BgColor currentBgColor=bgColor;
        UIsUtulity::FntColor currentFntColor=UIsUtulity::FntWhite;
        const TableCell * cell_ptr;

        UIsUtulity::setBgColor(bgColor);
        Output::print(std::string(leftMargin,' '));

        for (int i = 0; i < cells.size() ; i++)
        {
            cell_ptr = &cells[i];
            cell_ptr->print(currentBgColor,currentFntColor);
            if (currentBgColor != cellsDelimBgColor) 
            {
                UIsUtulity::setBgColor(cellsDelimBgColor);
                currentBgColor = cellsDelimBgColor;
            }
            if (currentFntColor != cellsDelimFntColor) 
            {
                UIsUtulity::setFntColor(cellsDelimFntColor);
                currentFntColor = cellsDelimFntColor;
            }
            if (i < cells.size()-1) Output::printFor(cellsDelim,DelimCellAmount);
        }

        if (currentBgColor != bgColor) UIsUtulity::setBgColor(bgColor);
        Output::print(std::string(rightMargin,' '));

        UIsUtulity::resetColors();
    }

    //methods
    void print(CursorCtrl &CursorCtrl) const
    {
        if (cells.size() == 0) return;

        UIsUtulity::BgColor currentBgColor=bgColor;
        UIsUtulity::FntColor currentFntColor=UIsUtulity::FntWhite;
        const TableCell * cell_ptr;

        UIsUtulity::setBgColor(bgColor);
        CursorCtrl.output(std::string(leftMargin,' '));

        for (int i = 0; i < cells.size() ; i++)
        {
            cell_ptr = &cells[i];
            cell_ptr->print(currentBgColor,currentFntColor);
            if (currentBgColor != cellsDelimBgColor) 
            {
                UIsUtulity::setBgColor(cellsDelimBgColor);
                currentBgColor = cellsDelimBgColor;
            }
            if (currentFntColor != cellsDelimFntColor) 
            {
                UIsUtulity::setFntColor(cellsDelimFntColor);
                currentFntColor = cellsDelimFntColor;
            }
            if (i < cells.size()-1) CursorCtrl.output(Output::getFor(cellsDelim,DelimCellAmount));
        }

        if (currentBgColor != bgColor) UIsUtulity::setBgColor(bgColor);
        CursorCtrl.output(std::string(rightMargin,' '));

        UIsUtulity::resetColors();
    }

    void addCell(const std::vector <TableCell> &cells)
    {
        for (const TableCell &cell : cells) this->cells.push_back(cell);
    }

    void addCell(const int number_of_cells = 1,const TableCell &cell = TableCell())
    {
        for (int i = 0; i< number_of_cells ; i++) cells.push_back(cell);
    }

    void setCellsTxt( int start , const int end,const std::string& new_val)
    {
        for (start ; start <= end ; start++) cells[start].setTxt(new_val);
    }


};
