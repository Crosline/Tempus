#pragma once
#include <fstream>

#include "Logger.h"

namespace Tempus {
    namespace Log {
        class TEMPUS_API FileLogger final : public Logger {
        private:
#pragma warning (push)
#pragma warning (disable : 4251)
            mutable std::ofstream _outputFile;
#pragma warning (pop)
        public:
            void Log(const Level& level, const std::string& message, const std::string& suffix) const override;

            FileLogger(Category category, const std::string& prefix, const std::string& filePath);

            ~FileLogger() override;
        };
    }
}

