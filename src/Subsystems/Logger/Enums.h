#pragma once
#include <string>
#include <unordered_map>

namespace Tempus {
	namespace Log {
		enum class Level : char {
			Debug,
			Warning,
			Error
		};

		enum class Category : char {
			General,
			System,
			Core,
			Rendering,
			Engine,
			None
		};

		static const std::unordered_map<Category, std::string> categoryMap = {
			{Category::General, "General"},
			{Category::System, "System"},
			{Category::Core, "Core"},
			{Category::Rendering, "Rendering"}
		};

		static const std::unordered_map<Level, std::string> levelMap = {
			{Level::Debug, "Debug"},
			{Level::Warning, "Warning"},
			{Level::Error, "Error"}
		};

		inline std::ostream& operator<<(std::ostream& stream, const Category& logCategory) {
			const auto it = categoryMap.find(logCategory);
			if (it != categoryMap.end())
			{
				stream << it->second;
			}

			return stream;
		}

		inline std::ostream& operator<<(std::ostream& stream, const Level& logLevel) {
			const auto it = levelMap.find(logLevel);
			if (it != levelMap.end())
			{
				stream << it->second;
			}

			return stream;
		}
	}
}