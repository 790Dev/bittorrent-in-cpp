#include "InfoHashGenerator.h"

#include "../bencode/BencodeEncoder.h"

#include <openssl/sha.h>

#include <sstream>
#include <iomanip>

std::string InfoHashGenerator::sha1Binary(
    const std::string& data
)
{
    unsigned char hash[SHA_DIGEST_LENGTH];

    SHA1(
        reinterpret_cast<const unsigned char*>(
            data.c_str()
        ),
        data.size(),
        hash
    );

    return std::string(
        reinterpret_cast<char*>(hash),
        SHA_DIGEST_LENGTH
    );
}

std::string InfoHashGenerator::sha1Hex(
    const std::string& data
)
{
    unsigned char hash[SHA_DIGEST_LENGTH];

    SHA1(
        reinterpret_cast<const unsigned char*>(
            data.c_str()
        ),
        data.size(),
        hash
    );

    std::stringstream ss;

    for(int i = 0; i < SHA_DIGEST_LENGTH; i++)
    {
        ss
            << std::hex
            << std::setw(2)
            << std::setfill('0')
            << (int)hash[i];
    }

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

    return sha1Binary(
        encodedInfo
    );
}

std::string InfoHashGenerator::generateHex(
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

    return sha1Hex(
        encodedInfo
    );
}