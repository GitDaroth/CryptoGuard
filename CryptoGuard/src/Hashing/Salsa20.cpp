#include "Hashing/Salsa20.h"

#include <bitset>
#include <iomanip>
#include "Utils.h"

std::string Salsa20::hash(std::string message, int rounds)
{
	unsigned long in[16];
	unsigned long x[16];

	for (int i = 0; i < 16; i++)
	{
		int offset = i * 4;
		std::bitset<8> b1(message[offset]);
		std::bitset<8> b2(message[offset + 1]);
		std::bitset<8> b3(message[offset + 2]);
		std::bitset<8> b4(message[offset + 3]);
		// to little endian
		std::bitset<32> word(b4.to_string() + b3.to_string() + b2.to_string() + b1.to_string());

		in[i] = word.to_ulong();
		x[i] = in[i];
	}

	for (int i = 0; i < rounds / 2; i++)
	{
		// Odd round.
		QR(x[0], x[4], x[8], x[12])		// column 1
		QR(x[5], x[9], x[13], x[1])		// column 2
		QR(x[10], x[14], x[2], x[6])	// column 3
		QR(x[15], x[3], x[7], x[11])	// column 4
		// Even round.
		QR(x[0], x[1], x[2], x[3])		// row 1
		QR(x[5], x[6], x[7], x[4])		// row 2
		QR(x[10], x[11], x[8], x[9])	// row 3
		QR(x[15], x[12], x[13], x[14])	// row 4
	}

	std::string hashedMessage;

	for (int i = 0; i < 16; i++)
	{
		x[i] = x[i] + in[i];
		// to big endian
		hashedMessage += Utils::ulongToString(x[i]).substr(3, 1) + Utils::ulongToString(x[i]).substr(2, 1) +
						 Utils::ulongToString(x[i]).substr(1, 1) + Utils::ulongToString(x[i]).substr(0, 1);
	}

	return hashedMessage;
}