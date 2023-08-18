#include "FileLogger.h"
#include "../ThreadTools/ThreadPool.h"

namespace Tempus {
    namespace Log {

        void FileLogger::Log(const Level& level, const std::string& message, const std::string& suffix) const {
            if (_category != Category::None && !ContainsCategory(_category))
                return;

            if (!_outputFile.is_open()) {
                return;
            }
            
            std::string result = PrepareLogMessage(level, message, suffix);

            Thread::ThreadPool::SharedPool.EnqueueJob([this, result]()
            {
                std::lock_guard<std::mutex> lock(_categoryMutex);
                _outputFile << result << std::endl;
            });
        }

        FileLogger::FileLogger(Category category, const std::string& prefix, const std::string& filePath): Logger(category, prefix) {
            _outputFile = std::ofstream(filePath);
            if (!_outputFile.is_open()) {
                std::cerr << "Failed to open file: " << filePath << std::endl;
                // throw std::runtime_error("Failed to open file" + filePath);
                // TODO - Crosline: We may add a define symbol to either allow with warnings or throw exception.
            }
        }

        FileLogger::~FileLogger() {
            std::lock_guard<std::mutex> lock(_categoryMutex);
            _outputFile.close();
        }

    }
}