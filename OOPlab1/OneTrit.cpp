#include "OneTrit.h"

Trit set(Trit val) {
	Trit trit = val;
	return trit;
}

Trit operator &(Trit first, Trit second) {
	if (first == Trit::False || second == Trit::False)
		return Trit::False;
	if (first == Trit::True && second == Trit::True)
		return Trit::True;
	return Trit::Unknown;
}

Trit operator |(Trit first, Trit second) {
	if (first == Trit::True || second == Trit::True)
		return Trit::True;
	if (first == Trit::False && second == Trit::False)
		return Trit::False;
	return Trit::Unknown;

}

Trit operator ~(Trit elem) {
	if (elem == Trit::True)
		return Trit::False;
	if (elem == Trit::False)
		return Trit::True;
	return Trit::Unknown;

}