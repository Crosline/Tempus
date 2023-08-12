#include "Logger.h"

#include <iostream>
#include <sstream>

#include "../DataTools/TimeTools.h"
#include "../ThreadTools/ThreadPool.h"

namespace Tempus {
    namespace Log {

        std::string prefix;
        Category category;

        bool Logger::ContainsCategory(const Category& category) {
            if (std::find(enabledCategories.begin(), enabledCategories.end(), category) != enabledCategories.end())
                return true;

            return false;
        }

        std::string Logger::PrepareLogMessage(const Level& level, const std::string& message, const std::string& suffix) const {
            std::ostringstream buffer;

            buffer << T_STREAM_BRACKETS(DataTools::TimeTools::GetCurrentTimeAsString());
            buffer << " ";

            buffer << T_STREAM_BRACKETS(level);

            if (category != Category::None) {
                buffer << T_STREAM_BRACKETS(category);
            }

            if (!prefix.empty()) {
                buffer << T_STREAM_BRACKETS(prefix);
            }

            if (!suffix.empty()) {
                buffer << T_STREAM_BRACKETS(suffix);
            }

            buffer << " ";

            buffer << message;

            return buffer.str();
        }

        void Logger::Log(const Level& level, const std::string& message, const std::string& suffix) const {
            if (category != Category::None && !ContainsCategory(category))
                return;

            std::string result = PrepareLogMessage(level, message, suffix);

            Thread::ThreadPool::SharedPool.EnqueueJob([this, result]()
            {
                std::lock_guard<std::mutex> lock(categoryMutex);
                std::cout << result << std::endl;
            });
        }

        void Logger::Debug(const std::string& message, const std::string& suffix) const {
            Log(Level::Debug, message, suffix);
        }

        void Logger::Warning(const std::string& message, const std::string& suffix) const {
            Log(Level::Warning, message, suffix);
        }

        void Logger::Error(const std::string& message, const std::string& suffix) const {
            Log(Level::Error, message, suffix);
        }


        void Logger::EnableCategory(const Category& category) {
            if (ContainsCategory(category))
                return;

            enabledCategories.emplace_back(category);
        }

        void Logger::DisableCategory(const Category& category) {
            if (!ContainsCategory(category))
                return;

            enabledCategories.erase(std::find(enabledCategories.begin(), enabledCategories.end(), category));
        }

        Logger::Logger(Category category, std::string prefix)
            : prefix(std::move(prefix)), category(category) {
            EnableCategory(this->category);
        }

        Logger::Logger(const Logger& other) {
            this->prefix = other.prefix;
            this->category = other.category;
        }

        Logger::~Logger() {
            DisableCategory(this->category);
        }

        std::vector<Category> Logger::enabledCategories;
        std::mutex Logger::categoryMutex;
        std::unique_ptr<Logger> Logger::SharedLogger = std::make_unique<Logger>(Category::None, "Shared");
    };
}