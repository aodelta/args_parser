#ifndef ARGS_PARSER_FETCH_H
#define ARGS_PARSER_FETCH_H

#include "def.h"
#include "global.h"
#include "Arg.h"
#include "errors.h"

#include <cstring>

namespace args_parser {

    template<typename T>
    static Error fetch(const char* name, const char* alias, T data, Arg::ETypes type);

    EXPORT Error fetch(const char* name, const char* alias, int* dest);
    EXPORT Error fetch(const char* name, const char* alias, float* dest);
    EXPORT Error fetch(const char* name, const char* alias, const char* dest);

    EXPORT Error fetch(const char* name, const char* alias, void(*f)());
    EXPORT Error fetch(const char* name, const char* alias, void(*f)(int d));
    EXPORT Error fetch(const char* name, const char* alias, void(*f)(float d));
    EXPORT Error fetch(const char* name, const char* alias, void(*f)(const char* d));
    
    Error fetch(const char* name, const char* alias, int* dest)        { return fetch<int*>  (name, alias, dest, Arg::ETypes::Integer);}
    Error fetch(const char* name, const char* alias, float* dest)      { return fetch<float*>(name, alias, dest, Arg::ETypes::Float);}
    Error fetch(const char* name, const char* alias, const char* dest) { return fetch<const char*>(name, alias, dest, Arg::ETypes::CharArray  );}

    Error fetch(const char* name, const char* alias, void(*f)())               { return fetch<void(*)()>   (name, alias, f, Arg::ETypes::FunctionEmpty  );}
    Error fetch(const char* name, const char* alias, void(*f)(int d))          { return fetch<void(*)(int)>(name, alias, f, Arg::ETypes::FunctionInteger  );}
    Error fetch(const char* name, const char* alias, void(*f)(float d))        { return fetch<void(*)(float)>(name, alias, f, Arg::ETypes::FunctionFloat  );}
    Error fetch(const char* name, const char* alias, void(*f)(const char* d))  { return fetch<void(*)(const char*)>(name, alias, f, Arg::ETypes::FunctionCharArray  );}
    
    template<typename T>
    static Error fetch(const char* name, const char* alias, T data, Arg::ETypes type) {
        if(!intern::init) {
            return Error(EErrors::NOT_INIT, -1);
        }
        bool match;
        Arg arg(name, alias, data);
        
        for(int i(1); i < intern::argc; i++) { // For each argument passed
#if !defined(DASH_ALLOWED)
            if(strncmp(intern::argv[i], "-", 1) == 0) continue;
#endif
            match = false;
            if(arg.alias() != nullptr) { // If it possesses and alias
                if(strcmp(intern::argv[i], arg.alias()) == 0) { // Check it
                    match = true;
                }
            }
            if(!match && strcmp(intern::argv[i], arg.name()) == 0) { // !match to avoid comparing name in the case the alias matches
                match = true;
            }

            if(match) {
                if(arg.type() == Arg::ETypes::FunctionEmpty) // Only case where no data is following
                    arg.handle(nullptr);
                else {
                    if(i >= intern::argc) // last argument
                        return Error { EErrors::NO_DATA_FOLLOWING, i}; // Limits reached
                    else {
#if !defined(DASH_ALLOWED)
                        if(strncmp(intern::argv[i+1], "-", 1) == 0) {
                            return Error(EErrors::NO_DATA_FOLLOWING, i); // Data expected, but found another argument
                        }
#endif
                        EErrors errorType = arg.handle(intern::argv[i+1]);
                        if(errorType != EErrors::NO_ERRORS) return Error(errorType, i);

                        i++;
                    }
                }
            }
        }
        return Error { EErrors::NO_ERRORS, -1};
    }
}

#endif // ARGS_PARSER_FETCH_H