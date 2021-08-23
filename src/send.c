#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <sys/socket.h>
#include "send.h"

//Will recv exactly the amount of specified bytes
//This is not always useful, as sometimes we just want o read
size_t recvlen(int fd, char *buf, size_t n) {
   size_t rc;
   size_t nread = 0;
   while (nread < n) {
      rc = recv(fd, buf + nread, n - nread, 0);
      if (rc == -1) {
         if (errno == EAGAIN || errno == EINTR) {
               continue;
         }
         return -1;
      }
      if (rc == 0) {
         break;
      }
      nread += rc;
   }
   return nread;
}

//Will always send the right amount of bytes
size_t sendlen(int fd, const char *buf, size_t n) {
   size_t rc;
   size_t nsent = 0;
   while (nsent < n) {
      rc = send(fd, buf + nsent, n - nsent, 0);
      if (rc == -1) {
         if (errno == EAGAIN || errno == EINTR) {
               continue;
         }
         return -1;
      }
      nsent += rc;
   }
   return nsent;
}

///Just sends the string
size_t sendstr(int fd, const char *str) {
   return sendlen(fd, str, strlen(str));
}