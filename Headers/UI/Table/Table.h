#pragma once

#include <vector>
#include <string>
#include "../UIsUtility.h"
#include "Row/TableRow.h"

class Table
{
private:
    std::vector <std::string> titles;
    std::vector<TableRow> rows;

public:

    Table() {}

    void addRow()
    {
        TableRow row = TableRow();
        rows.push_back(row);
    }

    void addRow(const TableRow &row)
    {
        rows.push_back(row);
    }

    void addRowsEffect(const int number_of_rows,const TableRow &row)
    {
        for(int i = 0; i< number_of_rows ;i++) rows.push_back(row);
    }

    void addRows(const int number_of_rows,const TableRow &row)
    {
        for(int i = 0; i< number_of_rows ;i++) rows.push_back(TableRow(row));
    }

    void addRows(const std::vector<TableRow> &Rows)
    {
        for(const TableRow &row : Rows) rows.push_back(row);
    }

    void addRows(const int number_of_rows)
    {
        for (int i= 0; i< number_of_rows;i++) rows.push_back(TableRow());
    }

    void setRowCellsTxt(int start_row ,const int end_row,int start_cell, const int end_cell,const std::string& new_val)
    {
        for (start_row ; end_row <= end_row ; start_row++) rows[start_row].setCellsTxt(start_cell,end_cell,new_val);
    }

    void setRowCellsTxtColor(int start_row ,const int end_row,int start_cell, const int end_cell,const UIsUtulity::FntColor new_val)
    {
        for (start_row ; end_row <= end_row ; start_row++) rows[start_row].setCellsTxtColor(start_cell,end_cell,new_val);
    }

    void setRowCellsBgColor(int start_row ,const int end_row,int start_cell, const int end_cell,const UIsUtulity::BgColor new_val)
    {
        for (start_row ; end_row <= end_row ; start_row++) rows[start_row].setCellsBgColor(start_cell,end_cell,new_val);
    }

    void setRowCellsWidth(int start_row ,const int end_row,int start_cell, const int end_cell,const int new_val)
    {
        for (start_row ; end_row <= end_row ; start_row++) rows[start_row].setCellsWidth(start_cell,end_cell,new_val);
    }

    void setRowCellsBgColor(int start_row ,const int end_row,int start_cell, const int end_cell,const Output::posType new_val)
    {
        for (start_row ; end_row <= end_row ; start_row++) rows[start_row].setCellsTxtPos(start_cell,end_cell,new_val);
    }

    void addRows(const int number_of_rows,const int cells_per_row)
    {
        TableRow row;
        row.addCell(cells_per_row);
        for (int i= 0; i< number_of_rows;i++) rows.push_back(row);
    }

    TableRow &getRow(const int row_index)
    {
        return rows[row_index];
    }

    void setRow(const int row_index,const TableRow &new_row)
    {
        rows[row_index] = new_row;
    }

    void setRowCell(const int row_index , const int cell_index,TableCell new_cell)
    {
        rows[row_index].setCell(cell_index,new_cell); 
    }

    void print(const bool each_row_in_new_line) const
    {
        for (const TableRow &row : rows) 
        {
            if (each_row_in_new_line) Output::print("\n",false);
            row.print();
        }
    }

    void print(const bool each_row_in_new_line,const int start , const int end) const
    {
        for (int i = start ; i <= end ;i++) 
        {
            if (each_row_in_new_line) Output::print("\n",false);
            rows[i].print();
        }
    }

    void print(const bool each_row_in_new_line,const int start , const int end,CursorCtrl &crsrCntrl) const
    {
        for (int i = start ; i <= end ;i++) 
        {
            if (each_row_in_new_line) crsrCntrl.output("\n");
            rows[i].print(crsrCntrl);
        }
    }

    std::vector<TableRow> &getRows()
    {return rows;}

    const std::vector<TableRow> &getRows() const
    {return rows;}

    void clear()
    {rows.clear();}

};