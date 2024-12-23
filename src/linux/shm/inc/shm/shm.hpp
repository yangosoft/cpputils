/**
 * @file shm.hpp
 * @brief Shared memory abstraction for POSIX systems.
 *
 *
 */

#pragma once

#include <errno.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>

#include <string>
// #include <expected>
#include <string_view>

namespace CppUtils
{

const int32_t INVALID_FD = -1;
class Shm
{
public:
    Shm()
        : fd(INVALID_FD)
        , ptr_shared_mem{nullptr}
    {
    }

    Shm(const std::string& file_mem_path)
        : mem_path(file_mem_path)
        , fd(INVALID_FD)
        , ptr_shared_mem{nullptr}
    {
    }

    /// @brief Open an existing shared memory
    /// @param file_mem_path Path to the shared memory
    /// @param mem_size Size of the shared memory
    /// @return 0 on success, -1 on error
    int32_t open_existing(const std::string& file_mem_path, std::size_t mem_size)
    {
        mem_path = file_mem_path;
        return open_existing(mem_size);
    }

    /// @brief Open an existing shared memory
    /// @param mem_size Size of the shared memory
    /// @return 0 on success, -1 on error
    int32_t open_existing(std::size_t mem_size)
    {
        if (fd != INVALID_FD) {
            return -1;
        }
        int flags = O_RDWR;
        return shared_open(flags, mem_size);
    }

    /// @brief Allocate a new shared memory
    /// @param mem_size Size of the shared memory
    /// @return 0 on success, -1 on error
    int32_t allocate(std::size_t mem_size)
    {
        if (fd != INVALID_FD) {
            return -1;
        }

        int flags = O_CREAT | O_EXCL | O_RDWR;

        return shared_open(flags, mem_size);
    }

    /// @brief Removes the shared memory file
    /// @return 0 on success, -1 on error
    int32_t unlink()
    {
        auto ret = shm_unlink(mem_path.c_str());
        if (ret != -1) {
            return 0;
        }
        return -1;
    }

    /// @brief Closes the shared memory
    void close()
    {
        if (fd != INVALID_FD) {
            ::close(fd);
        }
        fd = INVALID_FD;
    }

    /// @brief Get the pointer to the shared memory
    /// @return Pointer to the shared memory
    void* get_raw_ptr()
    {
        return ptr_shared_mem;
    }

    virtual ~Shm()
    {
        close();
    }

private:
    std::string mem_path;
    int fd;
    void* ptr_shared_mem;

    int32_t shared_open(int flags, std::size_t mem_size)
    {

        fd = shm_open(mem_path.c_str(), flags, S_IRUSR | S_IWUSR);

        if (fd == INVALID_FD) {
            return -1;
        }

        if (ftruncate(fd, mem_size) == INVALID_FD) {
            return -1;
        }

        ptr_shared_mem = mmap(nullptr, mem_size, PROT_WRITE | PROT_READ, MAP_SHARED, fd, 0);
        if (ptr_shared_mem == MAP_FAILED) {
            return -1;
        }

        return 0;
    }
};
}  // namespace CppUtils