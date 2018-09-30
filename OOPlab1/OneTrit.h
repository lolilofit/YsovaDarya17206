#ifndef _ONETRIT_H_
#define _ONETRIT_H_

enum class Trit : unsigned int { False = 1, Unknown = 0, True = 3 };

Trit set(Trit val);

Trit operator &(Trit first, Trit second);

Trit operator |(Trit first, Trit second);

Trit operator ~(Trit elem);

#endif