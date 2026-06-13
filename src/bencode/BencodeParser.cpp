#include "BencodeParser.h"

#include <stdexcept>
#include <cctype>

std::string BencodeParser::parseString(
    const std::string& data,
    size_t& pos
) {
    if (pos >= data.size()) {
        throw std::runtime_error("Malformed bencode: unexpected end of input when parsing string");
    }

    size_t colon = data.find(':', pos);
    if (colon == std::string::npos) {
        throw std::runtime_error("Malformed bencode: missing colon in string specification");
    }

    int len = 0;
    try {
        len = std::stoi(
            data.substr(pos, colon - pos)
        );
    } catch (...) {
        throw std::runtime_error("Malformed bencode: invalid string length specifier");
    }

    if (len < 0) {
        throw std::runtime_error("Malformed bencode: negative string length is invalid");
    }

    pos = colon + 1;

    if (pos + len > data.size()) {
        throw std::runtime_error("Malformed bencode: string length out of bounds");
    }

    std::string result =
        data.substr(pos, len);

    pos += len;

    return result;
}

long long BencodeParser::parseInteger(
    const std::string& data,
    size_t& pos
) {
    if (pos >= data.size() || data[pos] != 'i') {
        throw std::runtime_error("Malformed bencode: expected 'i' for integer");
    }
    pos++; // skip 'i'

    size_t end = data.find('e', pos);
    if (end == std::string::npos) {
        throw std::runtime_error("Malformed bencode: missing 'e' to end integer");
    }

    long long value = 0;
    try {
        value = std::stoll(
            data.substr(pos, end - pos)
        );
    } catch (...) {
        throw std::runtime_error("Malformed bencode: invalid integer format");
    }

    pos = end + 1;

    return value;
}

BencodeList BencodeParser::parseList(
    const std::string& data,
    size_t& pos
) {
    if (pos >= data.size() || data[pos] != 'l') {
        throw std::runtime_error("Malformed bencode: expected 'l' for list");
    }
    pos++; // skip 'l'

    BencodeList list;

    while (pos < data.size() && data[pos] != 'e') {
        list.push_back(
            parse(data, pos)
        );
    }

    if (pos >= data.size()) {
        throw std::runtime_error("Malformed bencode: list not closed with 'e'");
    }

    pos++; // skip 'e'

    return list;
}

BencodeDict BencodeParser::parseDictionary(
    const std::string& data,
    size_t& pos
) {
    if (pos >= data.size() || data[pos] != 'd') {
        throw std::runtime_error("Malformed bencode: expected 'd' for dictionary");
    }
    pos++; // skip 'd'

    BencodeDict dict;

    while (pos < data.size() && data[pos] != 'e') {
        if (!std::isdigit(static_cast<unsigned char>(data[pos]))) {
            throw std::runtime_error("Malformed bencode: dictionary keys must be strings");
        }

        std::string key =
            parseString(data, pos);

        BencodeValue value =
            parse(data, pos);

        dict[key] = value;
    }

    if (pos >= data.size()) {
        throw std::runtime_error("Malformed bencode: dictionary not closed with 'e'");
    }

    pos++; // skip 'e'

    return dict;
}

BencodeValue BencodeParser::parse(
    const std::string& data,
    size_t& pos
) {
    if (pos >= data.size()) {
        throw std::runtime_error("Malformed bencode: unexpected end of input");
    }

    char c = data[pos];

    if (std::isdigit(static_cast<unsigned char>(c)))
        return BencodeValue(
            parseString(data, pos)
        );

    if (c == 'i')
        return BencodeValue(
            parseInteger(data, pos)
        );

    if (c == 'l')
        return BencodeValue(
            parseList(data, pos)
        );

    if (c == 'd')
        return BencodeValue(
            parseDictionary(data, pos)
        );

    throw std::runtime_error(
        std::string("Malformed bencode: unknown type character '") + c + "'"
    );
}