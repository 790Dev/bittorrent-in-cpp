#pragma once

#include <string>

#include "TrackerClient.h"

class TrackerRequestBuilder
{
public:

    static std::string build(
        const TrackerInfo& tracker,
        const std::string& encodedInfoHash,
        const std::string& peerId,
        long long left
    );
};