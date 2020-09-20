#include "Hashing/SHA256.h"

#include <bitset>
#include <vector>
#include <iomanip>
#include "Utils.h"

std::string SHA256::hash(std::string message)
{
	std::vector<unsigned char> blocks_8bit;

	//----------- Pad the message to a multiple of 512 bit length -------------

	// Store each character of the message into a 8 bit block
	for (int i = 0; i < message.size(); i++)
	{
		blocks_8bit.push_back(message.c_str()[i]);
	}

	// l + k = 448 mod 512

	int messageBitLength = blocks_8bit.size() * 8;

	int numberOfBlocks_512Bit = 1 + (messageBitLength + 65) / 512;
	int paddingZerosBitLength = 448 - messageBitLength + (numberOfBlocks_512Bit - 1) * 512;

	// ISO/IEC 7816-4 Padding
	for (int i = 0; i < paddingZerosBitLength / 8; i++)
	{
		if (i == 0)
		{
			blocks_8bit.push_back(0x80); // 8bit: 10000000
		}
		else
		{
			blocks_8bit.push_back(0x00); // 8bit: 00000000
		}
	}

	// Append the message bit length as 64 bit number in 8 bit blocks
	std::bitset<64> messageBitLength_64bit(messageBitLength);
	std::string messageBitLength_64bit_string = messageBitLength_64bit.to_string();

	for (int i = 0; i < 8; i++)
	{
		std::bitset<8> b(messageBitLength_64bit_string.substr(8 * i, 8));
		blocks_8bit.push_back(static_cast<unsigned char>(b.to_ulong()));
	}

	//----------- Hash computation -------------
	unsigned long k[64] = {
			0x428a2f98,0x71374491,0xb5c0fbcf,0xe9b5dba5,0x3956c25b,0x59f111f1,
			0x923f82a4,0xab1c5ed5,0xd807aa98,0x12835b01,0x243185be,0x550c7dc3,
			0x72be5d74,0x80deb1fe,0x9bdc06a7,0xc19bf174,0xe49b69c1,0xefbe4786,
			0x0fc19dc6,0x240ca1cc,0x2de92c6f,0x4a7484aa,0x5cb0a9dc,0x76f988da,
			0x983e5152,0xa831c66d,0xb00327c8,0xbf597fc7,0xc6e00bf3,0xd5a79147,
			0x06ca6351,0x14292967,0x27b70a85,0x2e1b2138,0x4d2c6dfc,0x53380d13,
			0x650a7354,0x766a0abb,0x81c2c92e,0x92722c85,0xa2bfe8a1,0xa81a664b,
			0xc24b8b70,0xc76c51a3,0xd192e819,0xd6990624,0xf40e3585,0x106aa070,
			0x19a4c116,0x1e376c08,0x2748774c,0x34b0bcb5,0x391c0cb3,0x4ed8aa4a,
			0x5b9cca4f,0x682e6ff3,0x748f82ee,0x78a5636f,0x84c87814,0x8cc70208,
			0x90befffa,0xa4506ceb,0xbef9a3f7,0xc67178f2
	};

	unsigned long h0 = 0x6a09e667;
	unsigned long h1 = 0xbb67ae85;
	unsigned long h2 = 0x3c6ef372;
	unsigned long h3 = 0xa54ff53a;
	unsigned long h4 = 0x510e527f;
	unsigned long h5 = 0x9b05688c;
	unsigned long h6 = 0x1f83d9ab;
	unsigned long h7 = 0x5be0cd19;

	unsigned long w[64];

	unsigned long t1, t2, a, b, c, d, e, f, g, h;

	for (int i = 0; i < numberOfBlocks_512Bit; i++)
	{
		a = h0;
		b = h1;
		c = h2;
		d = h3;
		e = h4;
		f = h5;
		g = h6;
		h = h7;

		// Compute values for W[64]
		for (int j = 0; j < 64; j++)
		{
			if (j < 16)
			{
				int offset = j * 4 + i * 64;
				std::bitset<8> b1(blocks_8bit[offset]);
				std::bitset<8> b2(blocks_8bit[offset + 1]);
				std::bitset<8> b3(blocks_8bit[offset + 2]);
				std::bitset<8> b4(blocks_8bit[offset + 3]);
				std::bitset<32> word(b1.to_string() + b2.to_string() + b3.to_string() + b4.to_string());
				w[j] = word.to_ulong();
			}
			else
			{
				w[j] = SSIG1(w[j - 2]) + w[j - 7] + SSIG0(w[j - 15]) + w[j - 16];
			}
		}

		for (int j = 0; j < 64; j++)
		{
			t1 = h + BSIG1(e) + CH(e, f, g) + k[j] + w[j];
			t2 = BSIG0(a) + MAJ(a, b, c);
			h = g;
			g = f;
			f = e;
			e = d + t1;
			d = c;
			c = b;
			b = a;
			a = t1 + t2;
		}

		h0 += a;
		h1 += b;
		h2 += c;
		h3 += d;
		h4 += e;
		h5 += f;
		h6 += g;
		h7 += h;
	}

	std::string hashedMessage = Utils::ulongToString(h0) + Utils::ulongToString(h1) +
								Utils::ulongToString(h2) + Utils::ulongToString(h3) +
								Utils::ulongToString(h4) + Utils::ulongToString(h5) +
								Utils::ulongToString(h6) + Utils::ulongToString(h7);

	return hashedMessage;
}