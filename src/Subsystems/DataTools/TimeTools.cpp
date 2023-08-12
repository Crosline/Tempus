#include "TimeTools.h"

#include <iomanip>

namespace Tempus {
    namespace DataTools {
        namespace TimeTools {
            std::tm GetCurrentTime() {
                std::tm currentTime{};
                const time_t now = time(nullptr);
                localtime_s(&currentTime, &now); // NOLINT(cert-err33-c)

                return currentTime;
            }

            std::string GetCurrentTimeAsString() {
                const std::tm currentTime = GetCurrentTime();

                std::ostringstream buffer;
                buffer << std::setfill('0') << std::setw(2) << currentTime.tm_hour;
                buffer << ":" << std::setw(2) << currentTime.tm_min;
                buffer << ":" << std::setw(2) << currentTime.tm_sec;

                return buffer.str();
            }

        }
    }
}