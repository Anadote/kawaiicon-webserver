#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "connection.h"
#include "send.h"
#include "request.h"

//TD
static void send_info(struct request *user_request){

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

   send_info(user_request);
   return 0;
}

int main(){
   connection(user_handler);
}

