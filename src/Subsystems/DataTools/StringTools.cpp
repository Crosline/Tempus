#include "StringTools.h"

#include <cstdarg>
#include <stdexcept>

#include "Common.h"

namespace Tempus {
    namespace DataTools {
        namespace StringTools {

            inline bool Contains(const char* message, const char* subtext) {
                return strstr(message, subtext);
            }

            unsafe std::string Format(const char* message, ...) {
                if (Contains(message, "%x")) {
                    throw std::runtime_error("[ERROR] %x cannot be used with formatting.");
                }

                if (strlen(message) == 0 ) {
                    throw std::runtime_error("[ERROR] String cannot be empty.");
                }

                va_list args;
                va_start(args, message);

                const size_t size_s = std::vsnprintf(nullptr, 0, message, args) + 1; // Extra space for '\0'
                if (size_s <= 1) {
                    throw std::runtime_error("[ERROR] String size cannot be smaller than 1.");
                }

                const std::unique_ptr<char[]> buffer(new char[size_s]);

                auto temp = std::vsnprintf(buffer.get(), size_s, message, args);

                va_end(args);

                std::string result = std::string(buffer.get(), buffer.get() + size_s - 1);

                if (result.empty()) {
                    throw std::runtime_error("[ERROR] Something went wrong while formatting.");
                }

                return result;
            }

        }
    }
}