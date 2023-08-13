#include <Tempus.h>
#include <iostream>

class Game : public Tempus::Application {
public:
	Game() = default;

	~Game() = default;
};


std::unique_ptr<Tempus::Application> Tempus::CreateApplication() {
	const Log::Logger* log = new Log::ConsoleLogger(Log::Category::General, "Application");
	const std::shared_ptr<Log::Logger> log2 = std::make_shared<Log::FileLogger>(Log::Category::General, "Application", "../logs/game_log.txt");

	log->Debug("test enabled general");
	log2->Debug("test enabled general");

	
	TLogger::DisableCategory(Log::Category::General);
	TLogger::SharedLogger->Debug("Shared test for disabled");
	log->Debug("test2 for disabled general", __func__);

	TLogger::EnableCategory(Log::Category::General);
	TLogger::SharedLogger->Error("Shared test for enabled");
	TLogger::SharedLogger->Warning("Shared test for enabled");
	log->Debug("test3 enabled general");

	const std::string test = DataTools::StringTools::Format("a %d b", 5);
	log->Debug(test);
	log->Debug(DataTools::StringTools::Format("c %d", 5));
	log->Debug(DataTools::StringTools::Format("dd"));

	delete log;
	return std::make_unique<Game>();
}