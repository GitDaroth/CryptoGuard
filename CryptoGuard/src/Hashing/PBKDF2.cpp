#include "Hashing/PBKDF2.h"

#include <bitset>
#include "Utils.h"
#include "Hashing/HMAC.h"

std::string PBKDF2::hash(std::string password, std::string salt, int iterations, int derivedKeyLength)
{
	std::string derivedKey;
	for (int i = 1; i <= (derivedKeyLength / 32) + 1; i++)
	{
		std::string t;
		for (int j = 0; j < 32; j++)
		{
			t += (char)0x00;
		}

		std::bitset<32> word(i);
		std::string iString = Utils::ulongToString(word.to_ulong());
		std::string u = salt + iString;

		for (int j = 0; j < iterations; j++)
		{
			u = HMAC::hash(password, u);

			for (int k = 0; k < 32; k++)
			{
				t[k] ^= u[k];
			}
		}

		if (i == (derivedKeyLength / 32) + 1)
		{
			for (int j = 0; j < derivedKeyLength % 32; j++)
			{
				derivedKey += t[j];
			}
		}
		else
		{
			derivedKey += t;
		}
	}

	return derivedKey;
}