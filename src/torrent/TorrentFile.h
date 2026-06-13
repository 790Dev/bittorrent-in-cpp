#pragma once

#include <string>

#include "../bencode/BencodeValue.h"

class TorrentFile
{
private:

    std::string content;

public:

    bool load(const std::string& path);

    BencodeValue parse() const;

    const std::string& getContent() const;
};