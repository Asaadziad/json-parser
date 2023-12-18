#ifndef PARSER_H
#define PARSER_H

#include "stddef.h"

typedef struct token* Token;
typedef struct json_obj_arr* JSONObjectsArr;
typedef struct json_obj* JSONObject;

/*
 * will parse a given Json file
 * @return: an array of Json objects
 * */
JSONObjectsArr parse(const char* file_path);

/*
 * @args: Json objects array struct
 * @return: array size
 * */
size_t getJSOArraySize(JSONObjectsArr arr);

/*
 * @args: Json objects array struct
 * @return: Json objects
 * */
JSONObject* getJSOArray(JSONObjectsArr arr);

/*
 * @args: JSON Object
 * @return: JSON Object tokens
 * */
Token* getJSOTokens(JSONObject obj);

/*
 * free's the memory allocated for JSON objects array
 * */
void destroyJSONObjects(JSONObjectsArr objects);

#endif
