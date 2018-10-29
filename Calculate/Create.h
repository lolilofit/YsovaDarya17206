#ifndef CALC_H
#define CALC_H

#include<iostream>
#include<fstream>
#include<string>
#include<stack>
#include<list>
#include<map>
#include<vector>
#include "Context.h"
#include "Operations.h"
#include "exeptions.h"
#include "Factory.h"


class CreatePush : public Create {
	Operations* make() override;
};

class CreatePop : public Create {
	Operations* make() override;
};


class CreatePlus : public Create {
	Operations* make() override;
};

class CreateMinus : public Create {
	Operations* make() override;
};

class CreateDivide : public Create {
	Operations* make() override;
};

class CreateMultiply : public Create {
	Operations* make() override;
};

class CreateSqrt : public Create {
	Operations* make() override;
};

class CreatePrint : public Create {
	Operations* make() override;
};

class CreateDefine : public Create {
	Operations* make() override;
};

class CreateComment : public Create {
	Operations* make() override;
};


#endif 