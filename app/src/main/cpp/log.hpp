#pragma once

#define LOG_TAG "GeodeLauncher-Fix"

#include <android/log.h>
#include <fmt/core.h>

namespace log {
    template<typename... Args>
    inline void debug(fmt::format_string<Args...> fmt, Args&&... args) {
        std::string str = fmt::format(fmt, std::forward<Args>(args)...);
        __android_log_write(ANDROID_LOG_DEBUG, LOG_TAG, str.c_str());
    }

    template<typename... Args>
    inline void info(fmt::format_string<Args...> fmt, Args&&... args) {
        std::string str = fmt::format(fmt, std::forward<Args>(args)...);
        __android_log_write(ANDROID_LOG_INFO, LOG_TAG, str.c_str());
    }

    template<typename... Args>
    inline void warn(fmt::format_string<Args...> fmt, Args&&... args) {
        std::string str = fmt::format(fmt, std::forward<Args>(args)...);
        __android_log_write(ANDROID_LOG_WARN, LOG_TAG, str.c_str());
    }

    template<typename... Args>
    inline void error(fmt::format_string<Args...> fmt, Args&&... args) {
        std::string str = fmt::format(fmt, std::forward<Args>(args)...);
        __android_log_write(ANDROID_LOG_ERROR, LOG_TAG, str.c_str());
    }
}
