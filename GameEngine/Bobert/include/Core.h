#pragma once
#include <iostream>
#include <fstream>
#include <chrono>
#include <iomanip>
#include <queue>
#include <mutex>
#include <string>
#include <format>
#include <atomic>
#include <condition_variable>
#include <thread>

#ifdef BB_PLATFORM_WINDOWS
  #ifdef BB_BUILD_DLL
    #define Bobert_API __declspec(dllexport)
  #else
    #define Bobert_API __declspec(dllimport)
  #endif
#else 
  #error Bobert only supports Windows!
#endif  


