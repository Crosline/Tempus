#pragma once
#include "Logger.h"

namespace Tempus {
    namespace Log {
        class TEMPUS_API ConsoleLogger final : public Logger {
        public:
            ConsoleLogger(const Category category, const std::string& prefix)
                : Logger(category, prefix) {
            }
            explicit ConsoleLogger(const Logger& other)
                : Logger(other) {
            }

            void Log(const Level& level, const std::string& message, const std::string& suffix) const override;
        };
    }
}

