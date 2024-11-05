# 文件I/O

## 引言

UNIX系统文件I/O主要关注下列问题：

1. 可用的文件I/O函数：open、read、write、lseek、close等
2. unbuffered I/O的概念和理解
3. 多进程文件共享
4. dup、fcntl、sync、fsync、ioctl等函数的用法

## 文件描述符

对于内核而言，所有打开的文件都通过文件描述符引用。文件描述符是一个非负整数，当打开一个文件或者创建一个新文件时，操作系统内核向进程返回一个文件描述符，读写文件时，将open或creat返回的文件描述符作为参数传递给read或write。

UNIX系统下，每一个进程默认打开3个文件描述符，分别是0、1、2，对应标准输入、标准输出和标准错误，在头文件`<unistd.h>`中分别用`STDIN_FILENO`、`STDOUT_FILENO`和`STDERR_FILENO`表示：[打印默认文件描述符](./src/default_fd.c)

> 文件描述符的最大值

文件描述符的最大值决定了进程能够打开的文件的最大数量，有多种方式可以查看文件描述符的最大值

```bash
ulimit -n # 表示当前会话允许打开的文件描述符的最大数量
cat /proc/sys/fs/file-max # 整个UNIX系统允许打开的文件描述符的最大数量
sysctl fs.file-max # 系统允许打开的文件描述符的最大数量
cat /proc/${process_id}/limits | grep "Max open files" # 查看指定进程文件描述符的最大值
```

[打印进程文件描述符的最大值](./src/max_fd.c)

