#pragma once
#include "Enums.h"
#include <iostream>

namespace Tempus
{
	namespace Log
	{
		class Logger;
	}
}

using TLogger = Tempus::Log::Logger;

namespace Tempus {
	namespace Log {
#define T_STREAM_BRACKETS(x) "[" << (x) << "]"
#define T_LOGGER Tempus::Log::Logger
#define T_ENABLE_LOG(category) T_LOGGER::EnableCategory(category)
#define T_DISABLE_LOG(category) T_LOGGER::DisableCategory(category)
// #define LOG_DEBUG(message, suffix) Tempus::Log::Logger::Debug(message, suffix)
// #define LOG_WARNING(message, suffix) Tempus::Log::Logger::Debug(message, suffix)
// #define LOG_ERROR(message, suffix) Tempus::Log::Logger::Debug(message, suffix)

		class Logger {
		private:
			static std::vector<Category> enabledCategories;
			std::string prefix;
			Category category;

			static bool ContainsCategory(const Category& category) {
				if (std::find(enabledCategories.begin(), enabledCategories.end(), category) != enabledCategories.end())
					return true;

				return false;
			}

			void Log(Level level, const std::string& message, const std::string& suffix) const {
				if (!ContainsCategory(category))
					return;

				std::cout << T_STREAM_BRACKETS(level) << T_STREAM_BRACKETS(category) << T_STREAM_BRACKETS(prefix + suffix) << message << std::endl;
			}

		public:
			void Debug(const std::string& message, const std::string& suffix = "") const {
				Log(Level::Debug, message, suffix);
			}

			void Warning(const std::string& message, const std::string& suffix = "") const {
				Log(Level::Warning, message, suffix);
			}

			void Error(const std::string& message, const std::string& suffix = "") const {
				Log(Level::Error, message, suffix);
			}

			static void EnableCategory(const Category& category) {
				if (ContainsCategory(category))
					return;

				enabledCategories.emplace_back(category);
			}

			static void DisableCategory(const Category& category) {
				if (!ContainsCategory(category))
					return;

				enabledCategories.erase(std::find(enabledCategories.begin(), enabledCategories.end(), category));
			}

		public:
			Logger() = delete;

			explicit Logger(Category category, std::string prefix)
			: prefix(std::move(prefix)), category(category)
			{
				EnableCategory(category);
			}
			Logger(const Logger& other) {
				this->prefix = other.prefix;
				this->category = other.category;
			}
			~Logger() = default;
		};
		
		std::vector<Category> Logger::enabledCategories;
	}
}