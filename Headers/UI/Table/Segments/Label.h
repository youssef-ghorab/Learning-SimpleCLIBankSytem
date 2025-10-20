#include "../Cell//TableCell.h"
#include "Segment.h"
#include "../../ColorManager.h"
#include "UIsUtility.h"
#include "../../ScreenIO/Output.h"
#include "../Skeleton.h"
#include "../Cloth.h"

class Label : public Segment
{
public:
    std::string txt="text";
    ColorManager &colorManager;
    Skeleton skeleton;
    Cloth cloth;

    Label(ColorManager &color_manager) : colorManager(color_manager){}

    Label(const std::string &txt,
        const Cloth &c,
        const Skeleton &s,
        ColorManager &color_manager)
        : txt(txt),
        colorManager(color_manager) ,
        cloth(c),
        skeleton(s)
        {}

    void print() override
    {

    }
    
};  