#include "library.h"

#include <cstring>
#include <iostream>
#include <fstream>

#include <iomanip>
#include <chrono>
#include <ctime>

cpplogger::cpplogger(bool console_enabled, std::string log_file) {
    this->console_enabled = console_enabled;
    this->log_file = log_file;
    std::fstream logfile;
    logfile.open(this->log_file, std::ios::in | std::ios::out | std::ios::app); // Dodajemy std::ios::app, żeby dodawać na końcu

    if (!logfile.is_open()) {
        logfile.clear();
        logfile.open(this->log_file, std::ios::out);
        logfile << "CPPLOGER STARTED\n";
    } else {
        logfile.write("CPPLOGER STARTED \n", strlen("CPPLOGER STARTED \n"));
    }
    this->log_file_stream = std::move(logfile);
    if (console_enabled) {
        this->info("Initalized cpplogger",0);
    }
}
cpplogger::~cpplogger() {
    this->log_file_stream.close();
}

void cpplogger::log(std::string msg) {
    auto now = std::chrono::system_clock::now();
    std::time_t time_t_now = std::chrono::system_clock::to_time_t(now);
    std::tm tm_now = *std::localtime(&time_t_now);
    std::ostringstream timestamp_stream;
    timestamp_stream << std::put_time(&tm_now, "%d:%m:%y %H:%M:%S");

    std::string message = "[ " + timestamp_stream.str() + " ] [ LOG ] " + msg + " \n";

    if (this->console_enabled) {

        std::cout << message << std::endl;
    }

    this->log_file_stream.write(message.c_str(),strlen(message.c_str()));

}
void cpplogger::info(std::string msg, int level) {
    auto now = std::chrono::system_clock::now();
    std::time_t time_t_now = std::chrono::system_clock::to_time_t(now);
    std::tm tm_now = *std::localtime(&time_t_now);
    std::ostringstream timestamp_stream;
    timestamp_stream << std::put_time(&tm_now, "%d:%m:%y %H:%M:%S");

    std::string message = "[ " + timestamp_stream.str() + " ] [ INFO LEVEL " + std::to_string(level) + " ] " + msg + " \n";
    if (this->console_enabled) {
        std::cout <<  message << std::endl;
    }
    this->log_file_stream.write(message.c_str(),strlen(message.c_str()));
}
void cpplogger::warning(std::string msg, int level) {
    auto now = std::chrono::system_clock::now();
    std::time_t time_t_now = std::chrono::system_clock::to_time_t(now);
    std::tm tm_now = *std::localtime(&time_t_now);
    std::ostringstream timestamp_stream;
    timestamp_stream << std::put_time(&tm_now, "%d:%m:%y %H:%M:%S");

    std::string message = "[ " + timestamp_stream.str() + " ] [ WARN LEVEL " + std::to_string(level) + " ] " + msg + "\n";
    if (this->console_enabled) {
        std::cout << message << std::endl;
    }
    this->log_file_stream.write(message.c_str(),strlen(message.c_str()));
}
void cpplogger::error(std::string msg, int level) {
    auto now = std::chrono::system_clock::now();
    std::time_t time_t_now = std::chrono::system_clock::to_time_t(now);
    std::tm tm_now = *std::localtime(&time_t_now);
    std::ostringstream timestamp_stream;
    timestamp_stream << std::put_time(&tm_now, "%d:%m:%y %H:%M:%S");

    std::string message = "[ " + timestamp_stream.str() + " ] [ ERROR LEVEL " + std::to_string(level) + " ] " + msg + "\n";
    if (this->console_enabled) {
        std::cout << message << std::endl;
    }
    this->log_file_stream.write(message.c_str(),strlen(message.c_str()));
}

bool cpplogger::getCoutLogEnabled() const {
    return this->console_enabled;
}
void cpplogger::setCoutLogEnabled(bool new_state) {
    this->console_enabled = new_state;
}

extern "C" {

cpplogger_handle* cpplogger_create(bool console_enabled, const char* log_file) {
    cpplogger_handle* handle = new cpplogger_handle;
    handle->ptr = new cpplogger(console_enabled, std::string(log_file));
    return handle;
}

void cpplogger_destroy(cpplogger_handle* handle) {
    if (handle) {
        delete static_cast<cpplogger*>(handle->ptr);
        delete handle;
    }
}

void cpplogger_log(const char* msg, cpplogger_handle* handle) {
    if (handle && handle->ptr) {
        static_cast<cpplogger*>(handle->ptr)->log(std::string(msg));
    }
}
void cpplogger_info(const char* msg, int level, cpplogger_handle* handle) {
    if (handle && handle->ptr) {
        static_cast<cpplogger*>(handle->ptr)->info(std::string(msg), level);
    }
}
void cpplogger_warning(const char* msg, int level, cpplogger_handle* handle) {
    if (handle && handle->ptr) {
        static_cast<cpplogger*>(handle->ptr)->warning(std::string(msg), level);
    }
}
void cpplogger_error(const char* msg, int level, cpplogger_handle* handle) {
    if (handle && handle->ptr) {
        static_cast<cpplogger*>(handle->ptr)->error(std::string(msg), level);
    }
}
bool cpplogger_getCoutLogEnabled(cpplogger_handle* handle) {
    if (handle && handle->ptr) {
        return static_cast<cpplogger*>(handle->ptr)->getCoutLogEnabled();
    }
}
void cpplogger_setCoutLogEnabled(cpplogger_handle* handle, bool new_state) {
    if (handle && handle->ptr) {
        static_cast<cpplogger*>(handle->ptr)->setCoutLogEnabled(new_state);
    }
}

}

