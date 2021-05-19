#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include <exception>
#include <new>


class Exception: public std::exception{};

class NodeExists: public Exception{};
class NodeDoesntExist: public Exception{};
class TreeHasData: public Exception{};

#endif //EXCEPTIONS_H
