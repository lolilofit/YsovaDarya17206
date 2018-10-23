#ifndef  CONTEXT_H
#define CONTEXT_H

#include<iostream>
#include<string>
#include<stack>
#include<map>

using namespace std;


class Context {
	map <string, float> defined_arg;
	stack <float> st;

public:
	int count(string name);

	bool is_empty();

	void define_value(string name, float value);

	float find_val(string name);

	void push(float value);

	void pop();

	float top();
};

#endif