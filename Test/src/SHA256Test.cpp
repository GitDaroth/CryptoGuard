#include "catch.hpp"
#include "Hashing/SHA256.h"
#include "Utils.h"

TEST_CASE("SHA256 hashing test", "[SHA256]")
{
	std::string message, hashedMessage, hash;

	message = "abc";
	hash = Utils::convertHexToString("ba7816bf8f01cfea414140de5dae2223b00361a396177a9cb410ff61f20015ad");
	hashedMessage = SHA256::hash(message);
	REQUIRE(hashedMessage == hash);

	message = "";
	hash = Utils::convertHexToString("e3b0c44298fc1c149afbf4c8996fb92427ae41e4649b934ca495991b7852b855");
	hashedMessage = SHA256::hash(message);
	REQUIRE(hashedMessage == hash);

	message = "abcdbcdecdefdefgefghfghighijhijkijkljklmklmnlmnomnopnopq";
	hash = Utils::convertHexToString("248d6a61d20638b8e5c026930c3e6039a33ce45964ff2167f6ecedd419db06c1");
	hashedMessage = SHA256::hash(message);
	REQUIRE(hashedMessage == hash);

	message = "abcdefghbcdefghicdefghijdefghijkefghijklfghijklmghijklmnhijklmnoijklmnopjklmnopqklmnopqrlmnopqrsmnopqrstnopqrstu";
	hash = Utils::convertHexToString("cf5b16a778af8380036ce59e7b0492370b249b11e8f07a51afac45037afee9d1");
	hashedMessage = SHA256::hash(message);
	REQUIRE(hashedMessage == hash);

	message = "";
	for(int i = 0; i < 1000000; i++)
		message += "a";
	hash = Utils::convertHexToString("cdc76e5c9914fb9281a1c7e284d73e67f1809a48a497200e046d39ccc7112cd0");
	hashedMessage = SHA256::hash(message);
	REQUIRE(hashedMessage == hash);
}