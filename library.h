#pragma once
#ifndef CPPLOGER_LIBRARY_H
#define CPPLOGER_LIBRARY_H
#include <iostream>
#include <fstream>
#ifdef __use_cpplogger_macros

#define log cpplogger_log
#define info cpplogger_info
#define warning cpplogger_warning
#define error cpplogger_error

#endif
//C++ Compatible API
#ifdef __cplusplus
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
#endif


#ifdef __cplusplus
extern "C" {
#endif
// C-Compatible API
typedef struct {
    void *ptr;
}cpplogger_handle;
cpplogger_handle* cpplogger_create(bool console_enabled, const char* log_file);
void cpplogger_destroy(cpplogger_handle* handle);

void cpplogger_log(const char* msg, cpplogger_handle handle);
void cpplogger_info(const char* msg, int level, cpplogger_handle* handle);
void cpplogger_warning(const char* msg, int level, cpplogger_handle* handle);
void cpplogger_error(const char* msg, int level, cpplogger_handle* handle);

#ifdef __cplusplus
}
#endif
#endif //CPPLOGER_LIBRARY_H