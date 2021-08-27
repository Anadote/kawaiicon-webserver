#include <stdlib.h>
#include <string.h>

//Gets a static string and returns a malloc of it
char* alloc_str(char *buf){
   
   char *str = malloc(sizeof(char) * (strlen(buf) + 1));
   strcpy(str, buf);
   
   return str;
}

//Returns an allocated object of the two strings
char *concat_alloc(char *str1, char *str2){

   size_t len = strlen(str1) + strlen(str2) + 1;
   char *str = malloc(sizeof(char) * len);
   strcpy(str, str1);
   strcat(str, str2);
   return str;
}