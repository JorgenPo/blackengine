//
// Created by popof on 27.09.2018.
//

#ifndef BLACKENGINE_LOGGER_H
#define BLACKENGINE_LOGGER_H

#include <Exported.h>

#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>

namespace black {
enum class LogTarget {
  STDOUT,
  STDERR,
  FILE
};

enum class LogLevel {
  TRACE = 0,
  DEBUG = 1,
  INFO = 2,
  WARNING = 3,
  ERR = 4,
  CRITICAL = 5,
  OFF = 6
};

/**
 * Just a logger
 */
class BLACK_EXPORTED Logger {
  static const LogTarget DEFAULT_LOG_TARGET;
  static std::shared_ptr<Logger> defaultLogger;

  std::shared_ptr<spdlog::logger> logger;
public:
  /**
   * Init logging system
   */
  static void Initialize();

  /**
   * Add a new logger
   */
  static void AddLogger(LogTarget target, std::string_view name);

  /**
   * Remove logger
   */
  static void RemoveLogger(std::string_view name);

  /**
   * Set a minimum level of all loggers
   *
   * @param level Minimum log level
   */
  static void SetLogLevel(LogLevel level);

  /**
   * Return a logger pointer with a given name. If no such logger exist then create it with
   * default log target (stdout)
   *
   * @param name Logger name
   * @return
   */
  static std::shared_ptr<Logger> Get(std::string_view name);

  /**
   * Return a default logger
   * @return
   */
  static std::shared_ptr<Logger> Get();

private:
  static void AddStdOutLogger(std::string_view name);
  static void AddStdErrLogger(std::string_view name);
  static void InitializeFileLogger(std::string_view name);

public:
  explicit Logger(std::shared_ptr<spdlog::logger> logger);

  template<typename T>
  void trace(const T &msg) {
    this->logger->trace(msg);
  }

  template<typename... Args>
  void trace(const char *fmt, const Args &... args) {
    this->logger->trace(fmt, args...);
  }

  template<typename T>
  void debug(const T &msg) {
    this->logger->debug(msg);
  }

  template<typename... Args>
  void debug(const char *fmt, const Args &... args) {
    this->logger->debug(fmt, args...);
  }

  template<typename T>
  void info(const T &msg) {
    this->logger->info(msg);
  }

  template<typename... Args>
  void info(const char *fmt, const Args &... args) {
    this->logger->info(fmt, args...);
  }

  template<typename T>
  void warning(const T &msg) {
    this->logger->warn(msg);
  }

  template<typename... Args>
  void warning(const char *fmt, const Args &... args) {
    this->logger->warn(fmt, args...);
  }

  template<typename T>
  void error(const T &msg) {
    this->logger->error(msg);
  }

  template<typename... Args>
  void error(const char *fmt, const Args &... args) {
    this->logger->error(fmt, args...);
  }

  template<typename T>
  void critical(const T &msg) {
    this->logger->critical(msg);
  }

  template<typename... Args>
  void critical(const char *fmt, const Args &... args) {
    this->logger->critical(fmt, args...);
  }
};
}

#endif //BLACKENGINE_LOGGER_H
