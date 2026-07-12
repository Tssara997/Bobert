#pragma once
#include "Core.h"

namespace Bobert {
  class Bobert_API Logger {
    public:

      typedef enum class Level {INFO = 0, DEBUG, WARNING, ERROR, CRITICAL} Level;

      Logger() = default;
      ~Logger();
      void Init();
      void Log(const std::string& message, Level level = Level::INFO);
      void Info(const std::string& message);
      void Debug(const std::string& message);
      void Warning(const std::string& message);
      void Error(const std::string& message);
      void Critical(const std::string& message);
      void Shutdown();

    private:
      static inline std::chrono::system_clock::time_point TimeStart = std::chrono::system_clock::now();
      static constexpr std::string_view LoggerName = "Bobert_logger";
      static constexpr std::string_view FileAdress = "Bobert.log";

      std::queue<std::string> logQueue;
      std::mutex queueMutex;
      std::condition_variable cv;
      std::thread workerThread;
      std::atomic<bool> running = true;

      void ProcessQueue();

      std::string_view GetLevelString(Level level);
      std::string GetLocalTimeString();
  };
}