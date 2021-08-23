#include <stdio.h>

size_t recvlen(int fd, char *buf, size_t n);
size_t sendlen(int fd, const char *buf, size_t n);
size_t sendstr(int fd, const char *str);