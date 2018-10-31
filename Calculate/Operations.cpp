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
	if (arguments.size() != 1) {
		Push_lenght e;
		throw e;
	}

	if ((!is_number(*(arguments.begin()))) && (stack.count(*(arguments.begin())) == 0)) {
		Push_argument err;
		throw err;
	}

	if (is_number(*(arguments.begin())))
		stack.push(stof(*(arguments.begin())));
	else
		stack.push(stack.find_val(*(arguments.begin())));
}

void POP::abstract_operation(list<string> arguments, Context &stack) {
	if (arguments.size() != 0) {
		Pop_lenght e;
		throw e;
	}

	if (stack.is_empty()) {
		Pop_empty e;
		throw e;
	}
	stack.pop();
}


void PLUS::abstract_operation(list<string> arguments, Context &stack) {
	
	if (arguments.size() >= 2) {
		Plus_lenght e;
		throw e;
	}

	if (arguments.size() >= 2) {
		if (stack.count(*(arguments.begin())) == 0) {
			Plus_argument err_one;
			throw err_one;
		}
		if (arguments.size() == 3) {
			if (stack.count(*(arguments.begin()++)) == 0) {
				Plus_argument err_two;
				throw err_two;
			}
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
	if (arguments.size() > 2) {
		Minus_lenght e;
		throw e;
	}

	if (arguments.size() >= 1) {
		if (stack.count(*(arguments.begin())) == 0) {
			Minus_argument err_one;
			throw err_one;
		}
		if (arguments.size() == 2) {
			if (stack.count(*(arguments.begin()++)) == 0) {
				Minus_argument err_two;
				throw err_two;
			}
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
	
	if (arguments.size() > 2) {
		Multiply_lenght e;
		throw e;
	}

	if (arguments.size() >= 1) {
		if (stack.count(*(arguments.begin())) == 0) {
			Multiply_argument err_one;
			throw err_one;
		}
		if (arguments.size() == 2) {
			if (stack.count(*(arguments.begin()++)) == 0) {
				Multiply_argument err_two;
				throw err_two;
			}
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
	if (arguments.size() > 2) {
		Plus_lenght e;
		throw e;
	}

	if (arguments.size() >= 1) {
		if (stack.count(*(arguments.begin())) == 0) {
			Plus_argument err_one;
			throw err_one;
		}
		if (arguments.size() == 2) {
			if (stack.count(*(arguments.begin()++)) == 0) {
				Plus_argument err_two;
				throw err_two;
			}
			if (*(arguments.begin()++) == "0") {
				Divide_ByZero e;
				throw e;
			}
		}
		else {
			if (*(arguments.begin()) == "0") {
				Divide_ByZero e;
				throw e;
			}
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
		if (stack.count(*(arguments.begin())) == 0) {
			Sqrt_argument e;
			throw e;
		}
	}
	else {
		if (stack.find_val(*(arguments.begin())) < 0) {
			Sqrt_negative e;
			throw e;
		}
	}
	
	if (arguments.size() == 0)
		stack.push(sqrt(stack.top()));
	else
		stack.push(sqrt(stack.find_val(*(arguments.begin()))));
}

void PRINT::abstract_operation(list<string> arguments, Context &stack) {
	if ((arguments.size() == 1) && ((stack.count(*(arguments.begin())) == 0))) {
		Print_argument e;
		throw e;
	}

	if (arguments.size()>1) {
		Print_lenght e;
		throw e;
	}

	if (stack.is_empty()) {
		Print_empty e;
		throw e;
	}
	
	if (arguments.size() == 0)
		cout << stack.top();
	else
		cout << stack.find_val(*(arguments.begin()));
}

void DEFINE::abstract_operation(list<string> arguments, Context &stack) {
	if (arguments.size() != 2) {
		Define_lenght e;
		throw e;
	}

	if (!is_number(*(arguments.begin()++))) {
		Define_argument e;
		throw e;
	}
	stack.define_value(*(arguments.begin()), stof(*(++(arguments.begin()))));
}

void COMMENT::abstract_operation(list<string> arguments, Context &stack) {}