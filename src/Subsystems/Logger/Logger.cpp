#include "Logger.h"

#include <iostream>
#include <sstream>

namespace Tempus {
    namespace Log {

        static std::vector<Category> enabledCategories;
        std::string prefix;
        Category category;

        bool Logger::ContainsCategory(const Category& category) {
            if (std::find(enabledCategories.begin(), enabledCategories.end(), category) != enabledCategories.end())
                return true;

            return false;
        }

        void Logger::Log(const Level& level, const std::string& message, const std::string& suffix) const {
            if (category != Category::None && !ContainsCategory(category))
                return;

            std::ostringstream buffer;

            // Get and print the current time using HH:MM:SS format

            {
                std::tm currentTime{};
                const time_t now = time(nullptr);
                localtime_s(&currentTime, &now); // NOLINT(cert-err33-c)

                // Which one is better of the two?
                buffer << T_STREAM_BRACKETS(currentTime.tm_hour << ":" << currentTime.tm_min << ":" << currentTime.tm_sec);
            }

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

            std::cout << buffer.str() << std::endl;
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
        std::unique_ptr<Logger> Logger::SharedLogger = std::make_unique<Logger>(Category::None, "Shared");
    };
}