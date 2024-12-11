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

## 文件类型

UNIX系统下常见的文件类型：

> 普通文件

regular file，普通文件中包含了某种形式的数据，至于这种数据是文本还是二进制，对于UNIX内核而言并未区别，对普通文件内容的解释由处理该文件的应用程序进行，例如.py文件由Python解释器执行，一个值得注意的例外是二进制可执行文件，UNIX系统下所有的二进制可执行文件都遵循一种标准化的格式，这种格式使内核能够确定程序文本和数据的加载位置，UNIX系统下常见可执行文件的格式为ELF

```bash
file $(which ls)
/bin/ls: ELF 64-bit LSB shared object, x86-64, version 1 (SYSV), dynamically linked, interpreter /lib64/ld-linux-x86-64.so.2, for GNU/Linux 3.2.0, BuildID[sha1]=9567f9a28e66f4d7ec4baf31cfbf68d0410f0ae6, stripped
```

> 目录文件

directory file，目录包含了目录下每一项的名字和指向这些项有关信息的指针，对于一个目录文件具有读权限的任一进程可以读取该目录下的内容，但只有内核才能对目录进行写入

```c
DIR* dir = opendir("/usr/include");
struct diren* entry = NULL;
while(entry=readdir(dir)){
    //...
}
```

> 块特殊文件

block special file，这种类型的文件提供对设备**带缓冲**的访问，每次访问以固定长度为单位进行

```bash
ls /dev/sda -l
brw-rw---- 1 root disk 8, 0 May  4  2024 /dev/sda
```

> 字符特殊文件

character special file，提供对设备**不带缓冲**的访问，每次访问长度可变，系统中的所有设备要么是字符特殊文件，要么是块特殊文件

> FIFO

也称命名管道，first in first out，主要用于进程间通信

> socket

用于网络通信

> 符号链接

符号链接指向另一个文件

可以通过struct stat结构中的st_mode成员判断文件类型，通过调用宏函数完成

| 宏         | 文件类型     |
| ---------- | ------------ |
| S_ISREG()  | 普通文件     |
| S_ISDIR()  | 目录文件     |
| S_ISCHR()  | 字符特殊文件 |
| S_ISBLK()  | 块特殊文件   |
| S_ISFIFO() | 管道或FIFO   |
| S_ISLNK()  | 符号链接     |
| S_ISSOCK() | 套接字       |

[使用st_mode判断文件类型](./src/st_mode.c)

## 文件的访问权限

文件的访问权限被分为可读(r)、可写(w)、可执行(x)，需要注意的是，这里提到的文件是指广义上的文件(包括普通文件、目录、字符设备、块设备)，而不是单指普通文件。通过`ls -l`可以查看文件的访问权限

```bash
ls -l /usr/include/stdio.h
-rw-r--r-- 1 root root 34649 Aug  8 14:47 /usr/include/stdio.h
```

如果想要修改文件的权限，可以使用chmod命令，例如

```bash
chmod u+x test.txt # 给文件的所有者添加可执行权限
chmod g+r test.txt # 给文件的所属组添加可读权限
chmod o+w test.txt # 给文件的other添加可写权限
```

文件访问权限的含义：

**r**：读权限，对于文件而言，有r权限表示可以查看文件中的内容，对于目录而言，有r权限可以查看目录中的每一项

**w**：写权限，对于文件而言，有w权限表示可以修改文件中的内容，对于目录而言，有w权限表示可以在目录下新建文件或删除文件

**x**：可执行权限，对于文件而言，有x权限表示文件可执行，对于目录而言，有x权限表示可以通过cd进入目录

[测试文件的访问权限](./src/permission_test.c)

## 函数access和函数faccessat

函数access用于测试文件的权限以及文件是否存在

```c
#include <unistd.h>
int access(const char *pathname, int mode);
```

| mode | 说明                         |
| ---- | ---------------------------- |
| F_OK | 测试文件是否存在             |
| R_OK | 测试是否具备对文件的读权限   |
| W_OK | 测试是否具备对文件的写权限   |
| X_OK | 测试是否具备对文件的执行权限 |

[函数access的使用](./src/access_usage.c)

faccessat与access功能基本一致

```c
#include <fcntl.h>           /* Definition of AT_* constants */
#include <unistd.h>
int faccessat(int dirfd, const char *pathname, int mode, int flags);
```

当pathname为绝对路径时，dirfd被忽略，当pathname为相对路径时，如果dirfd为AT_FDCWD，表示相对于当前路径，否则表示相对于指定路径，最后一个参数flags通常被设置为0

[函数faccessat的使用](./src/faccessat_usage.c)

