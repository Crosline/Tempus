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

            FileLogger(Category category, const std::string& prefix, const std::string& filePath)
                : Logger(category, prefix) {
                _outputFile = std::ofstream(filePath);
                if (!_outputFile.is_open()) {
                    std::cerr << "Failed to open file: " << filePath << std::endl;
                    // throw std::runtime_error("Failed to open file" + filePath);
                    // TODO - Crosline: We may add a define symbol to either allow with warnings or throw exception.
                }
            }
            
            ~FileLogger() override;
        };
    }
}

