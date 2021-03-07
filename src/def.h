#ifndef ARGS_PARSER_DEF_H
#define ARGS_PARSER_DEF_H

#if defined(_WIN32) || defined(_WIN64)
    #define EXPORT __declspec(dllexport)
#elif defined(__linux__)
    #define EXPORT __attribute__((visibility("default")))
#endif

#define ARGS_PARSER_INIT_ARG_VARIABLE_FOR_CONSTRUCTOR(_name) \
            if(alias != nullptr) this->m_alias = alias; \
            this->m_name = name; \
            this->m_data = _name; \

#define ARGS_PARSER_FULL_EXCEPTION_CHECK \
                catch(std::invalid_argument&) { \
                    return EErrors::WRONG_DATA_TYPE; \
                } \
                catch(std::bad_any_cast&) { \
                    return EErrors::WRONG_DATA_TYPE; \
                } \
                catch(std::out_of_range&) { \
                    return EErrors::DATA_OVERFLOW; \
                } \
                catch(std::exception&) { \
                    return EErrors::UNDEFINED_ERROR; \
                } \

#define ARGS_PARSER_LIGHT_EXCEPTION_CHECK \
                catch(std::bad_any_cast&) { \
                    return EErrors::WRONG_DATA_TYPE; \
                } \
                catch(std::exception&) { \
                    return EErrors::UNDEFINED_ERROR; \
                } \

#endif // ARGS_PARSER_DEF_H