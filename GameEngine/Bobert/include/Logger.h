#pragma once
#include "Core.h"
#include "pch.h"

namespace Bobert {
  class Bobert_API Logger {
    public:

      typedef enum class Level {INFO = 0, DEBUG, WARNING, ERROR, CRITICAL} Level;

      static void Init();
      static void Shutdown();

      Logger(const Logger&) = delete;
      Logger& operator=(const Logger&) = delete;
      Logger(Logger&&) = delete;
      Logger& operator=(Logger&&) = delete;

      static Logger& GetSingelton() {
        static Logger instance;
        return instance;
      }

      void Log(const std::string& message, Level level = Level::INFO);
      static void Info(const std::string& message);
      static void Debug(const std::string& message);
      static void Warning(const std::string& message);
      static void Error(const std::string& message);
      static void Critical(const std::string& message);

    private:
      Logger() = default;

      inline static std::chrono::system_clock::time_point TimeStart = std::chrono::system_clock::now();
      static constexpr std::string_view LoggerName = "Bobert_logger";
      inline static const std::filesystem::path fullPath = "Bobert.log";
      static constexpr std::string_view fmt = "[{}] [{}] {}";

      inline static std::queue<std::string> logQueue;
      inline static std::mutex queueMutex;
      inline static std::condition_variable cv;
      inline static std::thread workerThread;
      inline static std::atomic<bool> running = true;
      inline static bool initialized = false;


      static void ProcessQueue();

      static std::string_view GetLevelString(Level level);
      static std::string GetLocalTimeString();

  };
}