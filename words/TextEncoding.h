#ifndef TEXTENCODING_H
#define TEXTENCODING_H

#include <cstddef>
#include <string>

namespace text_encoding {

inline std::string trimTrailingCarriageReturn(std::string value) {
    if (!value.empty() && value.back() == '\r') {
        value.pop_back();
    }
    return value;
}

inline std::string stripUtf8Bom(std::string value) {
    if (value.size() >= 3 &&
        static_cast<unsigned char>(value[0]) == 0xEF &&
        static_cast<unsigned char>(value[1]) == 0xBB &&
        static_cast<unsigned char>(value[2]) == 0xBF) {
        value.erase(0, 3);
    }
    return value;
}

inline bool decodeUtf8CodePoint(const std::string& value, std::size_t index,
                                std::size_t& width, unsigned int& code_point) {
    const unsigned char lead = static_cast<unsigned char>(value[index]);

    if (lead < 0x80) {
        width = 1;
        code_point = lead;
        return true;
    }

    if ((lead >> 5) == 0x6) {
        if (index + 1 >= value.size()) {
            return false;
        }

        const unsigned char trail = static_cast<unsigned char>(value[index + 1]);
        if ((trail & 0xC0) != 0x80) {
            return false;
        }

        width = 2;
        code_point = ((lead & 0x1F) << 6) | (trail & 0x3F);
        return true;
    }

    if ((lead >> 4) == 0xE) {
        if (index + 2 >= value.size()) {
            return false;
        }

        const unsigned char trail1 = static_cast<unsigned char>(value[index + 1]);
        const unsigned char trail2 = static_cast<unsigned char>(value[index + 2]);
        if ((trail1 & 0xC0) != 0x80 || (trail2 & 0xC0) != 0x80) {
            return false;
        }

        width = 3;
        code_point = ((lead & 0x0F) << 12) | ((trail1 & 0x3F) << 6) | (trail2 & 0x3F);
        return true;
    }

    if ((lead >> 3) == 0x1E) {
        if (index + 3 >= value.size()) {
            return false;
        }

        const unsigned char trail1 = static_cast<unsigned char>(value[index + 1]);
        const unsigned char trail2 = static_cast<unsigned char>(value[index + 2]);
        const unsigned char trail3 = static_cast<unsigned char>(value[index + 3]);
        if ((trail1 & 0xC0) != 0x80 || (trail2 & 0xC0) != 0x80 || (trail3 & 0xC0) != 0x80) {
            return false;
        }

        width = 4;
        code_point = ((lead & 0x07) << 18) | ((trail1 & 0x3F) << 12) | ((trail2 & 0x3F) << 6) | (trail3 & 0x3F);
        return true;
    }

    return false;
}

inline bool isValidUtf8(const std::string& value) {
    std::size_t index = 0;
    while (index < value.size()) {
        std::size_t width = 0;
        unsigned int code_point = 0;

        if (!decodeUtf8CodePoint(value, index, width, code_point)) {
            return false;
        }

        if ((width == 2 && code_point < 0x80) ||
            (width == 3 && code_point < 0x800) ||
            (width == 4 && code_point < 0x10000) ||
            code_point > 0x10FFFF ||
            (code_point >= 0xD800 && code_point <= 0xDFFF)) {
            return false;
        }

        index += width;
    }

    return true;
}

inline char toUpperCp1251(unsigned char ch) {
    if (ch >= 'a' && ch <= 'z') {
        return static_cast<char>(ch - 32);
    }

    if (ch >= 0xE0 && ch <= 0xFF) {
        return static_cast<char>(ch - 32);
    }

    if (ch == 0xB8) {
        return static_cast<char>(0xA8);
    }

    return static_cast<char>(ch);
}

inline std::string utf8ToCp1251(const std::string& value) {
    std::string result;
    result.reserve(value.size());

    std::size_t index = 0;
    if (value.size() >= 3 &&
        static_cast<unsigned char>(value[0]) == 0xEF &&
        static_cast<unsigned char>(value[1]) == 0xBB &&
        static_cast<unsigned char>(value[2]) == 0xBF) {
        index = 3;
    }

    while (index < value.size()) {
        std::size_t width = 0;
        unsigned int code_point = 0;

        if (!decodeUtf8CodePoint(value, index, width, code_point)) {
            result.push_back('?');
            ++index;
            continue;
        }

        if (code_point >= 0x0410 && code_point <= 0x042F) {
            result.push_back(static_cast<char>(0xC0 + (code_point - 0x0410)));
        } else if (code_point >= 0x0430 && code_point <= 0x044F) {
            result.push_back(static_cast<char>(0xE0 + (code_point - 0x0430)));
        } else if (code_point == 0x0401) {
            result.push_back(static_cast<char>(0xA8));
        } else if (code_point == 0x0451) {
            result.push_back(static_cast<char>(0xB8));
        } else if (code_point < 0x80) {
            result.push_back(static_cast<char>(code_point));
        } else {
            result.push_back('?');
        }

        index += width;
    }

    return result;
}

inline std::string normalizeWordEncoding(std::string value) {
    value = trimTrailingCarriageReturn(value);
    value = stripUtf8Bom(value);

    std::string normalized = isValidUtf8(value) ? utf8ToCp1251(value) : value;
    for (char& ch : normalized) {
        ch = toUpperCp1251(static_cast<unsigned char>(ch));
    }

    return normalized;
}

} // namespace text_encoding

#endif
