//
//  ResListFunc.c
//  SearchEngine
//
//  Created by Shen guo on 5/30/18.
//  Copyright © 2018 Shen guo. All rights reserved.
//

#include <string.h>
#include "ResListFunc.h"

void swap_(HashResultNode * node1, HashResultNode * node2) {
    char cpyKey[10];
    strcpy(cpyKey, node1->key);
    int cpyCount = node1->count;
    
    strcpy(node1->key, node2->key);
    node1->count = node2->count;
    
    strcpy(node2->key, cpyKey);
    node2->count = cpyCount;
}


void bubblesort_(HashResultNode ** resultList) {
    HashResultNode * end = NULL;
    
    if(*resultList == NULL) {
        return;
    }
    
    int i;
    do {
        i = 0;
        HashResultNode * temp = *resultList;
        while(temp->next != end) {
            if(temp->count < temp->next->count) {
                swap_(temp, temp->next);
                i = 1;
            }
            temp = temp->next;
        }
        end = temp;
    }
    while(i);
}

void keyValuePair_(HashResult * hashResult, HashResultNode ** resultList) {
    for(int i = 0; i < SIZE; i++) {
        HashResultNode * temp = hashResult->hashResultArr[i];
        while(temp != NULL) {
            HashResultNode * insertResList = (HashResultNode *) malloc(sizeof(HashResultNode));
            insertResList->key = (char *) malloc(sizeof(temp->key) + 1);
            strcpy(insertResList->key, temp->key);
            insertResList->count = temp->count;
            insertResList->next = *resultList;
            *resultList = insertResList;
            
            temp = temp->next;
        }
        continue;
    }
}

void sortResult(HashResult * hashResult, HashResultNode ** resultList) {
    keyValuePair_(hashResult, resultList);
    bubblesort_(resultList);    
}

void printList(HashResultNode * resultList) {
    HashResultNode * temp = resultList;
    while(temp != NULL) {
        printf("\n%s\n", temp->key);
        temp = temp->next;
    }
}
