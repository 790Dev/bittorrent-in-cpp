#include "PieceStorage.h"

#include <fstream>
#include <string>
#include <filesystem>

bool PieceStorage::savePiece(
    int pieceIndex,
    const std::vector<char>& data
)
{
    std::filesystem::create_directories("storage");

    std::string filename =
        "storage/piece_" +
        std::to_string(pieceIndex) +
        ".bin";

    std::ofstream out(
        filename,
        std::ios::binary
    );

    if(!out)
    {
        return false;
    }

    out.write(
        data.data(),
        data.size()
    );

    return true;
}