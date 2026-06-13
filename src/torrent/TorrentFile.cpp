#include "TorrentFile.h"

#include <fstream>
#include <sstream>

#include "../bencode/BencodeParser.h"

bool TorrentFile::load(
    const std::string& path
)
{
    std::ifstream file(
        path,
        std::ios::binary
    );

    if(!file)
    {
        return false;
    }

    std::stringstream buffer;

    buffer << file.rdbuf();

    content = buffer.str();

    return true;
}

BencodeValue TorrentFile::parse() const
{
    size_t pos = 0;

    return BencodeParser::parse(
        content,
        pos
    );
}

const std::string&
TorrentFile::getContent() const
{
    return content;
}