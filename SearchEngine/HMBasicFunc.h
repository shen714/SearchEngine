//
//  HMBasicFunc.h
//  SearchEngine
//
//  Created by Shen guo on 5/25/18.
//  Copyright © 2018 Shen guo. All rights reserved.
//

#ifndef HMBasicFunc_h
#define HMBasicFunc_h

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define SIZE 10

//The node of the value of HashNode. filename stores the file name of each word.
typedef struct File {
    char * fileName;
    struct File * next;
} File;

// The node in the first hashmap. Key stores the word in the file, value stores the file name.
typedef struct HashMapNode {
    char * key;
    File * value;
    struct HashMapNode * next;
} HashMapNode;

//The node of the second hashmap(in the function putResult_()). key stores the file name, count stores the number of time each files occur.
typedef struct HashResultNode {
    char * key;
    int count;
    struct HashResultNode * next;
} HashResultNode;

typedef struct HashMap {
    HashMapNode * hashArr[SIZE];
} HashMap;

typedef struct HashResult {
    HashResultNode * hashResultArr[SIZE];
} HashResult;

int hashFunc(char * key);

void set(HashMap * Hashmap, char * key, char * fileName);

File * get(HashMap * Hashmap, char * key);

void clearHashMap(HashMap * Hashmap);

void clearHashResult(HashResult * result);

#endif /* HMBasicFunc_h */
