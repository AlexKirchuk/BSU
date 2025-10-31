#ifndef COMMON_H
#define COMMON_H

#include <boost/shared_array.hpp>
#include <windows.h>
#include <string>

struct RingBuffer
{
    boost::shared_array<std::string> messages;
    int head;
    int tail;
    int capacity;
};

const int MAX_MESSAGE_LENGTH = 20;

#endif