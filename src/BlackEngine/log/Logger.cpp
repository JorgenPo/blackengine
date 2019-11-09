//
// Created by popof on 27.09.2018.
//

#include "Logger.h"
#include <iostream>

namespace black {
std::shared_ptr<Logger> Logger::defaultLogger;
const LogTarget Logger::DEFAULT_LOG_TARGET = LogTarget::STDOUT;

Logger::Logger(std::shared_ptr<spdlog::logger> logger) : logger(std::move(logger)) {

}

void Logger::AddLogger(black::LogTarget target, std::string_view name) {
  switch (target) {
  case LogTarget::STDOUT:AddStdOutLogger(name);
    break;
  case LogTarget::STDERR:AddStdErrLogger(name);
  case LogTarget::FILE:InitializeFileLogger(name);
    break;
  }
}

void Logger::RemoveLogger(std::string_view name) {
  spdlog::drop(name.data());
}

void Logger::AddStdOutLogger(std::string_view name) {
  auto console = spdlog::stdout_color_mt(name.data());
}

void Logger::AddStdErrLogger(std::string_view name) {
  auto console = spdlog::stderr_color_mt(name.data());
}

void Logger::InitializeFileLogger(std::string_view name) {
  auto file = spdlog::stdout_color_mt("console");
}

void Logger::SetLogLevel(LogLevel level) {
  spdlog::set_level(static_cast<spdlog::level::level_enum>(level));
}

std::shared_ptr<Logger> Logger::Get(std::string_view name) {
  auto logger = spdlog::get(name.data());

  if (logger == nullptr) {
    Logger::AddLogger(DEFAULT_LOG_TARGET, name);
    logger = spdlog::get(name.data());
  }

  return std::make_shared<Logger>(logger);
}

std::shared_ptr<Logger> Logger::Get() {
  return defaultLogger;
}

void Logger::Initialize() {
  Logger::AddLogger(LogTarget::STDOUT, "Default");
  defaultLogger = Logger::Get("Default");
}

}
