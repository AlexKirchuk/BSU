#ifndef COMMON_H
#define COMMON_H
const int MAX_MESSAGE_LENGTH = 21;
struct RingBuffer
{
    int head;
    int tail;
};
#endif