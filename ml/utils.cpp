#include "utils.hpp"

str reverse(str text)
{
    str res = "";
    for (size_t i = 0; i < text.size(); i++)
        res += text[text.size() - 1 - i];
    return res;
}
