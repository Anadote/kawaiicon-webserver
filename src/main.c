#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "connection.h"
#include "send.h"
#include "request.h"

//Just sends the recv'd info back
static void send_info(int fd, struct request *user_request){

   sendstr(fd, "Server says hi\n\n");
   
   sendstr(fd, "Your method was: ");
   sendstr(fd, user_request->method);
   sendstr(fd, "\n");

   sendstr(fd, "Resource was: ");
   sendstr(fd, user_request->resource);
}

//Handles a single user
static int user_handler(int fd){

   char buf[4096];
   struct request *user_request = malloc(sizeof(struct request));

   read(fd, buf, 4096);

   user_request = process_request(buf);
   if (!user_request){
      return 1;
   }

   send_info(fd, user_request);
   return 0;
}

int main(){
   connection(user_handler);
}

