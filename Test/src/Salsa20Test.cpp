#include "catch.hpp"
#include "Hashing/Salsa20.h"
#include "Utils.h"

TEST_CASE("Salsa20 hashing test", "[Salsa20]")
{
	std::string message, hashedMessage, hash;
	int rounds;

	message = Utils::convertHexToString("7e879a214f3ec9867ca940e641718f26baee555b8c61c1b50df846116dcd3b1dee24f319df9b3d8514121e4b5ac5aa3276021d2909c74829edebc68db8b8c25e");
	rounds = 8;
	hash = Utils::convertHexToString("a41f859c6608cc993b81cacb020cef05044b2181a2fd337dfd7b1c6396682f29b4393168e3c9e6bcfe6bc5b7a06d96bae424cc102c91745c24ad673dc7618f81");
	hashedMessage = Salsa20::hash(message, rounds);
	REQUIRE(hashedMessage == hash);
}