#pragma once
#include "API.h"

#include <string>
#include <sstream>

#define T_TIME Tempus::DataTools::TimeTools

namespace Tempus {

    namespace DataTools {
        namespace TimeTools {
            TEMPUS_API std::tm GetCurrentTime();
            TEMPUS_API std::string GetCurrentTimeAsString();
            
        }
    }

}