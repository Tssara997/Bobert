#pragma once

#ifdef BB_PLATFORM_WINDOWS
  #ifdef BB_BUILD_DLL
    #define Bobert_API __declspec(dllexport)
  #else
    #define Bobert_API __declspec(dllimport)
  #endif
#else 
  #error Bobert only supports Windows!
#endif  


