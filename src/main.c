#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "connection.h"
#include "send.h"
#include "request.h"
#include "html.h"

//Cleans up the struct
static void cleanup(struct request **user_request){

   //This so we get the propper address of the user struct
   struct request *request = (struct request*)user_request;

   free(request->method);
   free(request->resource);
   free(request);
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

   send_page(fd, user_request->resource);

   cleanup(&user_request);
   return 0;
}

int main(){
   set_server_path();
   connection(user_handler);
   
   //Need a better way than this
   free(SERVER_DIR);
}

