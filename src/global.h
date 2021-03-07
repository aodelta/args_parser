#ifndef ARGS_PARSER_GLOBAL_H
#define ARGS_PARSER_GLOBAL_H

namespace args_parser {
    namespace intern {
        int argc;
        char** argv;
        bool init = false;
    }
    
    void init(int argc, char** argv)
    {
        intern::argc = argc;
        intern::argv = argv;
        intern::init = true;
    }
}



#endif // ARGS_PARSER_GLOBAL_H