#pragma once

#include <string>

class PBKDF2
{
public:
	static std::string hash(std::string password, std::string salt, int iterations = 4096, int derivedKeyLength = 16);
};


