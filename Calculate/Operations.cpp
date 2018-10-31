#include "Operations.h"
#include<regex>


void Base::abstract_operation(list<string> arguments, Context &stack) {}

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
	
	if (arguments.size() > 1) {
		Sqrt_lenght e;
		throw e;
	}

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
		cout << stack.top();
	else
		cout << stack.find_val(*(arguments.begin()));
}

void DEFINE::abstract_operation(list<string> arguments, Context &stack) {
	if (arguments.size() != 2)
		throw Define_lenght();

	if (!is_number(*(arguments.begin()++))) 
		throw Define_argument();
	
	stack.define_value(*(arguments.begin()), stof(*(++(arguments.begin()))));
}

void COMMENT::abstract_operation(list<string> arguments, Context &stack) {}