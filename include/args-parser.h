#ifndef ARGS_PARSER_H
#define ARGS_PARSER_H

#if defined(_WIN32) || defined(_WIN64)
    #define IMPORT __declspec(dllimport)
#elif defined(__linux__)
    #define IMPORT
#endif


namespace args_parser {
    enum EErrors {
        NO_ERRORS         = 0x00,
        UNDEFINED_ERROR   = 0x01,
        NO_DATA_FOLLOWING = 0x11,
        WRONG_DATA_TYPE   = 0x12,
        DATA_OVERFLOW     = 0x13,
    };
    
    class IMPORT Arg;
    IMPORT EErrors parse(const int argc, const char** argv);
    IMPORT void bind(const char* name, const char* alias, int* dest);
    IMPORT void bind(const char* name, const char* alias, float* dest);
    IMPORT void bind(const char* name, const char* alias, const char* dest);
    IMPORT void bind(const char* name, const char* alias, void(*f)(int d));
    IMPORT void bind(const char* name, const char* alias, void(*f)(float d));
    IMPORT void bind(const char* name, const char* alias, void(*f)(const char* d));
};


#endif // ARGS_PARSER_H