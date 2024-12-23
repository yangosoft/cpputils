/**
 * @file futex.hpp
 * @brief Implementation of a futex-based mutex.
 *
 * This file contains the implementation of a mutex using futexes, based on Ulrich Drepper's
 * "Futexes Are Tricky" paper.
 *
 * @see https://www.akkadia.org/drepper/futex.pdf
 */

#pragma once

#include "futex.hpp"
#include "shm/shm.hpp"

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#include <atomic>
#include <memory>

namespace CppUtils
{

static bool file_exists(const std::string& file_path)
{
    struct stat buffer;
    return (stat(file_path.c_str(), &buffer) == 0);
}

class SharedFutex
{
public:
    SharedFutex(const std::string& mem_file_path)
        : file_path(mem_file_path)
        , ptr_futex(nullptr)
    {
        init(file_path);
    }

    SharedFutex()
        : ptr_futex(nullptr)
    {
    }

    int32_t init(const std::string& mem_path)
    {
        if (ptr_futex != nullptr) {
            return -1;
        }

        file_path = mem_path;

        if (file_exists("/dev/shm/" + mem_path)) {
            shm_atomic.open_existing(file_path, sizeof(int));
        } else {

            auto ret = shm_atomic.open_existing(file_path, sizeof(int));

            ret = shm_atomic.allocate(sizeof(int));

            if (ret != 0) {
                return ret;
            }
        }

        auto* ptr_int = static_cast<std::atomic_int*>(shm_atomic.get_raw_ptr());

        ptr_futex = std::make_unique<Futex>(ptr_int);
        return 0;
    }

    void lock()
    {
        ptr_futex->lock();
    }

    void unlock()
    {
        ptr_futex->unlock();
    }

private:
    std::string file_path;
    Shm shm_atomic;
    std::unique_ptr<Futex> ptr_futex;
};
}  // namespace CppUtils