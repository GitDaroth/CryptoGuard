#include "Hashing/HMAC.h"

#include "Hashing/SHA256.h"

std::string HMAC::hash(std::string key, std::string message)
{
	if (key.length() > 64)
	{
		key = SHA256::hash(key);
	}

	if (key.length() < 64)
	{
		for (int i = key.length(); i < 64; i++)
		{
			key += (char)0x00;
		}
	}

	std::string outerPadKey;
	for (int i = 0; i < 64; i++)
	{
		outerPadKey += key[i] ^ 0x5c;
	}

	std::string innerPadKey;
	for (int i = 0; i < 64; i++)
	{
		innerPadKey += key[i] ^ 0x36;
	}

	return SHA256::hash(outerPadKey + SHA256::hash(innerPadKey + message));
}