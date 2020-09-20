#include "catch.hpp"
#include "Hashing/PBKDF2.h"
#include "Utils.h"

TEST_CASE("PBKDF2 hashing test", "[PBKDF2]")
{
	std::string password, salt, hashedPassword, hash;
	int iterations, derivedKeyLength;

	password = "password";
	salt = "salt";
	iterations = 1;
	derivedKeyLength = 32;
	hash = Utils::convertHexToString("120fb6cffcf8b32c43e7225256c4f837a86548c92ccc35480805987cb70be17b");
	hashedPassword = PBKDF2::hash(password, salt, iterations, derivedKeyLength);
	REQUIRE(hashedPassword == hash);

	password = "password";
	salt = "salt";
	iterations = 2;
	derivedKeyLength = 32;
	hash = Utils::convertHexToString("ae4d0c95af6b46d32d0adff928f06dd02a303f8ef3c251dfd6e2d85a95474c43");
	hashedPassword = PBKDF2::hash(password, salt, iterations, derivedKeyLength);
	REQUIRE(hashedPassword == hash);

	password = "password";
	salt = "salt";
	iterations = 4096;
	derivedKeyLength = 32;
	hash = Utils::convertHexToString("c5e478d59288c841aa530db6845c4c8d962893a001ce4e11a4963873aa98134a");
	hashedPassword = PBKDF2::hash(password, salt, iterations, derivedKeyLength);
	REQUIRE(hashedPassword == hash);

	password = "passwordPASSWORDpassword";
	salt = "saltSALTsaltSALTsaltSALTsaltSALTsalt";
	iterations = 4096;
	derivedKeyLength = 40;
	hash = Utils::convertHexToString("348c89dbcbd32b2f32d814b8116e84cf2b17347ebc1800181c4e2a1fb8dd53e1c635518c7dac47e9");
	hashedPassword = PBKDF2::hash(password, salt, iterations, derivedKeyLength);
	REQUIRE(hashedPassword == hash);
}