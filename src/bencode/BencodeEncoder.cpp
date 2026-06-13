#include "BencodeEncoder.h"

#include <sstream>
#include <variant>
#include <type_traits>

std::string BencodeEncoder::encode(const BencodeValue& value) {
    std::stringstream ss;
    
    std::visit([&ss](auto&& arg) {
        using T = std::decay_t<decltype(arg)>;
        if constexpr (std::is_same_v<T, std::string>) {
            ss << arg.length() << ":" << arg;
        } else if constexpr (std::is_same_v<T, long long>) {
            ss << "i" << arg << "e";
        } else if constexpr (std::is_same_v<T, BencodeList>) {
            ss << "l";
            for (const auto& item : arg) {
                ss << BencodeEncoder::encode(item);
            }
            ss << "e";
        } else if constexpr (std::is_same_v<T, BencodeDict>) {
            ss << "d";
            for (const auto& [key, val] : arg) {
                ss << key.length() << ":" << key;
                ss << BencodeEncoder::encode(val);
            }
            ss << "e";
        }
    }, value.value);

    return ss.str();
}
