//Shamelessly copied from https://github.com/pwning/docs/blob/master/fork_accept.c
#include <arpa/inet.h>
#include <errno.h>
#include <pwd.h>
#include <signal.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <grp.h>
#include "connection.h"

const uint16_t port = 1337;

// Remember to check return values carefully in this function.
// Don't want to accidentally give people root :-)
static int drop_privs(char *username) {
   struct passwd *pw = getpwnam(username);
   if (pw == NULL) {
      fprintf(stderr, "User %s not found\n", username);
      return 1;
   }

   if (chdir(pw->pw_dir) != 0) {
      perror("chdir");
      return 1;
   }

   // Don't forget to drop supplemental groups. Forgetting this
   // has led to people escalating to root in some past CTFs :-)
   if (setgroups(0, NULL) != 0) {
      perror("setgroups");
      return 1;
   }

   if (setgid(pw->pw_gid) != 0) {
      perror("setgid");
      return 1;
   }

   if (setuid(pw->pw_uid) != 0) {
      perror("setuid");
      return 1;
   }

   return 0;
}

//Creates a connection, forks it and callds handler on it
int connection(int (*handler)(int fd)) {
   
   int rc;
   int opt;
   int sockfd;
   int clientfd;
   pid_t pid;
   struct sockaddr_in saddr = {0};

   if (signal(SIGCHLD, SIG_IGN) == SIG_ERR) {
      fputs("Failed to set SIGCHLD handler.", stderr);
      return 1;
   }

   sockfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
   if (sockfd == -1) {
      perror("socket");
      return 1;
   }

   opt = 1;
   if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &opt,
                  sizeof(opt)) != 0) {
      perror("setsockopt");
      return 1;
   }

   saddr.sin_family = AF_INET;
   saddr.sin_addr.s_addr = htonl(INADDR_ANY);
   saddr.sin_port = htons(port);

   if (bind(sockfd, (struct sockaddr *) &saddr,
            sizeof(saddr)) != 0) {
      perror("bind");
      return 1;
   }

   if (listen(sockfd, 20) != 0) {
      perror("listen");
      return 1;
   }

   while (1) {
      clientfd = accept(sockfd, NULL, NULL);
      if (clientfd == -1) {
         perror("accept");
         continue;
      }

      pid = fork();
      if (pid == -1) {
         perror("fork");
         close(clientfd);
         continue;
      }

      if (pid == 0) {
         // Avoid tons of long-running processes sticking around.
         alarm(10);
         close(sockfd);

         //Drop priviliages so we can run this as the right user
         rc = 0; //drop_privs("problemuser");
         if (rc == 0) {
               rc = handler(clientfd);
         }

         close(clientfd);
         _exit(rc);
      }
      close(clientfd);
   }

   return 0;
}