#ifndef  EXEPTIONS_H
#define EXEPTIONS_H
#include<iostream>

class MyExceptions : std::exception {
public:
	virtual const char* what() const throw() { return "exeption happened"; }
};

class Push_lenght : public MyExceptions {
	const char* what() const throw() override { return "PUSH bad lenght"; }
};

class Push_argument : public MyExceptions {
	const char* what() const throw() override { return "PUSH bad argument"; }
};

class Pop_lenght : public MyExceptions {
	const char* what() const throw() override { return "POP bad lenght"; }
};

class Pop_empty : public MyExceptions {
	const char* what() const throw() override { return "stack is empty"; }
};

class Plus_lenght : public MyExceptions {
	const char* what() const throw() override { return "Plus bad lenght"; }
};

class Plus_argument : public MyExceptions {
	const char* what() const throw() override { return "Plus bad argument"; }
};

class Minus_lenght : public MyExceptions {
	const char* what() const throw() override { return "Minus bad lenght"; }
};

class Minus_argument : public MyExceptions {
	const char* what() const throw() override { return "Minus bad argument"; }
};

class Divide_lenght : public MyExceptions {
	const char* what() const throw() override { return "divide bad lenght"; }
};

class Divide_argument : public MyExceptions {
	const char* what() const throw() override { return "Divide bad argument"; }
};

class Divide_ByZero : public MyExceptions {
	const char* what() const throw() override { return "Divide by zero"; }
};

class Multiply_lenght : public MyExceptions {
	const char* what() const throw() override { return "Multiply bad lenght"; }
};

class Multiply_argument : public MyExceptions {
	const char* what() const throw() override { return "Multiply bad argument"; }
};

class Sqrt_lenght : public MyExceptions {
	const char* what() const throw() override { return "Sqrt bad lenght"; }
};

class Sqrt_argument : public MyExceptions {
	const char* what() const throw() override { return "Sqrt bad arguments"; }
};

class Sqrt_negative : public MyExceptions {
	const char* what() const throw() override { return "Sqrt negative argument"; }
};

class Print_empty : public MyExceptions {
	const char* what() const throw() override { return "Stack is empty"; }
};

class Print_lenght : public MyExceptions {
	const char* what() const throw() override { return "Print bad lenght"; }
};

class Print_argument : public MyExceptions {
	const char* what() const throw() override { return "Print bad argument"; }
};

class Define_lenght : public MyExceptions {
	const char* what() const throw() override { return "Define bad lenght"; }
};

class Define_argument : public MyExceptions {
	const char* what() const throw() override { return "Define bad argument"; }
};

#endif 