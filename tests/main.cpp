#include "./../src/Arg.h"
#include "./../src/bind.h"
#include "./../src/errors.h"
#include "./../src/parser.h"
#include "./../src/fetch.h"
#include "./../src/global.h"

#include <iostream>

#include <cstring>

int main(int argc, char** argv)
{
    int a = 0;

    args_parser::init(argc, argv);

    struct args_parser::Error err(args_parser::fetch("-test", "tt", &a));

    if(err.type == args_parser::EErrors::NO_ERRORS)
        printf("No errors found\n");
    else {
        printf("Error found at position %d with reason %#010X\n", err.position, err.type);
    }

    printf("%d\n", a);

    return 0;
}
