# 文件和目录

## 引言

chapter03说明了文件IO的内容，主要围绕了打开文件、读文件、写文件等内容展开，重点关注文件在内存中的内核数据结构，例如进程表项、文件表项等，重点关注文件的数据，本章将从stat函数开始，逐一介绍文件的属性，并详细说明UNIX文件系统的结构以及符号链接等内容

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

