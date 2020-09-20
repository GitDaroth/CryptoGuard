#include "catch.hpp"
#include "Hashing/Scrypt.h"
#include "Utils.h"

TEST_CASE("Scrypt hashing test", "[Scrypt]")
{
	std::string password, salt, hashedPassword, hash;
	int derivedKeyLength, costFactor, blockSizeFactor, parallelizationFactor;

	password = "";
	salt = "";
	derivedKeyLength = 64;
	costFactor = 16;
	blockSizeFactor = 1;
	parallelizationFactor = 1;
	hash = Utils::convertHexToString("77d6576238657b203b19ca42c18a0497f16b4844e3074ae8dfdffa3fede21442fcd0069ded0948f8326a753a0fc81f17e8d3e0fb2e0d3628cf35e20c38d18906");
	hashedPassword = Scrypt::hash(password, salt, derivedKeyLength, costFactor, blockSizeFactor, parallelizationFactor);
	REQUIRE(hashedPassword == hash);

	password = "password";
	salt = "NaCl";
	derivedKeyLength = 64;
	costFactor = 1024;
	blockSizeFactor = 8;
	parallelizationFactor = 16;
	hash = Utils::convertHexToString("fdbabe1c9d3472007856e7190d01e9fe7c6ad7cbc8237830e77376634b3731622eaf30d92e22a3886ff109279d9830dac727afb94a83ee6d8360cbdfa2cc0640");
	hashedPassword = Scrypt::hash(password, salt, derivedKeyLength, costFactor, blockSizeFactor, parallelizationFactor);
	REQUIRE(hashedPassword == hash);

//	password = "pleaseletmein";
//	salt = "SodiumChloride";
//	derivedKeyLength = 64;
//	costFactor = 16384;
//	blockSizeFactor = 8;
//	parallelizationFactor = 1;
//	hash = Utils::convertHexToString("7023bdcb3afd7348461c06cd81fd38ebfda8fbba904f8e3ea9b543f6545da1f2d5432955613f0fcf62d49705242a9af9e61e85dc0d651e40dfcf017b45575887");
//	hashedPassword = Scrypt::hash(password, salt, derivedKeyLength, costFactor, blockSizeFactor, parallelizationFactor);
//	REQUIRE(hashedPassword == hash);

//	password = "pleaseletmein";
//	salt = "SodiumChloride";
//	derivedKeyLength = 64;
//	costFactor = 1048576;
//	blockSizeFactor = 8;
//	parallelizationFactor = 1;
//	hash = Utils::convertHexToString("2101cb9b6a511aaeaddbbe09cf70f881ec568d574a2ffd4dabe5ee9820adaa478e56fd8f4ba5d09ffa1c6d927c40f4c337304049e8a952fbcbf45c6fa77a41a4");
//	hashedPassword = Scrypt::hash(password, salt, derivedKeyLength, costFactor, blockSizeFactor, parallelizationFactor);
//	REQUIRE(hashedPassword == hash);
}