#ifndef RARSER_H
#define PARSER_H

#include<iostream>
#include<fstream>
#include<tuple>
#include<string>
#include<cstdio>
#include<sstream>

class Proxy;

template<const int cur, class... Args >
struct iter {
	 void next(std::tuple<Args...>const& tp, std::stringstream& stream_line, char _space) {
		 iter<cur - 1, Args...> _iter;
		 _iter.next(tp, stream_line, _space);
		  std::string _word;
		  std::stringstream word;
		  std::getline(stream_line, _word, _space);
		  word.str(_word);
		  word >> std::get<cur>(tp);
	}
};

template<class... Args>
struct iter<0, Args...> {
	 void next(std::tuple<Args...>const& tp, std::stringstream& stream_line, char _space) {
		std::string _word;
		std::stringstream word;
		std::getline(stream_line, _word, _space);
		word.str(_word);
		word >> std::get<0>(tp);
	}
};

template<class... Args>
struct iter<-1, Args...> {
	 void next(std::tuple<Args...>const& tp, std::stringstream& stream_line, char _space) {}
};


template<class... Args>
class CSVParser {
	std::ifstream &os;
	char _space;
	int after_line;
	int count = 0;


	std::tuple<Args...> make_tuple_str(std::string line) {
		std::stringstream stream_line;
		stream_line << line;
		std::tuple<Args...> _tuple;
		const int _size = sizeof...(Args);
		iter<_size - 1, Args...> _iter;
		_iter.next(_tuple, stream_line, _space);
	}

public:
	CSVParser(std::ifstream &in, const char space, int l) : _space(space), os(in), after_line(l) {};



	class Proxy {
		
	public:
		CSVParser * p;
		std::tuple<Args...> collection_el;
		std::ifstream &os_copy;
		int _size = sizeof...(Args);

		Proxy(std::tuple<Args...> _tuple, std::ifstream &_os) : os_copy(_os) {
			collection_el = _tuple;
			for (int i = 0; i < p->after_line; i++) {
				std::string _line;
				std::getline(os_copy, _line);
			}
		}


		void operator++() {
			(p->count)++;
			std::string line;
			std::getline(os_copy, line);
			std::tuple<Args...> _tuple;
			_tuple = p->make_tuple_str(line);
			this->collection_el = _tuple;
		}

		bool operator!=(Proxy two) {
			int _size = sizeof...(Args);
			if ((two.p->count != this->p->count) && (this->p->count != -1) && (two.p->count != -1))
				return 1;
			if (this->collection_el != two.collection_el)
				return 1;
			
			return 0;
		}

		std::tuple<Args...> operator*() {
			return this->collection_el;
		}
  		
		friend class CSVParser;
	};

	Proxy begin() {

		count = 1;

		std::string line;
		std::getline(os, line);
		os.seekg(0, os.beg);
		std::tuple<Args...> _tuple;
		_tuple = make_tuple_str(line);
		Proxy _begin(_tuple, this->os);
		return _begin;
	}


	Proxy end() {
		count = -1;
		std::string line;
		std::tuple<Args...> _tuple;
		Proxy _end(_tuple, this->os);
		return _end;
	}


	~CSVParser() {}
};

#endif PARSER_H
