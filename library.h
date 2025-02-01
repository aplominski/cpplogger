#ifndef CPPLOGER_LIBRARY_H
#define CPPLOGER_LIBRARY_H
#include <iostream>
#include <fstream>

class cpplogger {
public:
    cpplogger(bool console_enabled, std::string log_file);
    ~cpplogger();
    void log(std::string msg);
    void info(std::string msg, int level);
    void warning(std::string msg, int level);
    void error(std::string msg, int level);

private:
    bool console_enabled;
    std::string log_file;
    std::fstream log_file_stream;
};

#endif //CPPLOGER_LIBRARY_H