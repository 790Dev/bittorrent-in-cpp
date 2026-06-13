#include <iostream>

#include "torrent/TorrentFile.h"
#include "torrent/TorrentMetadata.h"

int main()
{
    std::cout << "========== BitTorrent Client ==========\n\n";

    TorrentFile torrent;

    if (!torrent.load("../torrents/sample.torrent"))
    {
        std::cout << "Failed to load torrent file!\n";
        return 1;
    }

    std::cout << "Torrent file loaded successfully.\n";

    BencodeValue root = torrent.parse();

    std::cout << "Torrent file parsed successfully.\n";

    TorrentMetadata metadata =
        TorrentMetadata::fromBencode(root);

    metadata.print();

    std::cout << "\n=======================================\n";

    return 0;
}