#ifndef ARGS_PARSER_PARSER_H
#define ARGS_PARSER_PARSER_H

#include <vector>
#include <cstring>

#include "def.h"
#include "global.h"
#include "Arg.h"
#include "./errors.h"

namespace args_parser {

    EXPORT Error parse() {
        if(!intern::init) {
            return Error(EErrors::NOT_INIT, -1);
        }
        bool match;

        for(int i(1); i < intern::argc; i++) { // For each argument passed
#if !defined(DASH_ALLOWED)
            if(strncmp(intern::argv[i], "-", 1) == 0) continue;
#endif
            match = false;
            for(const Arg& arg: args) { // For each possible argument 

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
        }
        return Error { EErrors::NO_ERRORS, -1};
    }
}

#endif // ARGS_PARSER_PARSER_H