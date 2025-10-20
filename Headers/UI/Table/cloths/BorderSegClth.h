#include "Cloth.h"
#include "../UIsUtility.h"
#include "../Cell/TableCell.h"

struct BordredSegmentsClth : public Cloth
{
    TableCell border;
};