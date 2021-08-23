#include <stdlib.h>
#include "request.h"

//TD
static char *get_method(char *str){
   return NULL;
}

//TD
static char *get_resource(char *str){
   return NULL;
}



//Processes the user request, each method does it individually
struct request *process_request(char *str){

   struct request *user_request = malloc(sizeof(struct request));

   char *user_method = get_method(str);
   if (!str){
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