//
// Created by Morpheus on 06-Oct-17.
//

#ifndef CYNICAL_ENGINE_CYNICAL_LOG_H
#define CYNICAL_ENGINE_CYNICAL_LOG_H

#include <stdio.h>

#if unix
#define ERROR_COLOR   "\x1B[31m"
#define WARNING_COLOR  "\x1B[33m"
#define NORMAL_COLOR "\x1B[0m"
#elif _WIN32
#define ERROR_COLOR
#define WARNING_COLOR
#define NORMAL_COLOR
#endif

#define INT_TO_STR_2(X) #X
#define INT_TO_STR(X) INT_TO_STR_2(X)

#define LOG_HEADER(COLOR,TYPE) COLOR "["TYPE"]: "
#define LOG_FOOTER "\n-> "__FILE__":" INT_TO_STR(__LINE__) "\n\n"; NORMAL_COLOR

typedef enum {
    LOG_MESSAGE,
    LOG_WARNING,
    LOG_ERROR,
} LOG_TYPE;

#ifdef CYNICAL_DEBUG

#define MESSAGE(MSG) {\
    const char message[] = LOG_HEADER(NORMAL_COLOR,"MESSAGE") MSG LOG_FOOTER; \
    printf(message);\
}\

#define WARNING(WARN_MESSAGE) {\
    const char message[] = LOG_HEADER(WARNING_COLOR,"WARNING") WARN_MESSAGE LOG_FOOTER; \
    printf(message);\
}\

#define ERROR(ERR_MESSAGE) {\
    const char message[] = LOG_HEADER(ERROR_COLOR,"ERROR") ERR_MESSAGE LOG_FOOTER; \
    printf(message);\
}\

#define ASSERT(result) {\
    if (!result) {\
        ERROR("Assertion failed!");\
    }\
}\

#define LOG(MSG,TYPE) {\
    switch (TYPE) {\
        case LOG_WARNING:\
            WARNING(MSG); \
            break;\
        case LOG_ERROR:\
            ERROR(MSG); \
            break;\
        default:\
            MESSAGE(MSG); \
            break;\
    }\
}\

#else

#define MESSAGE(MSG)
#define WARNING(WARN_MESSAGE)
#define ERROR(ERR_MESSAGE)
#define ASSERT(RESULT)
#define LOG(MESSAGE,TYPE)

#endif

#endif //CYNICAL_ENGINE_CYNICAL_LOG_H