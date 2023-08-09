#pragma once
#include <iostream>
#include <utility>
#include "../../Framework/Common.h"
#include "Enums.h"

namespace Tempus {
	namespace Log {
#define T_STREAM_BRACKETS(x) "[" << (x) << "]"
// #define LOG_DEBUG(message, suffix) Tempus::Log::Logger::Debug(message, suffix)
// #define LOG_WARNING(message, suffix) Tempus::Log::Logger::Debug(message, suffix)
// #define LOG_ERROR(message, suffix) Tempus::Log::Logger::Debug(message, suffix)

		class Logger {
		private:
			std::string prefix;
			Category category;

			void Log(Level level, const std::string& message, const std::string& suffix) const
			{
				std::cout << T_STREAM_BRACKETS(level) << T_STREAM_BRACKETS(category) << T_STREAM_BRACKETS(prefix + suffix) << message << std::endl;
			}

			void Log(Level level, const std::string& message) const
			{
				std::cout << T_STREAM_BRACKETS(level) << T_STREAM_BRACKETS(category) << T_STREAM_BRACKETS(prefix) << message << std::endl;
			}

		public:
			Logger() = delete;

			explicit Logger(Category category, std::string prefix)
			: prefix(std::move(prefix)), category(category) { }

			void Debug(const std::string& message, const std::string& suffix = "") const
			{
				Log(Level::Debug, message, suffix);
			}

			void Warning(const std::string& message, const std::string& suffix = "") const
			{
				Log(Level::Warning, message, suffix);
			}

			void Error(const std::string& message, const std::string& suffix = "") const
			{
				Log(Level::Error, message, suffix);
			}
		};
	}
}