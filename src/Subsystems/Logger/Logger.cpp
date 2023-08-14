#include "Logger.h"

#include <iostream>
#include <sstream>

#include "../DataTools/TimeTools.h"

namespace Tempus {
    namespace Log {

        std::string prefix;
        Category category;

        bool Logger::ContainsCategory(const Category& category) {
            if (std::find(_enabledCategories.begin(), _enabledCategories.end(), category) != _enabledCategories.end())
                return true;

            return false;
        }

        std::string Logger::PrepareLogMessage(const Level& level, const std::string& message, const std::string& suffix) const {
            std::ostringstream buffer;

            buffer << T_STREAM_BRACKETS(DataTools::TimeTools::GetCurrentTimeAsString());
            buffer << " ";

            buffer << T_STREAM_BRACKETS(level);

            if (_category != Category::None) {
                buffer << T_STREAM_BRACKETS(_category);
            }

            if (!_prefix.empty()) {
                buffer << T_STREAM_BRACKETS(_prefix);
            }

            if (!suffix.empty()) {
                buffer << T_STREAM_BRACKETS(suffix);
            }

            buffer << " ";

            buffer << message;

            return buffer.str();
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

            _enabledCategories.emplace_back(category);
        }

        void Logger::DisableCategory(const Category& category) {
            if (!ContainsCategory(category))
                return;

            _enabledCategories.erase(std::find(_enabledCategories.begin(), _enabledCategories.end(), category));
        }

        Logger::Logger(Category category, std::string prefix)
            : _prefix(std::move(prefix)), _category(category) {
            EnableCategory(this->_category);
        }

        Logger::Logger(const Logger& other) {
            this->_prefix = other._prefix;
            this->_category = other._category;
        }

        Logger::~Logger() {
            DisableCategory(this->_category);
        }

        std::vector<Category> Logger::_enabledCategories;
        std::mutex Logger::_categoryMutex;
    };
}