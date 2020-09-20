#pragma once

#include <string>

class AES
{
public:
	static std::string encrypt(std::string message, std::string key, std::string initialisationVector = "");
	static std::string decrypt(std::string encryptedMessage, std::string key, std::string initialisationVector = "");

private:
	static void substituteBytes(std::string& messageBlock);
	static void substituteBytesInv(std::string& messageBlock);
	static void shiftRows(std::string& messageBlock);
	static void shiftRowsInv(std::string& messageBlock);
	static void mixColumns(std::string& messageBlock);
	static void mixColumnsInv(std::string& messageBlock);

	static void addRoundKey(std::string& messageBlock, std::string roundKey);
	static std::string expandKey(std::string key, int numberOfRounds);
};

