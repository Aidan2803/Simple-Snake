#include <fstream>
#include <iostream>
#include <string>

#pragma once

class Logger {
public:
  template <typename... Args>
  static void log(Args... args) {
    std::string result;
    concatHelper(result, args...);

    std::ofstream logFile("debug.log", std::ios_base::app);
    if (logFile.is_open()) {
      logFile << result << std::endl;
      logFile.close();
    } else {
      std::cerr << "Unable to open log file" << std::endl;
    }
  }

private:
  static void concatHelper(std::string&) {}

  static void concatHelper(std::string& result, const std::string& first) { result += first; }

  static void concatHelper(std::string& result, const char* first) { result += first; }

  static void concatHelper(std::string& result, char first) { result += first; }

  template <typename T,
            typename std::enable_if<!std::is_same<T, const char*>::value && !std::is_same<T, std::string>::value &&
                                        !std::is_same<T, char>::value,
                                    int>::type = 0>
  static void concatHelper(std::string& result, const T& first) {
    result += std::to_string(first);
  }

  template <typename T, typename... Args>
  static void concatHelper(std::string& result, const T& first, const Args&... args) {
    concatHelper(result, first);
    concatHelper(result, args...);
  }
};