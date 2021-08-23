#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "connection.h"
#include "send.h"

//Handles a single user
static int user_handler(int fd){

   char buf[4096];

   //We just read and echo
   read(fd, buf, 4096);
   sendstr(fd, "Welcome from the server, here is your sent request:\n\n");
   sendstr(fd, buf);

   return 0;
}

int main(){
   connection(user_handler);
}

