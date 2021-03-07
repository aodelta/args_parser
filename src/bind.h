#ifndef ARGS_PARSER_BIND_H
#define ARGS_PARSER_BIND_H

#include "def.h"
#include "Arg.h"

namespace args_parser {

    EXPORT void bind(const char* name, const char* alias, int* dest);
    EXPORT void bind(const char* name, const char* alias, float* dest);
    EXPORT void bind(const char* name, const char* alias, const char* dest);

    EXPORT void bind(const char* name, const char* alias, void(*function)(int d));
    EXPORT void bind(const char* name, const char* alias, void(*function)(float d));
    EXPORT void bind(const char* name, const char* alias, void(*function)(const char* d));

    EXPORT void bind(const char* name, const char* alias, void(*f)());


    void bind(const char* name, const char* alias, int* dest) {
        args.emplace_back(name, alias, dest);
    }
    void bind(const char* name, const char* alias, float* dest) {
        args.emplace_back(name, alias, dest);
    }
    void bind(const char* name, const char* alias, const char* dest) {
        args.emplace_back(name, alias, dest);
    }

    void bind(const char* name, const char* alias, void(*function)(int d)) {
        args.emplace_back(name, alias, function);
    }
    void bind(const char* name, const char* alias, void(*function)(float d)) {
        args.emplace_back(name, alias, function);
    }
    void bind(const char* name, const char* alias, void(*function)(const char* d)) {
        args.emplace_back(name, alias, function);
    }

    void bind(const char* name, const char* alias, void(*function)()) {
        args.emplace_back(name, alias, function);
    }
}

#endif // ARGS_PARSER_BIND_H