#include "ConsoleLogger.h"

#include "../ThreadTools/ThreadPool.h"

namespace Tempus {
    namespace Log {

        void ConsoleLogger::Log(const Level& level, const std::string& message, const std::string& suffix) const {
            if (_category != Category::None && !ContainsCategory(_category))
                return;

            std::string result = PrepareLogMessage(level, message, suffix);

            if (level == Level::Error) {
                std::cerr << result << std::endl;
                return;
            }
            
            Thread::ThreadPool::SharedPool.EnqueueJob([this, result]()
            {
            std::lock_guard<std::mutex> lock(categoryMutex);
                std::cout << result << std::endl;
            });
        }

        std::shared_ptr<Logger> Logger::SharedLogger = std::make_shared<ConsoleLogger>(Category::None, "Shared");
    }
}
