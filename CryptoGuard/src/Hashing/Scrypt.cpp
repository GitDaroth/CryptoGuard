#include "Hashing/Scrypt.h"

#include <vector>
#include <bitset>
#include "Hashing/PBKDF2.h"
#include "Hashing/Salsa20.h"

std::string Scrypt::hash(std::string password, std::string salt, int derivedKeyLength, int costFactor, int blockSizeFactor, int parallelizationFactor)
{
	int blockSize = 128 * blockSizeFactor;

	std::string b = PBKDF2::hash(password, salt, 1, blockSize * parallelizationFactor);

	std::string expensiveSalt;
	for (int i = 0; i < parallelizationFactor; i++)
	{
		std::string bi = b.substr(i * blockSize, blockSize);
		bi = mixRound(bi, costFactor, blockSizeFactor);
		expensiveSalt += bi;
	}

	return PBKDF2::hash(password, expensiveSalt, 1, derivedKeyLength);
}

std::string Scrypt::mixRound(std::string block, int costFactor, int blockSizeFactor)
{
	int iterations = costFactor;

	std::vector<std::string> v;
	for (int i = 0; i < iterations; i++)
	{
		v.push_back(block);
		block = mixBlock(block, blockSizeFactor);
	}
	for (int i = 0; i < iterations; i++)
	{
		int offset = block.size() - 64;
		std::bitset<8> b1(block[offset]);
		std::bitset<8> b2(block[offset + 1]);
		std::bitset<8> b3(block[offset + 2]);
		std::bitset<8> b4(block[offset + 3]);
		std::bitset<8> b5(block[offset + 4]);
		std::bitset<8> b6(block[offset + 5]);
		std::bitset<8> b7(block[offset + 6]);
		std::bitset<8> b8(block[offset + 7]);
		// to little endian
		std::bitset<64> doubleWord(b8.to_string() + b7.to_string() + b6.to_string() + b5.to_string() + b4.to_string() + b3.to_string() + b2.to_string() + b1.to_string());

		//std::bitset<64> subBlock(block.substr(block.size() - 64, 8));
		int j = doubleWord.to_ullong() % costFactor;

		for (int k = 0; k < block.size(); k++)
		{
			block[k] ^= v.at(j)[k];
		}

		block = mixBlock(block, blockSizeFactor);
	}

	return block;
}

std::string Scrypt::mixBlock(std::string block, int blockSizeFactor)
{
	std::string mixedBlock;
	std::vector<std::string> y;

	std::string x = block.substr(block.size() - 64, 64);
	for (int i = 0; i < 2 * blockSizeFactor; i++)
	{
		std::string bi = block.substr(i * 64, 64);
		for (int j = 0; j < 64; j++)
		{
			x[j] ^= bi[j];
		}

		x = Salsa20::hash(x, 8);
		y.push_back(x);
	}

	// Append even indices
	for (int i = 0; i < 2 * blockSizeFactor; i += 2)
	{
		mixedBlock += y[i];
	}

	// Append odd indices
	for (int i = 1; i < 2 * blockSizeFactor; i += 2)
	{
		mixedBlock += y[i];
	}

	return mixedBlock;
}
