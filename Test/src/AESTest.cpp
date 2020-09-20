#include "catch.hpp"
#include "Encryption/AES.h"
#include "Utils.h"

TEST_CASE("AES encryption/decryption test", "[AES]")
{
	std::string plainText, key, initializationVector, cipherText, encryptedPlainText, decryptedCipherText;
	SECTION( "128-bit key" )
	{
		plainText = Utils::convertHexToString("6bc1bee22e409f96e93d7e117393172a");
		key = Utils::convertHexToString("2b7e151628aed2a6abf7158809cf4f3c");
		initializationVector = Utils::convertHexToString("000102030405060708090A0B0C0D0E0F");
		cipherText = Utils::convertHexToString("7649abac8119b246cee98e9b12e9197d");
		encryptedPlainText = AES::encrypt(plainText, key, initializationVector);
		decryptedCipherText = AES::decrypt(cipherText, key, initializationVector);
		REQUIRE(encryptedPlainText == cipherText);
		REQUIRE(decryptedCipherText == plainText);

		plainText = Utils::convertHexToString("ae2d8a571e03ac9c9eb76fac45af8e51");
		key = Utils::convertHexToString("2b7e151628aed2a6abf7158809cf4f3c");
		initializationVector = Utils::convertHexToString("7649ABAC8119B246CEE98E9B12E9197D");
		cipherText = Utils::convertHexToString("5086cb9b507219ee95db113a917678b2");
		encryptedPlainText = AES::encrypt(plainText, key, initializationVector);
		decryptedCipherText = AES::decrypt(cipherText, key, initializationVector);
		REQUIRE(encryptedPlainText == cipherText);
		REQUIRE(decryptedCipherText == plainText);

		plainText = Utils::convertHexToString("30c81c46a35ce411e5fbc1191a0a52ef");
		key = Utils::convertHexToString("2b7e151628aed2a6abf7158809cf4f3c");
		initializationVector = Utils::convertHexToString("5086CB9B507219EE95DB113A917678B2");
		cipherText = Utils::convertHexToString("73bed6b8e3c1743b7116e69e22229516");
		encryptedPlainText = AES::encrypt(plainText, key, initializationVector);
		decryptedCipherText = AES::decrypt(cipherText, key, initializationVector);
		REQUIRE(encryptedPlainText == cipherText);
		REQUIRE(decryptedCipherText == plainText);

		plainText = Utils::convertHexToString("f69f2445df4f9b17ad2b417be66c3710");
		key = Utils::convertHexToString("2b7e151628aed2a6abf7158809cf4f3c");
		initializationVector = Utils::convertHexToString("73BED6B8E3C1743B7116E69E22229516");
		cipherText = Utils::convertHexToString("3ff1caa1681fac09120eca307586e1a7");
		encryptedPlainText = AES::encrypt(plainText, key, initializationVector);
		decryptedCipherText = AES::decrypt(cipherText, key, initializationVector);
		REQUIRE(encryptedPlainText == cipherText);
		REQUIRE(decryptedCipherText == plainText);
	}

	SECTION( "192-bit key" )
	{
		plainText = Utils::convertHexToString("6bc1bee22e409f96e93d7e117393172a");
		key = Utils::convertHexToString("8e73b0f7da0e6452c810f32b809079e562f8ead2522c6b7b");
		initializationVector = Utils::convertHexToString("000102030405060708090A0B0C0D0E0F");
		cipherText = Utils::convertHexToString("4f021db243bc633d7178183a9fa071e8");
		encryptedPlainText = AES::encrypt(plainText, key, initializationVector);
		decryptedCipherText = AES::decrypt(cipherText, key, initializationVector);
		REQUIRE(encryptedPlainText == cipherText);
		REQUIRE(decryptedCipherText == plainText);

		plainText = Utils::convertHexToString("ae2d8a571e03ac9c9eb76fac45af8e51");
		key = Utils::convertHexToString("8e73b0f7da0e6452c810f32b809079e562f8ead2522c6b7b");
		initializationVector = Utils::convertHexToString("4F021DB243BC633D7178183A9FA071E8");
		cipherText = Utils::convertHexToString("b4d9ada9ad7dedf4e5e738763f69145a");
		encryptedPlainText = AES::encrypt(plainText, key, initializationVector);
		decryptedCipherText = AES::decrypt(cipherText, key, initializationVector);
		REQUIRE(encryptedPlainText == cipherText);
		REQUIRE(decryptedCipherText == plainText);

		plainText = Utils::convertHexToString("30c81c46a35ce411e5fbc1191a0a52ef");
		key = Utils::convertHexToString("8e73b0f7da0e6452c810f32b809079e562f8ead2522c6b7b");
		initializationVector = Utils::convertHexToString("B4D9ADA9AD7DEDF4E5E738763F69145A");
		cipherText = Utils::convertHexToString("571b242012fb7ae07fa9baac3df102e0");
		encryptedPlainText = AES::encrypt(plainText, key, initializationVector);
		decryptedCipherText = AES::decrypt(cipherText, key, initializationVector);
		REQUIRE(encryptedPlainText == cipherText);
		REQUIRE(decryptedCipherText == plainText);

		plainText = Utils::convertHexToString("f69f2445df4f9b17ad2b417be66c3710");
		key = Utils::convertHexToString("8e73b0f7da0e6452c810f32b809079e562f8ead2522c6b7b");
		initializationVector = Utils::convertHexToString("571B242012FB7AE07FA9BAAC3DF102E0");
		cipherText = Utils::convertHexToString("08b0e27988598881d920a9e64f5615cd");
		encryptedPlainText = AES::encrypt(plainText, key, initializationVector);
		decryptedCipherText = AES::decrypt(cipherText, key, initializationVector);
		REQUIRE(encryptedPlainText == cipherText);
		REQUIRE(decryptedCipherText == plainText);
	}

	SECTION( "256-bit key" )
	{
		plainText = Utils::convertHexToString("6bc1bee22e409f96e93d7e117393172a");
		key = Utils::convertHexToString("603deb1015ca71be2b73aef0857d77811f352c073b6108d72d9810a30914dff4");
		initializationVector = Utils::convertHexToString("000102030405060708090A0B0C0D0E0F");
		cipherText = Utils::convertHexToString("f58c4c04d6e5f1ba779eabfb5f7bfbd6");
		encryptedPlainText = AES::encrypt(plainText, key, initializationVector);
		decryptedCipherText = AES::decrypt(cipherText, key, initializationVector);
		REQUIRE(encryptedPlainText == cipherText);
		REQUIRE(decryptedCipherText == plainText);

		plainText = Utils::convertHexToString("ae2d8a571e03ac9c9eb76fac45af8e51");
		key = Utils::convertHexToString("603deb1015ca71be2b73aef0857d77811f352c073b6108d72d9810a30914dff4");
		initializationVector = Utils::convertHexToString("F58C4C04D6E5F1BA779EABFB5F7BFBD6");
		cipherText = Utils::convertHexToString("9cfc4e967edb808d679f777bc6702c7d");
		encryptedPlainText = AES::encrypt(plainText, key, initializationVector);
		decryptedCipherText = AES::decrypt(cipherText, key, initializationVector);
		REQUIRE(encryptedPlainText == cipherText);
		REQUIRE(decryptedCipherText == plainText);

		plainText = Utils::convertHexToString("30c81c46a35ce411e5fbc1191a0a52ef");
		key = Utils::convertHexToString("603deb1015ca71be2b73aef0857d77811f352c073b6108d72d9810a30914dff4");
		initializationVector = Utils::convertHexToString("9CFC4E967EDB808D679F777BC6702C7D");
		cipherText = Utils::convertHexToString("39f23369a9d9bacfa530e26304231461");
		encryptedPlainText = AES::encrypt(plainText, key, initializationVector);
		decryptedCipherText = AES::decrypt(cipherText, key, initializationVector);
		REQUIRE(encryptedPlainText == cipherText);
		REQUIRE(decryptedCipherText == plainText);

		plainText = Utils::convertHexToString("f69f2445df4f9b17ad2b417be66c3710");
		key = Utils::convertHexToString("603deb1015ca71be2b73aef0857d77811f352c073b6108d72d9810a30914dff4");
		initializationVector = Utils::convertHexToString("39F23369A9D9BACFA530E26304231461");
		cipherText = Utils::convertHexToString("b2eb05e2c39be9fcda6c19078c6a9d1b");
		encryptedPlainText = AES::encrypt(plainText, key, initializationVector);
		decryptedCipherText = AES::decrypt(cipherText, key, initializationVector);
		REQUIRE(encryptedPlainText == cipherText);
		REQUIRE(decryptedCipherText == plainText);
	}
}