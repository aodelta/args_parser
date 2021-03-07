#ifndef ARGS_PARSER_ERRORS_H
#define ARGS_PARSER_ERRORS_H

#include "def.h"

namespace args_parser {
    enum class EErrors : int {
        NO_ERRORS       = 0x00,
        UNDEFINED_ERROR = 0x01,
        NOT_INIT        = 0x02,


        // error & 0x00 CLIENT ERRORS
        NO_DATA_FOLLOWING = 0x11, // No data found next a correct argument that require data
        WRONG_DATA_TYPE   = 0x12, // The cast failed, so the data expected and the data provided aren't the same tyoe
        DATA_OVERFLOW     = 0x13, // Data too big to be casted into variable in memory

    };

    struct Error {
        EErrors type;
        int position;

        Error() {
            this->type = EErrors::NO_ERRORS;
            this->position = -2;
        }
        Error(EErrors type, int position) {
            this->type = type;
            this->position = position;
        }
    };
}

#endif // ARGS_PARSER_ERRORS_H