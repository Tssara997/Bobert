#include "include/Logger.h"

namespace Bobert {

  void Logger::Init() {
    if (initialized) {
      Warning("Tried to initialize Logger after already initializing it");
      return;
    }

    std::ofstream logFile(fullPath, std::ios::out | std::ios::trunc);
    if (!logFile.is_open()) {
      std::cerr << "Failed to open log file: " << LoggerName << std::endl;
      return;
    }
    logFile.close();

    workerThread = std::thread(&Logger::ProcessQueue);
    initialized = true;
    Info("Initialization Logger succseful");
  }


  void Logger::Log(const std::string& message, Level level) {
    auto levelStrV = GetLevelString(level);
    auto timeStr = GetLocalTimeString();

    // możliwość optymalizacji poźniej, zamiast pushować std::string do kolejny, pushować arg (queue.push({fmt, timeStr, levelStrV, message}))
    std::string log = std::vformat(fmt, std::make_format_args(timeStr, levelStrV,  message));

    {
      std::lock_guard<std::mutex> lock(queueMutex);
      logQueue.push(log);
    }
    cv.notify_one();
  }


  void Logger::Info(const std::string& message) { 
    GetSingelton().Log(message, Level::INFO);
  }



  void Logger::Debug(const std::string& message) {
    GetSingelton().Log(message, Level::DEBUG);
  }


  void Logger::Warning(const std::string& message) {
    GetSingelton().Log(message, Level::WARNING);
  }


  void Logger::Error(const std::string& message) {
    GetSingelton().Log(message, Level::ERROR);
  }


  void Logger::Critical(const std::string& message) {
    GetSingelton().Log(message, Level::CRITICAL);
  }


  void Logger::ProcessQueue() {
    std::ofstream file(fullPath, std::ios::app);

    while(true){
      std::string log;

      {
        std::unique_lock<std::mutex> lock(queueMutex);

        cv.wait(lock, [] {return !logQueue.empty() || !running; });

        if (!running && logQueue.empty())
          break;

        log = std::move(logQueue.front());
        logQueue.pop();
      }

      if (file.is_open()) {
        file << log << std::endl;
      }
    }
  }


  void Logger::Shutdown() {
    {
      Info("Logger is closing");
      std::lock_guard<std::mutex> lock(queueMutex);
      running = false;
    }
    cv.notify_one();
    if (workerThread.joinable())
      workerThread.join();
  }


  std::string_view Logger::GetLevelString(Level level) {
   switch (level) {
        case Level::INFO:     return "INFO";
        case Level::DEBUG:    return "DEBUG";
        case Level::WARNING:  return "WARNING";
        case Level::ERROR:    return "ERROR";
        case Level::CRITICAL: return "CRITICAL";
        default:              return "UNKNOWN";
    }
  }


  std::string Logger::GetLocalTimeString() {
    auto now = std::chrono::system_clock::now();
    std::time_t now_c = std::chrono::system_clock::to_time_t(now);

    std::tm now_tm;
  #ifdef BB_PLATFORM_WINDOWS
    localtime_s(&now_tm, &now_c); // tylko Windows
  #elif BB_PLATFORM_LINUX
    localtime_r(&now_c, &now_tm); // chyba zle dziala
  #endif

    std::ostringstream oss;
    oss << std::put_time(&now_tm, "%H:%M:%S");
    return oss.str();
  }
}