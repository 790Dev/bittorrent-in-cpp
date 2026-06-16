#pragma once

#include <string>

class FileAssembler
{
public:

    static bool assemble(
        const std::string& storageDir,
        const std::string& outputFilePath,
        int totalPieces
    );
};
