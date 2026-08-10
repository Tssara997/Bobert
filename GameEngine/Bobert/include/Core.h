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

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#ifdef BB_PLATFORM_WINDOWS
  #ifdef BB_BUILD_DLL
    #define Bobert_API __declspec(dllexport)
  #else
    #define Bobert_API __declspec(dllimport)
  #endif
#elif BB_PLATFORM_LINUX
  #ifdef BB_BUILD_DLL
    #define Bobert_API __attribute__((visibility("default")))
  #else
    #define Bobert_API
  #endif
#else 
  #error Bobert only supports Windows!
#endif  


