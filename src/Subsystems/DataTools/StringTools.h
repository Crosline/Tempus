#pragma once
#include "Common.h"
#include <stdexcept>
#include <cstdarg>
#include <cstdio>
#include <string>
#include <memory>

namespace Tempus {
    namespace DataTools {
        namespace StringTools {
            
            template <typename... Args>
            std::string string_format(const std::string& format, Args... args) {
                const int size_s = std::snprintf(nullptr, 0, format.c_str(), args...) + 1; // Extra space for '\0'

                if (size_s <= 0)
                    throw std::exception("Error during formatting.");
                
                auto size = static_cast<size_t>(size_s);
                std::unique_ptr<char[]> buf(new char[size]);
                std::snprintf(buf.get(), size, format.c_str(), args...);
                return std::string(buf.get(), buf.get() + size - 1); // We don't want the '\0' inside
            }
        }
    }
}