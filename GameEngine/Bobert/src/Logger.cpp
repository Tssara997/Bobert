#include "include/Logger.h"

namespace Bobert {
  void Logger::Init() {
    std::ofstream logFile(FileAdress.data(), std::ios::out | std::ios::trunc);
    if (!logFile.is_open()) {
      std::cerr << "Failed to open log file: " << FileAdress << std::endl;
      return;
    }
    logFile.close();

    workerThread = std::thread(&Logger::ProcessQueue, this);
  }

  void Logger::Log(const std::string& message, Level level) {
    // auto now = std::chrono::time_point_cast<std::chrono::seconds>(std::chrono::current_zone()->to_local(std::chrono::system_clock::now()));

    auto levelStrV = GetLevelString(level);
    auto timeStr = GetLocalTimeString();

    std::string log = std::vformat("[{}] [{}] {}", std::make_format_args(timeStr, levelStrV,  message));
    // std::string log = GetLocalTimeString() + " [" + GetLevelString(level) + "] " + message;

    queueMutex.lock();
    logQueue.push(log);
    queueMutex.unlock();
    cv.notify_one();
  }

  void Logger::Info(const std::string& message) {
    Log(message, Level::INFO);
  }

  void Logger::Debug(const std::string& message) {
    Log(message, Level::DEBUG);
  }

  void Logger::Warning(const std::string& message) {
    Log(message, Level::WARNING);
  }

  void Logger::Error(const std::string& message) {
    Log(message, Level::ERROR);
  }

  void Logger::Critical(const std::string& message) {
    Log(message, Level::CRITICAL);
  }

  void Logger::ProcessQueue() {
    std::ofstream file(FileAdress.data(), std::ios::app);

    while(true){
      std::unique_lock<std::mutex> lock1(queueMutex);

      cv.wait(lock1, [this] {return !logQueue.empty() || !running; });

      if (!running && logQueue.empty())
        break;

      std::string log = logQueue.front();
      logQueue.pop();

      lock1.unlock();

      if (file.is_open()) {
        file << log << std::endl;
      }
    }

    file.close();
  }

  void Logger::Shutdown() {
    {
      std::lock_guard<std::mutex> lock(queueMutex);
      running = false;
    }
    cv.notify_one();
    if (workerThread.joinable())
      workerThread.join();
  }

  Logger::~Logger() {
    Info("Logger is closing");
    Shutdown();
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
    localtime_s(&now_tm, &now_c); // tylko Windows

    std::ostringstream oss;
    oss << std::put_time(&now_tm, "%H:%M:%S");
    return oss.str();
  }
}