#include "FileAssembler.h"

#include <fstream>
#include <vector>
#include <iostream>

bool FileAssembler::assemble(
    const std::string& storageDir,
    const std::string& outputFilePath,
    int totalPieces
)
{
    std::ofstream out(
        outputFilePath,
        std::ios::binary
    );

    if(!out)
    {
        std::cerr
            << "Failed to open output file: "
            << outputFilePath
            << "\n";

        return false;
    }

    std::vector<char> buffer(65536); // 64KB buffer

    for(int i = 0; i < totalPieces; i++)
    {
        std::string piecePath =
            storageDir +
            "/piece_" +
            std::to_string(i) +
            ".bin";

        std::ifstream in(
            piecePath,
            std::ios::binary
        );

        if(!in)
        {
            std::cerr
                << "Failed to open piece file: "
                << piecePath
                << "\n";

            return false;
        }

        while(
            in.read(
                buffer.data(),
                buffer.size()
            )
        )
        {
            out.write(
                buffer.data(),
                in.gcount()
            );
        }

        if(in.gcount() > 0)
        {
            out.write(
                buffer.data(),
                in.gcount()
            );
        }
    }

    return true;
}
