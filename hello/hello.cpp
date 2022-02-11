#include <iostream>
#include <string_view>

#include <ctime>

#include <fuse.h>
#include <unistd.h>

#include <fmt/core.h>

namespace kq {

time_t init_timestamp;

using namespace std::literals::string_view_literals;

int getattr(char const* path, struct stat* st)
{
    st->st_uid = getuid();
    st->st_gid = getgid();
    st->st_mtime = init_timestamp;
    st->st_atime = init_timestamp;
    st->st_ctime = init_timestamp;

    if (path == "/"sv) {
        st->st_mode = S_IFDIR | 0400;
        st->st_nlink = 2;
    } else {
        st->st_mode = S_IFREG | 0400;
        st->st_nlink = 1;
        st->st_size = 4096;
    }

    return 0;
}

int readdir(char const* path, void* buffer,
    fuse_fill_dir_t filler, off_t offset, fuse_file_info* fi)
{
    filler(buffer, ".", nullptr, 0);
    filler(buffer, "..", nullptr, 0);

    if (path == "/"sv) {
        filler(buffer, "Hello, FUSE!", nullptr, 0);
    }

    return 0;
}

int read(char const* path, char* buffer, size_t size,
    off_t offset, fuse_file_info *fi)
{
    static auto message = fmt::format(
        "Hello, FUSE!\nCreated at {}\n", init_timestamp);

    if (path != "/Hello, FUSE!"sv)
        return -ENOENT;
    
    if (offset >= message.size())
        return 0;

    auto bytes_to_copy = std::min(size,
        message.size() - offset);
    auto begin = message.cbegin() + offset;
    std::copy(begin, begin + bytes_to_copy, buffer);
    return bytes_to_copy;
}

} // kq

int main(int argc, char** argv)
{
    fuse_operations ops = {
        .getattr = &kq::getattr,
        .read    = &kq::read,
        .readdir = &kq::readdir,
    };

    kq::init_timestamp = time(nullptr) - 20 * 3600 * 24;

    return fuse_main(argc, argv, &ops, nullptr);
}
