#ifndef OPERATIONS_H
#define OPERATIONS_H

#include<iostream>
#include<fstream>
#include<string>
#include<stack>
#include<list>
#include<map>
#include<vector>
#include "Context.h"
#include "exeptions.h"


using namespace std;

class Operations {
public:
	virtual void abstract_operation(list<string> arguments, Context &stack) {};
	bool is_number(string val);
	virtual void catch_ecxeption(list<string> arguments, Context &stack) {};
};


class Base : public Operations {

public:

	void abstract_operation(list<string> arguments, Context &stack) override;
};

class PUSH : public Operations {

public:
	void catch_ecxeption(list<string> arguments, Context &stack) override;

	void abstract_operation(list<string> arguments, Context &stack) override;
};

class POP : public Operations {
public:
	void catch_ecxeption(list<string> arguments, Context &stack) override;

	void abstract_operation(list<string> arguments, Context &stack) override;
};

class PLUS : public Operations {
public:
	void catch_ecxeption(list<string> arguments, Context &stack) override;

	void abstract_operation(list<string> arguments, Context &stack) override;
};

class MINUS : public Operations {
public:
	void catch_ecxeption(list<string> arguments, Context &stack) override;

	void abstract_operation(list<string> arguments, Context &stack) override;
};

class MULTIPLY : public Operations {
public:
	void catch_ecxeption(list<string> arguments, Context &stack) override;

	void abstract_operation(list<string> arguments, Context &stack) override;
};

class DIVIDE : public Operations {
public:
	void catch_ecxeption(list<string> arguments, Context &stack) override;

	void abstract_operation(list<string> arguments, Context &stack) override;
};

class SQRT : public Operations {
public:
	void abstract_operation(list<string> arguments, Context &stack) override;

	void catch_ecxeption(list<string> arguments, Context &stack) override;
};

class PRINT : public Operations {
public:
	void abstract_operation(list<string> arguments, Context &stack) override;

	void catch_ecxeption(list<string> arguments, Context &stack) override;
};

class DEFINE : public Operations {
public:
	void abstract_operation(list<string> arguments, Context &stack) override;

	void catch_ecxeption(list<string> arguments, Context &stack) override;
};

class COMMENT : public Operations {
public:
	void abstract_operation(list<string> arguments, Context &stack) override;
};

#endif 