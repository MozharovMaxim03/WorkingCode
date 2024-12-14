#pragma once
#include <string>
#include <vector>

using uchar = unsigned char;
using ushort = unsigned short;
using ulong = unsigned long;
using ulonglong = unsigned long long;
using uint = unsigned int;

using uint8 = unsigned char;
using uint16 = unsigned short;
using uint32 = unsigned long;
using uint64 = unsigned long long;

using str = std::string;
template <typename T> using vec = std::vector<T>;

str reverse(str text);

