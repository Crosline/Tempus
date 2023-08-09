#pragma once

#ifdef TEMPUS_WINDOWS
#ifdef TEMPUS_EXPORT_DLL
#define TEMPUS_API __declspec(dllexport)
#else
#define TEMPUS_API __declspec(dllimport)
#endif // TEMPUS_EXPORT_DLL
#else
#error Engine does not have support for this platform!
#endif // TEMPUS_WINDOWS
