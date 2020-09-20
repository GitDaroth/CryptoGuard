#pragma once

#include <string>

#define ROTLEFT(a,b) (((a) << (b)) | ((a) >> (32 - (b))))
#define QR(a, b, c, d)       \
    b ^= ROTLEFT(a + d, 7); \
    c ^= ROTLEFT(b + a, 9); \
    d ^= ROTLEFT(c + b,13); \
    a ^= ROTLEFT(d + c,18);

class Salsa20
{
public:
	static std::string hash(std::string message, int rounds);
};


