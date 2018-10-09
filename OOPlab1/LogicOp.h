#ifndef _LOGICOP_
#define _LOGICOP_
#include"OneTrit.h"
#include "TritSet.h"


TritSet operator&(TritSet &first, TritSet &second);

TritSet operator|(TritSet &first, TritSet &second);

TritSet operator~(TritSet &first);

#endif
