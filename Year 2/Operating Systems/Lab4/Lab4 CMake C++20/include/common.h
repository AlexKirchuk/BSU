#ifndef COMMON_H
#define COMMON_H

#include <boost/interprocess/sync/named_mutex.hpp>
#include <boost/interprocess/sync/named_semaphore.hpp>
#include <boost/interprocess/managed_shared_memory.hpp>
#include <string>

namespace bip = boost::interprocess;

const int MAX_MESSAGE_LENGTH = 20;

namespace ipc_names
{
    inline const std::string MUTEX_NAME = "MutexAccess";
    inline const std::string EMPTY_NAME = "EmptySlots";
    inline const std::string FULL_NAME = "FullSlots";
    inline const std::string SHMEM_NAME = "SharedMemory";
    inline const std::string BUFFER_NAME = "RingBuffer";
}

struct RingBuffer
{
    int head;
    int tail;
};

inline bip::named_mutex open_mutex()
{
    return bip::named_mutex(bip::open_only, ipc_names::MUTEX_NAME.c_str());
}

inline bip::named_semaphore open_empty()
{
    return bip::named_semaphore(bip::open_only, ipc_names::EMPTY_NAME.c_str());
}

inline bip::named_semaphore open_full()
{
    return bip::named_semaphore(bip::open_only, ipc_names::FULL_NAME.c_str());
}

#endif