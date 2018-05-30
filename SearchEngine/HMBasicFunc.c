//
//  HMBasicFunc.c
//  SearchEngine
//
//  Created by Shen guo on 5/25/18.
//  Copyright © 2018 Shen guo. All rights reserved.
//

#include "HMBasicFunc.h"

int hashFunc(char * key) {
    int keyIndex = 0;
    for(int i = 0; i < strlen(key); i++) {
        keyIndex += *(key + i);
    }
    keyIndex = keyIndex % SIZE;
    return keyIndex;
}

HashMapNode * searchKey_(HashMap* Hashmap, char * key) {
    int keyIndex = hashFunc(key);
    
    HashMapNode * temp = Hashmap->hashArr[keyIndex];
    while(temp != NULL) {
        if(!strcmp(temp->key, key)) {
            return temp;
        }
        temp = temp->next;
    }

    return NULL;
}

/**
 * When it is a new key.
 * @param keyIndex The number represent the word in the hashmap.
 * @param toInsert The
 */
void insertKeyNode_(HashMap * Hashmap, int keyIndex, HashMapNode * toInsert) {
    if(Hashmap->hashArr[keyIndex] == NULL) {
        Hashmap->hashArr[keyIndex] = toInsert;
        return;
    }
    HashMapNode * temp = Hashmap->hashArr[keyIndex];
    
    while(temp->next != NULL) {
        temp = temp->next;
    }
    temp->next = toInsert;
    return;
}

/**
 * When it is a duplicated key but new value.
 * @param searchedNode The node in the hashmap return by searchKey_().
 * @param fileName The file needed to be insert.
 */
void insertFileNode_(HashMapNode * searchedNode, char * fileName) {
    File * headFile = searchedNode->value;
    File * insteredFile = (File *) malloc (sizeof(File));
    insteredFile->fileName = (char *) malloc (sizeof(char) * (strlen(fileName) + 1));
    insteredFile->fileName = fileName;
    insteredFile->next = headFile;
    searchedNode->value = insteredFile;
}

/*
1)new key -> create and add a HashMap node to the hashmap.
2)duplicated key but new value -> create and add a FileName node to the HashMap node.
3)duplicated key and same value -> ignore.
 */
/**
 * @param key The word sanned by scanDir().
 * @param fileName The file contain the word.
 */
void set(HashMap* Hashmap, char * key, char * fileName) {
    int keyIndex = hashFunc(key);
    
    //1)new key -> create and add a HashMap node to the hashmap.
    if(searchKey_(Hashmap, key) == NULL) {
        File * value = (File *) malloc (sizeof(File));
        value->fileName = (char *) malloc (sizeof(char) * (strlen(fileName) + 1));
        strcpy(value->fileName, fileName);
        value->next = NULL;
        
        HashMapNode * toInsert = (HashMapNode *) malloc (sizeof(HashMapNode));
        toInsert->key = (char *) malloc (sizeof(char) * (strlen(key) + 1));
        strcpy(toInsert->key, key);
        toInsert->value = value;
        toInsert->next = NULL;

        insertKeyNode_(Hashmap, keyIndex, toInsert);
        return;
    }
    //2)duplicated key but new value -> create and add a FileName node to the HashMap node.
    HashMapNode * searchedNode = searchKey_(Hashmap, key);
    File * temp = searchedNode->value;
    
    while(temp != NULL) {
        if(strcmp(temp->fileName, fileName)) {
            temp = temp->next;
        } else { //duplicated key and same value -> ignoe
            return;
        }
    }
    insertFileNode_(searchedNode, fileName);
    return;
}

File * get(HashMap * Hashmap, char * key) {
    HashMapNode * getResult = searchKey_(Hashmap, key);
    if(getResult == NULL) {
        return NULL;
    }
    return getResult->value;
}

void clearHashMap(HashMap* Hashmap) {
    HashMapNode * temp;
    for(int i = 0; i < SIZE; i++) {
        temp = Hashmap->hashArr[i];
        HashMapNode * next;
        while (temp != NULL) {
            next = temp->next;
            free(temp);
            temp = next;
        }
        continue;
    }
}

void clearHashResult(HashResult * result) {
    HashResultNode * temp;
    for(int i = 0; i < SIZE; i++) {
        temp = result->hashResultArr[i];
        HashResultNode * next;
        while(temp != NULL) {
            next = temp->next;
            free(temp);
            temp = next;
        }
        continue;
    }
}
