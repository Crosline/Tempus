#pragma once
#include "API.h"
#include "Common.h"
#include "../../Logger/ConsoleLogger.h"
#include "../../Settings/ProjectSettings.h"

namespace Tempus {
    namespace Renderer {
        class TEMPUS_API BaseWindow {
        protected:
            bool _isRunning;
            Settings::ProjectSettings _settings;
            Log::ConsoleLogger _logger;
            
            explicit BaseWindow(Settings::ProjectSettings settings)
            : _isRunning(false), _settings(std::move(settings)), _logger(Log::Category::Rendering,"Window") {
                
            }

            virtual void PrepareWindow() = 0;
            virtual void Update() = 0;
            virtual void ShowWindow() = 0;
        public:
            virtual ~BaseWindow() = default;
        };

    }
}