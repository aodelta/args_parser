#ifndef ARGS_PARSER_ARG_H
#define ARGS_PARSER_ARG_H

#include <string>
#include <vector>
#include <any>
#include <exception>
#include <stdexcept>

#include "./errors.h"

#include "def.h"

namespace args_parser {

    class EXPORT Arg;

    EXPORT std::vector<Arg> args;

    class Arg {
    public:
        enum ETypes {
            /*
                Variables & 0x00
                Functions & 0x10

                Allow the function isFuntion() to return & 0x10 instead of checking every different type of function, and so speed up the cast process
            */

            Integer = 0x01,
            Float = 0x02,
            CharArray = 0x03,
            
            FunctionEmpty = 0x11, // If it is a function without argument
            FunctionInteger = 0x12,
            FunctionFloat = 0x13,
            FunctionCharArray = 0x14
        };

        Arg(const char* name, const char* alias, int* data) {
            ARGS_PARSER_INIT_ARG_VARIABLE_FOR_CONSTRUCTOR(data)
            this->m_type = ETypes::Integer;
        }
        Arg(const char* name, const char* alias, float* data) {
            ARGS_PARSER_INIT_ARG_VARIABLE_FOR_CONSTRUCTOR(data)
            this->m_type = ETypes::Float;
        }
        Arg(const char* name, const char* alias, const char* data) {
            ARGS_PARSER_INIT_ARG_VARIABLE_FOR_CONSTRUCTOR(data)
            this->m_type = ETypes::CharArray;
        }
        Arg(const char* name, const char* alias, void(*function)()) {
            ARGS_PARSER_INIT_ARG_VARIABLE_FOR_CONSTRUCTOR(function)
            this->m_type = ETypes::FunctionEmpty;
        }
        Arg(const char* name, const char* alias, void(*function)(int)) {
            ARGS_PARSER_INIT_ARG_VARIABLE_FOR_CONSTRUCTOR(function)
            this->m_type = ETypes::FunctionInteger;
        }
        Arg(const char* name, const char* alias, void(*function)(float)) {
            ARGS_PARSER_INIT_ARG_VARIABLE_FOR_CONSTRUCTOR(function)
            this->m_type = ETypes::FunctionFloat;
        }
        Arg(const char* name, const char* alias, void(*function)(const char*)) {
            ARGS_PARSER_INIT_ARG_VARIABLE_FOR_CONSTRUCTOR(function)
            this->m_type = ETypes::FunctionCharArray;
        }

        EErrors handle(const char* data) const {
            if(this->isFunction()) { // if it is a function
                return this->callFunction(data);
            }
            else {
                return setDest(data);
            }
        }

    private:
        EErrors setDest(const char* d) const {
            if(this->m_type == ETypes::Integer) {
                try {
                    int value = std::stoi(d);
                    *(std::any_cast<int*>(this->m_data)) = value;
                }
                ARGS_PARSER_FULL_EXCEPTION_CHECK
            }
            else if(this->m_type == ETypes::Float) {
                try {
                    float value = std::stof(d);
                    *(std::any_cast<float*>(this->m_data)) = value;
                }
                ARGS_PARSER_FULL_EXCEPTION_CHECK
            }
            else if(this->m_type == ETypes::CharArray) {
                try {
                    const char* tmp = std::any_cast<const char*>(this->m_data);
                    tmp = d;
                }
                ARGS_PARSER_LIGHT_EXCEPTION_CHECK
            }
            return EErrors::NO_ERRORS;
        }

        EErrors callFunction(const char* d) const {
            if(this->m_type == ETypes::FunctionEmpty) {
                try {
                    std::any_cast<void(*)()>(this->m_data)();
                }
                ARGS_PARSER_LIGHT_EXCEPTION_CHECK
            }
            else if(this->m_type == ETypes::FunctionInteger) {
                try {
                    int value = std::stoi(d);
                    std::any_cast<void(*)(int)>(this->m_data)(value);
                }
                ARGS_PARSER_FULL_EXCEPTION_CHECK
            }
            else if(this->m_type == ETypes::FunctionFloat) {
                try {
                    float value = std::stof(d);
                    std::any_cast<void(*)(float)>(this->m_data)(value);
                }
                ARGS_PARSER_FULL_EXCEPTION_CHECK
            }
            else if(this->m_type == ETypes::FunctionCharArray) {
                try {
                    std::any_cast<void(*)(const char*)>(this->m_data)(d);
                }
                ARGS_PARSER_LIGHT_EXCEPTION_CHECK
            }
            return EErrors::NO_ERRORS;
        }

    public:
        [[nodiscard]] const char* alias()            const { return this->m_alias; }
        [[nodiscard]] const char* name()             const { return this->m_name; }
        [[nodiscard]] ETypes      type()             const { return this->m_type; }
        [[nodiscard]] bool        isFunction()       const { return this->m_type & 0x10; }

    private:
        const char* m_alias;
        const char* m_name;

        std::any m_data;
        ETypes m_type;
    };
}

#endif // ARGS_PARSER_ARG_H