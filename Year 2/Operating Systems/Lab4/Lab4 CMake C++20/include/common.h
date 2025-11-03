#ifndef COMMON_H
#define COMMON_H
const int MAX_MESSAGE_LENGTH = 20;
struct RingBuffer
{
    int head;
    int tail;
};
#endif