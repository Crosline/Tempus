#include <Tempus.h>
#include <iostream>

class Game : public Tempus::Application {
public:
	Game() = default;

	~Game() = default;
};


std::unique_ptr<Tempus::Application> Tempus::CreateApplication() {
	const Log::Logger log(Log::Category::General, "Application");

	log.Debug("test enabled general");

	TLogger::DisableCategory(Log::Category::General);
	TLogger::SharedLogger->Debug("Shared test for disabled");
	log.Debug("test2 for disabled general", __func__);

	TLogger::EnableCategory(Log::Category::General);
	TLogger::SharedLogger->Debug("Shared test for enabled");
	log.Debug("test3 enabled general");

	return std::make_unique<Game>();
}