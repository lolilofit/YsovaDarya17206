#include "Operations.h"
#include<regex>
#include "Create.h"
#include "Factory.h"

namespace {

	bool init() {

		CreatePush* _push = new CreatePush();
		CreatePop* _pop = new CreatePop();
		CreatePlus* _plus = new CreatePlus();
		CreateMinus* _minus = new CreateMinus();
		CreateDivide* _divide = new CreateDivide();
		CreateMultiply* _mult = new CreateMultiply();
		CreateSqrt* _sqrt = new CreateSqrt();
		CreatePrint* _print = new CreatePrint();
		CreateDefine* _def = new CreateDefine();
		CreateComment* _comment = new CreateComment();
		Factory::get_instance().init_cmd("PUSH", _push);
		Factory::get_instance().init_cmd("POP", _pop);
		Factory::get_instance().init_cmd("+", _plus);
		Factory::get_instance().init_cmd("-", _minus);
		Factory::get_instance().init_cmd("/", _divide);
		Factory::get_instance().init_cmd("*", _mult);
		Factory::get_instance().init_cmd("SQRT", _sqrt);
		Factory::get_instance().init_cmd("PRINT", _print);
		Factory::get_instance().init_cmd("DEFINE", _def);
		Factory::get_instance().init_cmd("#", _comment);

		return true;
	}
	bool initial = init();
}


bool is_number(string val) {
	regex num("[-]*""[0-9]*"".""[0-9]*");
	if(regex_match(val, num))
	 return 1;
	return 0;
}

void PUSH::abstract_operation(list<string> arguments, Context &stack) {
	if (arguments.size() != 1) 
		throw Push_lenght();
	
	if ((!is_number(*(arguments.begin()))) && (stack.count(*(arguments.begin())) == 0)) 
		throw Push_argument();
	

	if (is_number(*(arguments.begin())))
		stack.push(stof(*(arguments.begin())));
	else
		stack.push(stack.find_val(*(arguments.begin())));
}

void POP::abstract_operation(list<string> arguments, Context &stack) {
	if (arguments.size() != 0) 
		throw Pop_lenght();
	

	if (stack.is_empty()) 
		throw Pop_empty();
	
	stack.pop();
}


void PLUS::abstract_operation(list<string> arguments, Context &stack) {
	
	if (arguments.size() >= 2) 
		throw Plus_lenght();
	
	if (arguments.size() >= 2) {
		if (stack.count(*(arguments.begin())) == 0) 
			throw Plus_argument();
		
		if (arguments.size() == 3) {
			if (stack.count(*(arguments.begin()++)) == 0)
				throw Plus_argument();
		}
	}
	
	if (arguments.size() == 0) {
		float first = stack.top();
		stack.pop();
		float second = stack.top();
		stack.pop();
		stack.push(first + second);
	}
	else {
		if (arguments.size() == 1) {
			float first = stack.find_val(*(arguments.begin()));
			float second = stack.top();
			stack.pop();
			stack.push(first + second);
		}
		else {
			float first = stack.find_val(*(arguments.begin()));
			float second = stack.find_val(*(++arguments.begin()));
			stack.push(first + second);
		}
	}
}

void MINUS::abstract_operation(list<string> arguments, Context &stack) {
	if (arguments.size() > 2) 
		throw Minus_lenght();
	
	if (arguments.size() >= 1) {
		if (stack.count(*(arguments.begin())) == 0) 
			throw Minus_argument();
		
		if (arguments.size() == 2) {
			if (stack.count(*(arguments.begin()++)) == 0)
				throw Minus_argument();
		}
	}
	
	if (arguments.size() == 0) {
		float first = stack.top();
		stack.pop();
		float second = stack.top();
		stack.pop();
		stack.push(first - second);
	}
	else {
		if (arguments.size() == 1) {
			float first = stack.find_val(*(arguments.begin()));
			float second = stack.top();
			stack.pop();
			stack.push(first - second);
		}
		else {
			float first = stack.find_val(*(arguments.begin()));
			float second = stack.find_val(*(++arguments.begin()));
			stack.push(first - second);
		}
	}
}

void MULTIPLY::abstract_operation(list<string> arguments, Context &stack) {
	
	if (arguments.size() > 2) 
		throw Multiply_lenght();
	

	if (arguments.size() >= 1) {
		if (stack.count(*(arguments.begin())) == 0) 
			throw Multiply_argument();
		
		if (arguments.size() == 2) {
			if (stack.count(*(arguments.begin()++)) == 0)
				throw Multiply_argument();
		}
	}
	
	if (arguments.size() == 0) {
		float first = stack.top();
		stack.pop();
		float second = stack.top();
		stack.pop();
		stack.push(first * second);
	}
	else {
		if (arguments.size() == 1) {
			float first = stack.find_val(*(arguments.begin()));
			float second = stack.top();
			stack.pop();
			stack.push(first * second);
		}
		else {
			float first = stack.find_val(*(arguments.begin()));
			float second = stack.find_val(*(++arguments.begin()));
			stack.push(first * second);
		}
	}
}

void DIVIDE::abstract_operation(list<string> arguments, Context &stack) {
	if (arguments.size() > 2)
		throw Divide_lenght();
	
	if (arguments.size() >= 1) {
		if (stack.count(*(arguments.begin())) == 0)
			throw Divide_argument();
		
		if (arguments.size() == 2) {
			if (stack.count(*(arguments.begin()++)) == 0) 
				throw Divide_argument();
			
			if (*(arguments.begin()++) == "0") 
				throw Divide_ByZero();
		}
		else {
			if (*(arguments.begin()) == "0") 
				throw Divide_ByZero();
		}
	}
	
	if (arguments.size() == 0) {
		float first = stack.top();
		stack.pop();
		float second = stack.top();
		stack.pop();
		stack.push(first / second);
	}
	else {
		if (arguments.size() == 1) {
			float first = stack.find_val(*(arguments.begin()));
			float second = stack.top();
			stack.pop();
			stack.push(first / second);
		}
		else {
			float first = stack.find_val(*(arguments.begin()));
			float second = stack.find_val(*(++arguments.begin()));
			stack.push(first / second);
		}
	}
}

void SQRT::abstract_operation(list<string> arguments, Context &stack) {
	
	if (arguments.size() > 1) 
		throw Sqrt_lenght();

	if (arguments.size() == 1) {
		if (stack.count(*(arguments.begin())) == 0) 
			throw Sqrt_argument();
	}
	else {
		if (stack.find_val(*(arguments.begin())) < 0) 
			throw Sqrt_negative();
	}
	
	if (arguments.size() == 0)
		stack.push(sqrt(stack.top()));
	else
		stack.push(sqrt(stack.find_val(*(arguments.begin()))));
}

void PRINT::abstract_operation(list<string> arguments, Context &stack) {
	if ((arguments.size() == 1) && ((stack.count(*(arguments.begin())) == 0)))
		throw Print_argument();
	
	if (arguments.size()>1) 
		throw Print_lenght();

	if (stack.is_empty()) 
		throw Print_empty();
	
	if (arguments.size() == 0)
		cout << stack.top()<<endl;
	else
		cout << stack.find_val(*(arguments.begin())) << endl;
}

void DEFINE::abstract_operation(list<string> arguments, Context &stack) {
	if (arguments.size() != 2)
		throw Define_lenght();

	if (!is_number(*(arguments.begin()++))) 
		throw Define_argument();
	
	stack.define_value(*(arguments.begin()), stof(*(++(arguments.begin()))));
}

void COMMENT::abstract_operation(list<string> arguments, Context &stack) {}