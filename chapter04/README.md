# 文件和目录

## 引言

chapter03说明了文件IO的内容，主要围绕了打开文件、读文件、写文件等内容展开，重点关注文件在内存中的内核数据结构，例如进程表项、文件表项等，本章将从stat函数开始，介绍文件的属性，并详细说明UNIX文件系统的结构以及符号链接等内容

## 函数stat、fstat、fstatat、lstat

```c
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
int stat(const char *pathname, struct stat *statbuf);
int fstat(int fd, struct stat *statbuf);
int lstat(const char *pathname, struct stat *statbuf);
#include <fcntl.h>           /* Definition of AT_* constants */
#include <sys/stat.h>
int fstatat(int dirfd, const char *pathname, struct stat *statbuf,int flags);
```

这些函数都用于获取文件的属性，将其填充到statbuf结构中。

1. 函数lstat与stat的区别在于参数pathname如果是符号链接，lstat会获取符号链接的属性，而不是其实际指向的文件
2. fstatat函数通过第一个参数dirfd指定相对目录，pathname为该相对目录下的路径，如果pathname为绝对路径，则忽略dirfd，dirfd可以被设置为`AT_FDCWD`，表示当前目录
3. fstatat函数的参数flags表示是否跟随符号链接，默认情况下fstatat函数会跟随符号链接，如果flags参数被设置为`AT_SYMLINK_NOFOLLOW`，表示不跟随符号链接，获取符号链接本身的内容

struct stat基本结构如下，包含了文件的各种属性：

```c
struct stat {
    mode_t st_mode;//file type & mode (permissions)
    ino_t st_ino;//i-node number
    dev_t st_dev;//device name (file system)
    dev_t st_rdev;//device name for special files
    nlink_t st_nlink;//number of links
    uid_t st_uid;//user ID of owner
    gid_t st_gid;//group ID of owner
    off_t st_size;//size in bytes, for regular files
    struct timespec st_atime;//time of last access
    struct timespec st_mtime;//time of last modification
    struct timespec st_ctime;//time of last file status change
    blksize_t st_blksize;//best I/O block size
    blkcnt_t st_blocks;//number of disk blocks allocated
};
```

**注意**：stat结构中不包含文件名，主要包含文件的元数据，文件名存在在DIR结构中，通过opendir和readdir能获取文件名

演示stat、fstat、fstatat、lstat函数的使用：[usage for stat、fstat、fstatat、lstat](./src/usage_example.c)

