#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include "connection.h"
#include "send.h"
#include "request.h"
#include "html.h"
#include "util.h"

//Handles a single user
static int user_handler(int fd){

   char buf[4096];
   struct request *user_request = malloc(sizeof(struct request));
   
   //The headers from the server
   char *server_header;

   //The reply for the resource
   char *resource_number_reply;

   //The final response from the server
   char *server_reponse;

   read(fd, buf, 4096);

   user_request = process_request(buf);
   if (!user_request){
      return 1;
   }

   char *page = get_page(user_request->resource);
   if (!strcmp(page, "404.html")){
      resource_number_reply = alloc_str(" 404 Not Found\r\n\r\n");
   }
   else {
      resource_number_reply = alloc_str(" 200 OK\r\n\r\n");
   }

   server_header = concat_alloc(user_request->http_type, resource_number_reply);
   free(resource_number_reply); 

   server_reponse = concat_alloc(server_header, page);
   free(server_header);

   //Sends the actual reponse back to the user
   sendstr(fd, server_reponse);
   
   free(server_reponse);

   //Cleanup
   free(page);
   free(user_request->method);
   free(user_request->resource);
   free(user_request->http_type);
   free(user_request);
   return 0;
}

int main(){
   set_server_path();
   connection(user_handler);
   
   //Need a better way than this
   free(SERVER_DIR);
}