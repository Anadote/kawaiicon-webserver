#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <unistd.h>
#include <unistd.h>
#include "html.h"
#include "send.h"
#include "util.h"

//Sets the path of where the server i
void set_server_path(){
    char server_dir_relative[] = "/server_files/";
    
    char bin_path[128];
    memset(bin_path, 0, 128);
    readlink("/proc/self/exe", bin_path, 128 - 1);

    //Where to binary starts
    char *bin_start = strstr(bin_path, "/bin/server");
    if (!bin_start){
        perror("Bad naming?");
    }

    //The offset from the start to the "/server"
    size_t offset = bin_start - bin_path;

    size_t server_dir_size = offset + strlen(server_dir_relative) + 1;
    char *server_dir = malloc(sizeof(char) * server_dir_size);
    strncpy(server_dir, bin_path, offset);
    strcat(server_dir, server_dir_relative);

    //Sets the global const
    SERVER_DIR = server_dir;
    SERVER_DIR_SIZE = server_dir_size;

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
    memset(page_content, 0, PAGE_SIZE);

    //page_dir = server_page_dir + str
    size_t page_dir_size = SERVER_DIR_SIZE + strlen(str) + 1;
    page_dir = malloc(sizeof(char) * page_dir_size);
    strcpy(page_dir, SERVER_DIR);
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

//Gets the wanted page content
char *get_page(char *resource){

    char *page_found = check_page(resource);
    char *page_content = get_content(page_found);

    free(page_found);
    return page_content;
}