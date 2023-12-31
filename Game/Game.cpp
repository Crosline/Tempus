#include <locale>
#include <Tempus.h>

class Game : public Tempus::Application {
public:
    Game() = default;

    ~Game() override = default;

    void Run() override {
        while (true) {
            
        }
    }
};

std::unique_ptr<Tempus::Application> Tempus::CreateApplication() {
    const Log::Logger* log = new Log::ConsoleLogger(Log::Category::General, "Application");
    const Log::Logger* log2 = new Log::FileLogger(Log::Category::General, "Application", "test.log");

    log->Debug("test enabled general");
    log2->Debug("test enabled general");


    TLogger::DisableCategory(Log::Category::General);
    log->Debug("test2 for disabled general", __func__);

    TLogger::SharedLogger->Debug("Shared test for disabled");
    TLogger::EnableCategory(Log::Category::General);
    TLogger::SharedLogger->Warning("Shared test for enabled");
    log->Debug("test3 enabled general");

    const std::string test = DataTools::StringTools::Format("a %d b", 5);
    log->Debug(test);
    log->Debug(DataTools::StringTools::Format("c %d", 5));
    log->Debug(DataTools::StringTools::Format("dd"));

    delete log;
    delete log2; 
    return std::make_unique<Game>();
}