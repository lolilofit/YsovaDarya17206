#ifndef  EXEPTIONS_H
#define EXEPTIONS_H
#include<iostream>

class MyExceptions : std::exception {
public:
	virtual const char* what() const throw() { return "exeption happened"; }
};

class PushEcxeption : public MyExceptions {
public:
	const char* what() const throw() override { return "PUSH Failure"; }
};

class Push_lenght : public PushEcxeption {
	const char* what() const throw() override { return "PUSH bad lenght"; }
};

class Push_argument : public PushEcxeption {
	const char* what() const throw() override { return "PUSH bad argument"; }
};

class PopEcxeption : public MyExceptions {
	const char* what() const throw() override { return "POP failure"; }
};

class Pop_lenght : public PopEcxeption {
	const char* what() const throw() override { return "POP bad lenght"; }
};

class Pop_empty : public PopEcxeption {
	const char* what() const throw() override { return "stack is empty"; }
};

class PlusEcxeption : public MyExceptions {
public:
	const char* what() const throw() override { return "+ Failure"; }
};

class Plus_lenght : public PlusEcxeption {
	const char* what() const throw() override { return "Plus bad lenght"; }
};

class Plus_argument : public PlusEcxeption {
	const char* what() const throw() override { return "Plus bad argument"; }
};

class MinusEcxeption : public MyExceptions {
public:
	const char* what() const throw() override { return "- Failure"; }
};

class Minus_lenght : public MinusEcxeption {
	const char* what() const throw() override { return "Minus bad lenght"; }
};

class Minus_argument : public MinusEcxeption {
	const char* what() const throw() override { return "Minus bad argument"; }
};

class DivideEcxeption : public MyExceptions {
public:
	const char* what() const throw() override { return "/ Failure"; }
};

class Divide_lenght : public DivideEcxeption {
	const char* what() const throw() override { return "divide bad lenght"; }
};

class Divide_argument : public DivideEcxeption {
	const char* what() const throw() override { return "Divide bad argument"; }
};

class Divide_ByZero : public DivideEcxeption {
	const char* what() const throw() override { return "Divide by zero"; }
};

class MultiplyEcxeption : public MyExceptions {
public:
	const char* what() const throw() override { return "* Failure"; }
};

class Multiply_lenght : public MultiplyEcxeption {
	const char* what() const throw() override { return "Multiply bad lenght"; }
};

class Multiply_argument : public MultiplyEcxeption {
	const char* what() const throw() override { return "Multiply bad argument"; }
};

class SqrtEcxeption : public MyExceptions {
	const char* what() const throw() override { return "Sqrt failure"; }
};

class Sqrt_lenght : public SqrtEcxeption {
	const char* what() const throw() override { return "Sqrt bad lenght"; }
};

class Sqrt_argument : public SqrtEcxeption {
	const char* what() const throw() override { return "Sqrt bad arguments"; }
};

class Sqrt_negative : public SqrtEcxeption {
	const char* what() const throw() override { return "Sqrt negative argument"; }
};

class PrintEcxeptions : public MyExceptions {
	const char* what() const throw() override { return "Print failure"; }
};

class Print_empty : public PrintEcxeptions {
	const char* what() const throw() override { return "Stack is empty"; }
};

class Print_lenght : public PrintEcxeptions {
	const char* what() const throw() override { return "Print bad lenght"; }
};

class Print_argument : public PrintEcxeptions {
	const char* what() const throw() override { return "Print bad argument"; }
};

class DefineEcxeptions : public MyExceptions {
	const char* what() const throw() override { return "Define failure"; }
};

class Define_lenght : public DefineEcxeptions {
	const char* what() const throw() override { return "Define bad lenght"; }
};

class Define_argument : public DefineEcxeptions {
	const char* what() const throw() override { return "Define bad argument"; }
};

#endif 