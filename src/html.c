#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "html.h"
#include "send.h"

#define PAGE_SIZE 1024

//You've got to set this to the absolute of where server is
const char server_page_dir[] = "";

//Gets a static string and returns a malloc of it
static char* alloc_str(char *buf){
    char *str = malloc(sizeof(char) * (strlen(buf) + 1));
    strcpy(str, buf);
    return str;
    
}

//Checks the page, and makes the right path that the user will get
static char *check_page(char *str){

    if (!strcmp(str, "/") || 
        !strcmp(str, "index") || 
        !strcmp(str, "main") || 
        !strcmp(str, "index.html") || 
        !strcmp(str, "main.html")){
        return alloc_str("index.html");
    }
    else{
        return alloc_str("404.html");
    }
}

//Gets the file content from str
static char *get_content(char *str){

    FILE *f;
    char *page_dir;

    char page_content[PAGE_SIZE];

    //page_dir = server_page_dir + str
    size_t page_dir_size = strlen(server_page_dir) + strlen(str) + 1;
    page_dir = malloc(sizeof(char) * page_dir_size);
    strcpy(page_dir, server_page_dir);
    strcat(page_dir, str);

    f = fopen(page_dir, "rb");
    //We trust the url
    assert(f);

    fread(page_content, sizeof(char), PAGE_SIZE - 1, f);

    //Null terminates just in case
    page_content[PAGE_SIZE - 1] = '\0';

    fclose(f);
    free(page_dir);

    return alloc_str(page_content);
}

//Send the page from str
void send_page(int fd, char *str){

    char *page = check_page(str);
    char *page_content = get_content(page);

    sendstr(fd, page_content);
    free(page);
    free(page_content);
   
}