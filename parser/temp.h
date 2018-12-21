#ifndef TEMP_H
#define TEMP_H
#include<iostream>
#include<tuple>
#include<fstream>
#include<conio.h>

	template<class Ch, class Tr, const int ind, class... Args>
	struct _iteration {
		static void next_val(std::basic_ostream<Ch, Tr>& os, std::tuple<Args...>const& tp) {
			_iteration<Ch, Tr, ind - 1, Args...>::next_val(os, tp);
			os << std::get<ind>(tp);
		}
	};

	template<class Ch, class Tr, class... Args>
	struct _iteration<Ch, Tr, 0, Args...> {
		static void next_val(std::basic_ostream<Ch, Tr>& os, std::tuple<Args...>const& tp) {
			os << std::get<0>(tp);
		}
	};

	template<class Ch, class Tr, class... Args>
	struct _iteration<Ch, Tr, -1, Args...> {
		
		static void next_val(std::basic_ostream<Ch, Tr>& os, std::tuple<Args...>const& tp) {}
	};

	/*void _each(std::tuple<Args...> t) {
	const int _size = std::tuple_size <std::tuple<Args...>>::value;
	_iteration<_size - 1, Args...>::next_val(t);
	}*/

        template<class Ch, class Tr, class... Args>
		auto operator<<(std::basic_ostream<Ch, Tr>& os, std::tuple<Args...>const& t) {
			const int _size = std::tuple_size <std::tuple<Args...>>::value;
			_iteration<Ch, Tr, _size - 1, Args...>::next_val(os, t);
    		return &os;
		}
	
		
#endif