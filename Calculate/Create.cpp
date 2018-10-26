#include "Create.h"

Operations* CreatePush::make() {
	return new PUSH();
}
Operations* CreatePop::make() {
	return new POP();
}

Operations* CreatePlus::make() {
	return new PLUS();
}

Operations* CreateMinus::make() {

	return new MINUS();
}

Operations* CreateDivide::make() {
	return new DIVIDE();
}

Operations* CreateMultiply::make() {
	return new MULTIPLY();
}
Operations* CreateSqrt::make() {
	return new SQRT();
}

Operations* CreatePrint::make() {
	return new PRINT();
}

Operations* CreateDefine::make() {
	return new DEFINE();
}

Operations* CreateComment::make() {
	return new COMMENT();
}