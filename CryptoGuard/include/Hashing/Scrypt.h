#pragma once

#include <string>

class Scrypt
{
public:
	static std::string hash(std::string password, std::string salt, int derivedKeyLength = 64, int costFactor = 16, int blockSizeFactor = 1, int parallelizationFactor = 1);

private:
	static std::string mixRound(std::string block, int costFactor, int blockSizeFactor);
	static std::string mixBlock(std::string block, int blockSizeFactor);
};


