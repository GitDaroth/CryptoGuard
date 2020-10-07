#pragma once

#include <string>
#include <iostream>
#include <zxcvbn.h>
#include <QRandomGenerator>

namespace Utils
{
	inline static std::string ulongToString(unsigned long ulong)
	{
		std::string outString;
		outString += ulong >> 24;
		outString += (ulong >> 16) & 0xff;
		outString += (ulong >> 8) & 0xff;
		outString += ulong & 0xff;
		return outString;
	}

	inline static void printHex(std::string message)
	{
		for (unsigned char c : message)
		{
			if (c / 16 < 10) 
				std::cout << (char)((c / 16) + '0');
			if (c / 16 >= 10) 
				std::cout << (char)((c / 16 - 10) + 'a');

			if (c % 16 < 10) 
				std::cout << (char)((c % 16) + '0');
			if (c % 16 >= 10) 
				std::cout << (char)((c % 16 - 10) + 'a');

			std::cout << " ";
		}
	}

	inline static std::string convertHexToString(std::string hexString)
	{
		std::string outString;
		for (int i = 0; i < hexString.size(); i += 2)
		{
			int intFromHex;

			if (hexString[i] >= '0' && hexString[i] <= '9')
				intFromHex = (hexString[i] - '0') * 16;
			else if (hexString[i] >= 'a' && hexString[i] <= 'z')
				intFromHex = (hexString[i] - 'a' + 10) * 16;
			else if (hexString[i] >= 'A' && hexString[i] <= 'Z')
				intFromHex = (hexString[i] - 'A' + 10) * 16;

			if (hexString[i + 1] >= '0' && hexString[i + 1] <= '9')
				intFromHex += hexString[i + 1] - '0';
			else if (hexString[i + 1] >= 'a' && hexString[i + 1] <= 'z')
				intFromHex += hexString[i + 1] - 'a' + 10;
			else if (hexString[i + 1] >= 'A' && hexString[i + 1] <= 'Z')
				intFromHex += hexString[i + 1] - 'A' + 10;

			outString += (char)intFromHex;
		}
		return outString;
	}

	inline static float calcPasswordStrength(const std::string& password)
	{	
		ZxcResult result = ZxcvbnMatch(password.c_str(), {}, nullptr);
		return result.Score;
	}

	inline static std::string generatePassword(size_t length)
	{
		const std::string numericalChars = "0123456789";
		const std::string alphabeticalLowerCaseChars = "abcdefghijklmnopqrstuvwxyz";
		const std::string alphabeticalUpperCaseChars = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
		const std::string specialChars = "!@#$%^&*";
		const std::string allChars = "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ!@#$%^&*";

		std::string generatedPassword = "";
		for (int i = 0; i < length; i++)
		{
			char randomChar = allChars[QRandomGenerator::system()->bounded((int)allChars.size())];
			generatedPassword += randomChar;
		}

		// ensure that at least 1 character from each category is in the password
		int numericalCharsCount = 0;
		size_t lastNumericalCharIndex = INT_MAX;
		int alphabeticalLowerCaseCharsCount = 0;
		size_t lastAlphabeticalLowerCaseCharIndex = INT_MAX;
		int alphabeticalUpperCaseCharsCount = 0;
		size_t lastAlphabeticalUpperCaseCharIndex = INT_MAX;
		int specialCharsCount = 0;
		size_t lastSpecialCharIndex = INT_MAX;
		for (int i = 0; i < length; i++)
		{
			if (numericalChars.find(generatedPassword[i]) != std::string::npos)
			{
				numericalCharsCount++;
				lastNumericalCharIndex = i;
			}
			else if (alphabeticalLowerCaseChars.find(generatedPassword[i]) != std::string::npos)
			{
				alphabeticalLowerCaseCharsCount++;
				lastAlphabeticalLowerCaseCharIndex = i;
			}
			else if (alphabeticalUpperCaseChars.find(generatedPassword[i]) != std::string::npos)
			{
				alphabeticalUpperCaseCharsCount++;
				lastAlphabeticalUpperCaseCharIndex = i;
			}
			else if (specialChars.find(generatedPassword[i]) != std::string::npos)
			{
				specialCharsCount++;
				lastSpecialCharIndex = i;
			}
		}

		if (numericalCharsCount == 0)
		{
			char randomNumericalChar = numericalChars[QRandomGenerator::system()->bounded((int)numericalChars.size())];
			int randomIndex;
			do
				randomIndex = QRandomGenerator::system()->bounded((int)length);
			while (randomIndex == lastAlphabeticalLowerCaseCharIndex ||
				randomIndex == lastAlphabeticalUpperCaseCharIndex ||
				randomIndex == lastSpecialCharIndex);

			lastNumericalCharIndex = randomIndex;
			generatedPassword[randomIndex] = randomNumericalChar;
		}

		if (alphabeticalLowerCaseCharsCount == 0)
		{
			char randomAlphabeticalLowerCaseChar = alphabeticalLowerCaseChars[QRandomGenerator::system()->bounded((int)alphabeticalLowerCaseChars.size())];
			int randomIndex;
			do
				randomIndex = QRandomGenerator::system()->bounded((int)length);
			while (randomIndex == lastNumericalCharIndex ||
				randomIndex == lastAlphabeticalUpperCaseCharIndex ||
				randomIndex == lastSpecialCharIndex);

			lastAlphabeticalLowerCaseCharIndex = randomIndex;
			generatedPassword[randomIndex] = randomAlphabeticalLowerCaseChar;
		}

		if (alphabeticalUpperCaseCharsCount == 0)
		{
			char randomAlphabeticalUpperCaseChar = alphabeticalUpperCaseChars[QRandomGenerator::system()->bounded((int)alphabeticalUpperCaseChars.size())];
			int randomIndex;
			do
				randomIndex = QRandomGenerator::system()->bounded((int)length);
			while (randomIndex == lastNumericalCharIndex ||
				randomIndex == lastAlphabeticalLowerCaseCharIndex ||
				randomIndex == lastSpecialCharIndex);

			lastAlphabeticalUpperCaseCharIndex = randomIndex;
			generatedPassword[randomIndex] = randomAlphabeticalUpperCaseChar;
		}

		if (specialCharsCount == 0)
		{
			char randomSpecialChar = specialChars[QRandomGenerator::system()->bounded((int)specialChars.size())];
			int randomIndex;
			do
				randomIndex = QRandomGenerator::system()->bounded((int)length);
			while (randomIndex == lastAlphabeticalLowerCaseCharIndex ||
				randomIndex == lastAlphabeticalUpperCaseCharIndex ||
				randomIndex == lastNumericalCharIndex);

			lastSpecialCharIndex = randomIndex;
			generatedPassword[randomIndex] = randomSpecialChar;
		}

		return generatedPassword;
	}
}