#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "request.h"
#include "util.h"

//Gets the method via strcmp
static char *get_method(char *str){

   if (strlen(str) <= 6){
      return NULL;
   }
   else if (!strncmp(str, "GET", 3)){
      return alloc_str("GET");
   }
   else if (!strncmp(str, "HEAD", 4)){
      return alloc_str("HEAD");
   }
   else
   {
      return NULL;
   }
}

//Gets the wanted resource by assuming spaces are around it
static char *get_resource(char *str){

   //Start of the resource
   char *start = strchr(str, ' ');
   if (!start){
      return NULL;
   }
   start++;

   char *end = strchr(start, ' ');
   if (!end){
      return NULL;
   }

   size_t len = end - start;

   //Two spaces right next to each other
   if (!len){
      return NULL;
   }

   char *resource = malloc(sizeof(char) * (len + 1) );
   strncat(resource, start, len);
   
   return resource;
}

static char *get_http_type(char *str){

   char *first_space = strchr(str, ' ');
   if (!first_space){
      return NULL;
   }
   first_space++;

   char *http_start = strchr(first_space, ' ');
   if (!http_start){
      return NULL;
   }
   http_start++;

   char *http_end = strstr(http_start, "\r\n");
   if (!http_end){
      return NULL;
   }

   size_t http_len = http_end - http_start;
   char *http_type = malloc(sizeof(char) * (http_len + 1));
   strncpy(http_type, http_start, http_len);

   return http_type;
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
   
   char *http_type = get_http_type(str);
   if (!http_type){
      return NULL;
   }

   user_request->http_type = http_type;

   return user_request;
}