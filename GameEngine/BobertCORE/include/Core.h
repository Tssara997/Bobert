/**
 * @file Core.h
 * @brief Core engine macros, platform detection, and API import/export definitions.
 */

#pragma once

#ifdef BB_PLATFORM_WINDOWS
  #ifdef BB_BUILD_DLL
    /// @brief Macro used for exporting/importing symbols in DLL builds
    #define Bobert_API __declspec(dllexport)
  #else
    #define Bobert_API __declspec(dllimport)
  #endif
#elif BB_PLATFORM_LINUX
  #ifdef BB_BUILD_DLL
    /// @brief Macro used for exporting/importing symbols in DLL builds
    #define Bobert_API __attribute__((visibility("default")))
  #else
    #define Bobert_API
  #endif
#else 
  #error Bobert only supports Windows!
#endif  


