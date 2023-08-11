#pragma once
#include "Common.h"

#include <cstdarg>
#include <format>

namespace Tempus {
    namespace DataTools {
        namespace StringTools {

            inline bool Contains(const char* message, const char* subtext) {
                return strstr(message, subtext);
            }

            // inspired by
            // https://stackoverflow.com/questions/2342162/stdstring-formatting-like-sprintf
            unsafe std::string Format(const char* message, ...) {
                if (Contains(message, "%x")) {
                    throw std::exception("Error during formatting.");
                }

                va_list args;
                va_start(args, message);

                // Is the extra space for '\0' necessary?
                const size_t size_s = std::snprintf(nullptr, 0, message, args) + 1; // Extra space for '\0'
                if (size_s <= 1) {
                    throw std::exception("Error during formatting.");
                }

                const std::unique_ptr<char[]> buffer(new char[size_s]);

                auto temp = std::vsnprintf(buffer.get(), size_s, message, args);

                va_end(args);

                return std::string(buffer.get(), buffer.get() + size_s - 1);
            }

        }
    }
}