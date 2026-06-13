#include "InfoHashGenerator.h"

#include "../bencode/BencodeEncoder.h"

#include <sstream>
#include <iomanip>
#include <variant>
#include <vector>
#include <cstdint>

namespace {
    uint32_t leftRotate(uint32_t value, int bits) {
        return (value << bits) | (value >> (32 - bits));
    }
}

std::string InfoHashGenerator::sha1(
    const std::string& data
)
{
    uint32_t h0 = 0x67452301;
    uint32_t h1 = 0xEFCDAB89;
    uint32_t h2 = 0x98BADCFE;
    uint32_t h3 = 0x10325476;
    uint32_t h4 = 0xC3D2E1F0;

    std::vector<uint8_t> message(data.begin(), data.end());
    uint64_t bitLength = message.size() * 8;

    message.push_back(0x80);

    while ((message.size() % 64) != 56) {
        message.push_back(0x00);
    }

    for (int i = 7; i >= 0; --i) {
        message.push_back((bitLength >> (i * 8)) & 0xFF);
    }

    for (size_t chunkStart = 0; chunkStart < message.size(); chunkStart += 64) {
        uint32_t w[80];

        for (int i = 0; i < 16; ++i) {
            size_t offset = chunkStart + i * 4;
            w[i] = ((uint32_t)message[offset] << 24) |
                   ((uint32_t)message[offset + 1] << 16) |
                   ((uint32_t)message[offset + 2] << 8) |
                   ((uint32_t)message[offset + 3]);
        }

        for (int i = 16; i < 80; ++i) {
            w[i] = leftRotate(w[i - 3] ^ w[i - 8] ^ w[i - 14] ^ w[i - 16], 1);
        }

        uint32_t a = h0;
        uint32_t b = h1;
        uint32_t c = h2;
        uint32_t d = h3;
        uint32_t e = h4;

        for (int i = 0; i < 80; ++i) {
            uint32_t f, k;
            if (i <= 19) {
                f = (b & c) | ((~b) & d);
                k = 0x5A827999;
            } else if (i <= 39) {
                f = b ^ c ^ d;
                k = 0x6ED9EBA1;
            } else if (i <= 59) {
                f = (b & c) | (b & d) | (c & d);
                k = 0x8F1BBCDC;
            } else {
                f = b ^ c ^ d;
                k = 0xCA62C1D6;
            }

            uint32_t temp = leftRotate(a, 5) + f + e + k + w[i];
            e = d;
            d = c;
            c = leftRotate(b, 30);
            b = a;
            a = temp;
        }

        h0 += a;
        h1 += b;
        h2 += c;
        h3 += d;
        h4 += e;
    }

    std::stringstream ss;
    ss << std::hex << std::setfill('0');
    ss << std::setw(8) << h0
       << std::setw(8) << h1
       << std::setw(8) << h2
       << std::setw(8) << h3
       << std::setw(8) << h4;

    return ss.str();
}

std::string InfoHashGenerator::generate(
    const BencodeValue& root
)
{
    auto rootDict =
        std::get<BencodeDict>(
            root.value
        );

    auto infoValue =
        rootDict.at("info");

    std::string encodedInfo =
        BencodeEncoder::encode(
            infoValue
        );

    return sha1(
        encodedInfo
    );
}