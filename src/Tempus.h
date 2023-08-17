#pragma once


#include "Framework/API.h"
#include "Framework/EngineConfig.h"

#include "Core/Application.h"
#include "Core/EntryPoint.h"

/// Settings Subsystem ///
#include "Subsystems/Settings/ProjectSettings.h"

/// Logger Subsystem ///
#include "Subsystems/Logger/Logger.h"
#include "Subsystems/Logger/ConsoleLogger.h"
#include "Subsystems/Logger/FileLogger.h"
#include "Subsystems/Logger/Enums.h"

/// Data Tools ///
#include "Subsystems/DataTools/StringTools.h"
#include "Subsystems/DataTools/TimeTools.h"

/// Thread Tools ///
#include "Subsystems/ThreadTools/ThreadPool.h"

/// Renderer Subsystem ///
#include "Subsystems/Renderer/WindowTools/BaseWindow.h"
#include "Subsystems/Renderer/WindowTools/WinAPIWindow.h"