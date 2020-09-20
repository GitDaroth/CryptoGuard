#pragma once

#include <string>
#include <iostream>

namespace Utils
{
	inline std::string ulongToString(unsigned long ulong)
	{
		std::string outString;
		outString += ulong >> 24;
		outString += (ulong >> 16) & 0xff;
		outString += (ulong >> 8) & 0xff;
		outString += ulong & 0xff;
		return outString;
	}

	inline void printHex(std::string message)
	{
		for (unsigned char c : message)
		{
			if (c / 16 < 10) std::cout << (char)((c / 16) + '0');
			if (c / 16 >= 10) std::cout << (char)((c / 16 - 10) + 'a');

			if (c % 16 < 10) std::cout << (char)((c % 16) + '0');
			if (c % 16 >= 10) std::cout << (char)((c % 16 - 10) + 'a');

			std::cout << " ";
		}
	}

	inline std::string convertHexToString(std::string hexString)
	{
		std::string outString;
		for (int i = 0; i < hexString.size(); i += 2)
		{
			int intFromHex;

			if (hexString[i] >= '0' && hexString[i] <= '9')
			{
				intFromHex = (hexString[i] - '0') * 16;
			}
			else if (hexString[i] >= 'a' && hexString[i] <= 'z')
			{
				intFromHex = (hexString[i] - 'a' + 10) * 16;
			}
			else if (hexString[i] >= 'A' && hexString[i] <= 'Z')
			{
				intFromHex = (hexString[i] - 'A' + 10) * 16;
			}

			if (hexString[i + 1] >= '0' && hexString[i + 1] <= '9')
			{
				intFromHex += hexString[i + 1] - '0';
			}
			else if (hexString[i + 1] >= 'a' && hexString[i + 1] <= 'z')
			{
				intFromHex += hexString[i + 1] - 'a' + 10;
			}
			else if (hexString[i + 1] >= 'A' && hexString[i + 1] <= 'Z')
			{
				intFromHex += hexString[i + 1] - 'A' + 10;
			}

			outString += (char)intFromHex;
		}
		return outString;
	}
}