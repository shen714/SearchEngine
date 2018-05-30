//
//  SearchforWord.c
//  SearchEngine
//
//  Created by Shen guo on 5/26/18.
//  Copyright © 2018 Shen guo. All rights reserved.
//

#include <stdlib.h>
#include <string.h>
#include "HMBasicFunc.h"
#include "SearchforWord.h"

HashResultNode * searchFile_(HashResult * hashResult, char * fileName) {
    int keyIndex = hashFunc(fileName);
    if(hashResult->hashResultArr[keyIndex] == NULL) {
        return NULL;
    }
    HashResultNode * temp = hashResult->hashResultArr[keyIndex];
    while(temp != NULL) {
        if(!strcmp(temp->key, fileName)) {
            return temp;
        }
        temp = temp->next;
    }
    
    return NULL;
}

void insertResultNode_(HashResult * hashResult, char * fileName) {
    int keyIndex = hashFunc(fileName);
    
    HashResultNode * toInsert = (HashResultNode *) malloc(sizeof(HashResultNode));
    toInsert->key = (char *) malloc(sizeof(strlen(fileName) + 1));
    strcpy(toInsert->key, fileName);
    toInsert->count = 1;
    
    toInsert->next = hashResult->hashResultArr[keyIndex];
    hashResult->hashResultArr[keyIndex] = toInsert;
}

/**
 * @param sourceFile The File list which returned by get(). It is the value of HashMap(the list of file name).
 * @param hashResult The result of puResult_(). Its key is the filename and its count is the times of the file occurs.
 */
void mergetoHashResult_(File * sourceFile, HashResult * hashResult) {
    File * temp = sourceFile;
    while(temp != NULL) {
        HashResultNode * searchedResult = searchFile_(hashResult, temp->fileName);
        if(searchedResult == NULL) {
            insertResultNode_(hashResult, temp->fileName);
        } else {
            searchedResult->count++;
        }
        temp = temp->next;
    }
    return;
}

/*
 1)Scan the word need to be searched.
 2)search the word in the hashmap, put its value(the filename) into a linked lsit, while
 3)checking if the word have already exist. If not, add it; if it is, ignore.
 4)print the list.
 */
void searchWord(HashMap * hashMap, HashResult * hashResult) {
    printf("What do you want to search?\n");
    char wordtoSearch[SIZE];
    File * sourceFile;
    
    int i = 0;
    char ch;
   
    while(1) {
        ch = getchar();
        if(ch == ' ' || ch == EOF) {
            if(i != 0) {
                wordtoSearch[i] = '\0';
                sourceFile = get(hashMap, wordtoSearch);
                mergetoHashResult_(sourceFile, hashResult);
                
                if(ch == EOF) {
                    break;
                }
                i = 0;
            } else {
                continue;
            }
        } else {
            wordtoSearch[i++] = ch;
        }
    }
}
