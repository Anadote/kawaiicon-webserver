struct request{
   char *method;
   char *resource;
};

struct request *process_request(char *str);