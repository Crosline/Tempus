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

        FileLogger::~FileLogger() {
            _outputFile.close();
        }

    }
}