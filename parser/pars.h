#ifndef RARSER_H
#define PARSER_H

#include<iostream>
#include<fstream>
#include<tuple>
#include<string>
#include<cstdio>
#include<sstream>

class Proxy;

template<int ind, class Args>
struct convert {
	Args dog(std::string src) {
		Args result;
		std::stringstream buff(src);
		buff >> result;
		return result;
	}
};

template<int ind>
struct convert<ind, std::string> {
	std::string dog(std::string src) {
		return src;
	}
};

template<const int cur, class... Args >
struct iter {
	 void next(std::tuple<Args...>& tp, std::stringstream& stream_line, char _space) {
		 iter<cur - 1, Args...> _iter;
		 _iter.next(tp, stream_line, _space);
		  std::string _word;
		  std::stringstream word;
		  std::getline(stream_line, _word, _space);
		  word.str(_word);
		  using currentType = typename std::tuple_element<cur, std::tuple<Args...>>::type;
		  convert<0, currentType> _type;
		  std::get<cur>(tp) = _type.dog(_word);
	}
};

template<class... Args>
struct iter<0, Args...> {
	 void next(std::tuple<Args...>& tp, std::stringstream& stream_line, char _space) {
		std::string _word;
		std::stringstream word;
		std::getline(stream_line, _word, _space);
		word.str(_word);
		word >> std::get<0>(tp);
	}
};

template<class... Args>
struct iter<-1, Args...> {
	 void next(std::tuple<Args...>& tp, std::stringstream& stream_line, char _space) {}
};


template<class... Args>
class CSVParser {
	std::ifstream &os;
	char _space;
	int after_line;
	
	void make_tuple_str(std::tuple<Args...> &_tuple, std::string line) {
		std::stringstream stream_line;
		stream_line << line;
		const int _size = sizeof...(Args);
		iter<_size - 1, Args...> _iter;
		_iter.next(_tuple, stream_line, _space);
	}

	

public:
	CSVParser(std::ifstream &in, const char space, int l) : _space(space), os(in), after_line(l) {};



	class Proxy {
		int count = 0;
	
		int is_end() {
			if (os_copy.eof())
				return -1;
			else
				return 0;
		}

	public:
		CSVParser *p;
		std::tuple<Args...> collection_el;
		std::ifstream &os_copy;
		int _size = sizeof...(Args);

		Proxy(std::tuple<Args...> _tuple, std::ifstream &_os, CSVParser* _p, int _count) : os_copy(_os), p(_p), count(_count) {
			collection_el = _tuple;
			
		}


		void operator++() {
			
			std::string line;
			std::getline(os_copy, line);
			if (!(is_end() && line.empty()))
				(count)++;
			else count = -1;
			std::tuple<Args...> _tuple;
			p->make_tuple_str(_tuple, line);
		
			this->collection_el = _tuple;
		}

		bool operator!=(Proxy two) {
			int _size = sizeof...(Args);
			if (count == -1) {
				//os.seekg(0, os.beg);
				return 0;
			}
			if (two.count != count) 
				return 1;
			if (this->collection_el != two.collection_el)
				return 1;
			
			return 0;
		}

		std::tuple<Args...> operator*() {
			return this->collection_el;
		}

		std::tuple<Args...>* operator->() {
			return &(this->collection_el);
		}
  		
		friend class CSVParser;
	};

	Proxy begin() {
		std::string line; 
		os.seekg(0, os.beg);
		for (int i = 0; i < after_line; i++) 
			std::getline(os, line);
				
		std::getline(os, line);
		
		std::tuple<Args...> _tuple;
		make_tuple_str(_tuple, line);
		Proxy _begin(_tuple, this->os, this, 1);
		return _begin;
	}


	Proxy end() {
		
		std::string line;
		std::tuple<Args...> _tuple;
		Proxy _end(_tuple, this->os, this, -1);
	//	os.seekg(0, os.beg);
		return _end;
	}


	~CSVParser() {}
};

#endif PARSER_H
