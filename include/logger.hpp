#include <fstream>
#include <iostream>

#pragma once

class Logger{
    public:
    static void logToFile(const std::string& message) {
      std::ofstream logFile("debug.log", std::ios_base::app);
      if (logFile.is_open()) {
          logFile << message << std::endl;
          logFile.close();
      } else {
          std::cerr << "Unable to open log file" << std::endl;
      }
  }
};