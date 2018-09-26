#ifndef _LOGICOP_
#define _LOGICOP_
#include"OneTrit.h"
#include "TritArr.h"


TritArr operator&(TritArr &first, TritArr &second);

TritArr operator|(TritArr &first, TritArr &second);

TritArr operator~(TritArr &first);

#endif