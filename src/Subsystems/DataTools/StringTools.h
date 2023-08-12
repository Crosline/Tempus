#pragma once
#include <string>

#include "Common.h"
#include "API.h"

#define T_STRING Tempus::DataTools::StringTools

namespace Tempus {
    namespace DataTools {
        namespace StringTools {

            inline bool Contains(const char* message, const char* subtext);

            // inspired by
            // https://stackoverflow.com/questions/2342162/stdstring-formatting-like-sprintf
            TEMPUS_API unsafe std::string Format(const char* message, ...);

        }
    }
}