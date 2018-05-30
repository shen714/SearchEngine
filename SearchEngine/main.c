//
//  main.c
//  SearchEngine
//
//  Created by Shen guo on 5/25/18.
//  Copyright © 2018 Shen guo. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include "CreateHashMap.h"
#include "HMBasicFunc.h"
#include "SearchforWord.h"
#include "ResListFunc.h"

/*
 * 1.Read the database. Scan each word into "hashmap" one by one.
 * 2.Search word in the "hashmap". Return the file name in the list "result"
 * 3.Print the "result" out.
 * 4.Clear "hashmap" and "result".
 */
int main(int argc, char ** argv) {
    HashMap * hashMap = (HashMap *) calloc (1, sizeof(HashMap));
    scanDir("/Users/shenguo/Desktop/C_progamming/SearchEngine/SearchEngine/database", hashMap);
    
    HashResult * hashResult = (HashResult *) calloc(1, sizeof(HashResult));
    searchWord(hashMap, hashResult);
    
    HashResultNode * resultList = NULL;
    sortResult(hashResult, &resultList);
    
    printList(resultList);
    
    clearHashMap(hashMap);
    clearHashResult(hashResult);
    
    return 0;
}


