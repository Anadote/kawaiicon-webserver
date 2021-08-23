#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "request.h"

//Gets the method via strcmp
static char *get_method(char *str){

   if (strlen(str) <= 6){
      return NULL;
   }
   else if (!strncmp(str, "GET", 3)){
      return "GET";
   }
   else if (!strncmp(str, "HEAD", 4)){
      return "HEAD";
   }
   else
   {
      return NULL;
   }
}

//TD
static char *get_resource(char *str){
   return NULL;
}

//Processes the user request, each method does it individually
struct request *process_request(char *str){

   struct request *user_request = malloc(sizeof(struct request));

   char *user_method = get_method(str);
   if (!user_method){
      return NULL;
   }
   user_request->method = user_method;
   
   char *user_resource = get_resource(str);
   if (!user_resource){
      return NULL;
   }
   user_request->resource = user_resource;
   
   return user_request;
}