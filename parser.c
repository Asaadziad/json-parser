#include "parser.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"


#define START_SIZE 8

struct token {
  char* key;
  char* lValue;
};

struct json_obj {
    int    size; // num of tokens
    Token* tokens;
};

struct json_obj_arr {
  size_t size;
  JSONObject* array;
};
/*
 *  Creates an empty Json object
 * */
static JSONObject createJsonObj(){
  JSONObject j = (JSONObject)malloc(sizeof(*j));
  if(!j) {
    fprintf(stderr, "Couldn't create json object");
    return NULL;
  }
  Token* ta = (Token*)malloc(sizeof(Token) * START_SIZE);
  if(!ta) {
    fprintf(stderr, "Couldn't create token array");
    return NULL;
  }
  j->size = 0;
  j->tokens = ta;
  return j;
}

static Token tokenize(char* line){
  Token t = (Token)malloc(sizeof(*t));
  if(!t) return NULL;
  char* token = strtok(line, ":");
    
  t->key = token;
  token = strtok(NULL,":");
  t->lValue = token;
  fprintf(stderr,"%s - %s",t->key,t->lValue);
 
  
  return t;
}


static char* strip_from_white_spaces(char* string) {
  char* s_string = NULL;
  char* start_ptr = string;
  char *current = string;
  size_t len = 0;
  while(*current != '\0') {
    if(*current == ' '){
      current = current+1;
      continue;
    }
    len++;
    current = current +1;
  }

  s_string = (char*)malloc(sizeof(char) * (len + 1));
  if(!s_string) return NULL;
  int index = 0;
  s_string[len] = '\0';
  while(index < len) {
    if(*start_ptr == ' '){
      start_ptr = start_ptr +1;
      continue;
    }
    s_string[index] = *start_ptr;
    index++;
    start_ptr = start_ptr + 1;
  }
  return s_string;
}


JSONObjectsArr parse(const char* file_path){
  FILE* file = fopen(file_path, "r");
  
  char* buffer = NULL;
  size_t len = 0;
  JSONObjectsArr arr = (JSONObjectsArr)malloc(sizeof(*arr));
 if(!arr) {
 fprintf(stderr, "Couldn't allocate JSON array");
 return NULL;
 } 
  JSONObject* objects = (JSONObject*)malloc(sizeof(JSONObject) * START_SIZE);
  if(!objects) return NULL;
  int i = 0;
  while(getline(&buffer, &len,file ) != -1){
    //TODO:: if we read an object opener ( { ) : create json  

   char* stripped_line = strip_from_white_spaces(buffer);
   if(strstr(stripped_line, "{")){
         JSONObject obj = createJsonObj();
         if(!obj) continue;
         while(!strstr(stripped_line, "}")){
            free(stripped_line);
            getline(&buffer, &len,file); 
            stripped_line = strip_from_white_spaces(buffer); 
 
            if(strstr(stripped_line, "}")) break; 
            obj->tokens[obj->size] = tokenize(stripped_line);    
            obj->size++;                    
         }
         objects[i] = obj;
         i++; 

    } 
           //TODO:: add obj to an array of JSon objects
    
  }
  arr->size = i+1;
  arr->array = objects;
  fclose(file);
  if(buffer) free(buffer);
  return arr;
}
 int main(){
  JSONObject* objects = parse("../data/dialouges.json");
  fprintf(stderr,"%d",objects[1]->size);
  return 0;
 }
