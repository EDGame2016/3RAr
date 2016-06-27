#include "toString.h"

//template <typename T>
std::string toString(const int& value)
{
    std::stringstream stream;
    stream << value;
    return stream.str();
}
