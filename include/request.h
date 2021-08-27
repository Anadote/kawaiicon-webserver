struct request{
   //Method, GET
   char *method;

   //The url/wanted page
   char *resource;

   //The verison of the http type
   char *http_type;
};

struct request *process_request(char *str);