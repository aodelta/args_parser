
# args_parser
(MIT License)

C++ argument parser with binds, parsing and fetching.

Dll  export via Cmake is still in progress, I recommend for now including the src in the main project subdirectory
and include all files ^^'

Whatever how you parse it (binding or fetching) : 
- the 1st argument will be the principle name of the argument (nullptr forbidden)
- the 2dn argument will be the alias (nullptr allowed)
- the 3rd argument will be a variable of supported type, or a void function with supported params (none or one only)

Supported types :
  Variables  : **int**, **float** and **const char\*** 
  Functions : empty, **int**, **float** and **const char\*** 

Note : a dash is required at every argument start, for clearer argument management and faster iteration over arguments. If you want to change this behaviour, define ARGS_PARSER_DASH_NOT_REQUIRED before including the header.

There are 2 main ways you can retrieve value from argument with this utility.

## Binding

Useful for entry binding

```cpp
#include <args_parser.h>

void help();
void useNumber(int num);

int main(int argc, char* argv)
{
    args_parser::init(argc, argv); // REQUIRED before parsing or fetching anything
    
    float ratio = -1.0f;
    
    args_parser::bind("help", "h", help); // No data expected after the argument, will call help() if it founds the arg
    args_parser::bind("number", "n", useNumber); // int expected, will call useNumber with the number provided if no errors
    args_parser::bind("ratio", nullptr, &ratio); // float expected, no alias, will assign to ratio the value provided

    args_parser::Error err = args_parser::parse(); // Will parse every argument and
    if(err.type != args_parser::EErrors::NO_ERRORS)
        ;// handle it with err.position to know where things wrong
        
    return 0;
}
```

## Fetching

Useful to fetch any value at any moment in program

```cpp
#include <args_parser.h>

static bool animation_allowed = true;

void noAnimation() { animation_allowed = false; }

int startGame()
{
    // args_parser::init called somewhere before
    
    args_parser::Error err = args_parser::fetch("noanimation", nullptr, noAnimation);
    
    return 0;
}
```
