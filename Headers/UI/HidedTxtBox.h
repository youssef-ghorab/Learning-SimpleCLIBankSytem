#include "TxtBox.h"

class HidedTxtBoxV2 : public TxtBox
{
private:
    char symbole = '*';
    std::string txtOnHideForm="";
    std::string txtOnShowForm="";
    bool isTxtHided=true;

    std::string getTxtHidedForm()
    {
        return std::string(getValue().length(),symbole);
    }

public:
    HidedTxtBoxV2(const int box_width,const std::string& initial_txt,UIsUtulity::BgColor initial_txt_bg_color ,UIsUtulity::FntColor initial_txt_color,Output::posType initial_txt_ancher, const std::string&value,UIsUtulity::BgColor value_bg_color,UIsUtulity::FntColor value_color,Output::posType value_ancher ,const int spaces_btw_txt_box_and_flag,const std::string &is_current_flag_symbole,UIsUtulity::BgColor is_current_flag_bg_color, UIsUtulity::FntColor is_current_flag_color,CursorCtrl * cursor,const bool hide_value)
    :TxtBox(box_width,initial_txt,initial_txt_bg_color,initial_txt_color,initial_txt_ancher,value,value_bg_color,value_color,value_ancher,spaces_btw_txt_box_and_flag,is_current_flag_symbole,is_current_flag_bg_color,is_current_flag_color,cursor)
    {
        if (hide_value) hideTxt(true);
        else showValue(true);
    }

    void hideTxt(const bool update_on_screen=true)
    {
        if (isTxtHided) return;
        setValue(txtOnHideForm);
        if (update_on_screen) updateOnscreen();
        isTxtHided =true;
    }

    void showValue(const bool update_on_screen=true)
    {
        if (!isTxtHided) return;
        setValue(txtOnShowForm);
        if (update_on_screen) updateOnscreen();
        isTxtHided = false;
    }

    char getHideSymbole()
    {
        return symbole;
    }

    void setHideSymbole(const char new_val)
    {
        symbole = new_val;
    }

    void valuePush(const char &c,const bool update_on_screen=true) override
    {
        if (isTxtHided) TxtBox::valuePush(symbole,update_on_screen);
        else TxtBox::valuePush(c,update_on_screen);
        txtOnShowForm += c;
        txtOnHideForm += symbole;
    }

    void valuePop(const bool update_on_screen= true)
    {
        if (txtOnHideForm.empty()) return;
        txtOnHideForm.pop_back();
        txtOnShowForm.pop_back();
        TxtBox::valuePop(update_on_screen);
    }

    void stdReset() override
    {
        txtOnHideForm = "";
        txtOnShowForm = "";
        TxtBox::stdReset();
    }

    std::string getValue() const override
    {
        return txtOnShowForm;
    }
};