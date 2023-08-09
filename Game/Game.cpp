#include <Tempus.h>
#include <iostream>

class Game : public Tempus::Application {
public:
	Game() = default;

	~Game() = default;
};


std::unique_ptr<Tempus::Application> Tempus::CreateApplication() {
	const Log::Logger log(Log::Category::General, "Application");

	log.Debug("test enabled general", __func__);
	TLogger::DisableCategory(Log::Category::General);
	log.Debug("test2 for disabled general", __func__);
	// TLogger::EnableCategory(Log::Category::General);
	// log.Debug("test3 enabled general", __func__);

	return std::make_unique<Game>();
}