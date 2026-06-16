#include "PieceHashVerifier.h"

#include <openssl/sha.h>

#include <sstream>
#include <iomanip>

std::string PieceHashVerifier::calculateHash(
    const std::vector<char>& pieceData
)
{
    unsigned char hash[SHA_DIGEST_LENGTH];

    SHA1(
        reinterpret_cast<const unsigned char*>(
            pieceData.data()
        ),
        pieceData.size(),
        hash
    );

    return std::string(
        reinterpret_cast<char*>(hash),
        SHA_DIGEST_LENGTH
    );
}

bool PieceHashVerifier::verify(
    const std::vector<char>& pieceData,
    const std::string& expectedHash
)
{
    std::string actualHash =
        calculateHash(
            pieceData
        );

    return actualHash == expectedHash;
}
