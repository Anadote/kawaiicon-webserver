void send_page(int fd, char *str);

void set_server_path();

//Absoulte path of the server dir
char *SERVER_DIR;

//This is so we can save strlen
size_t SERVER_DIR_SIZE;

//The max size of a page
#define PAGE_SIZE 1024