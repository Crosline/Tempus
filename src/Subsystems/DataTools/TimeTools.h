#pragma once
#include <string>
#include <sstream>

#include "API.h"

#define T_TIME Tempus::DataTools::TimeTools

namespace Tempus {

    namespace DataTools {
        namespace TimeTools {
            TEMPUS_API std::tm GetCurrentTime();
            TEMPUS_API std::string GetCurrentTimeAsString();

        }
    }

}