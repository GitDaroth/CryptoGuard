#pragma once

#include <string>

class HMAC
{
public:
	static std::string hash(std::string key, std::string message);
};


