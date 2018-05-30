//
//  CreateHashMap.c
//  SearchEngine
//
//  Created by Shen guo on 5/25/18.
//  Copyright © 2018 Shen guo. All rights reserved.
//

#include <dirent.h>
#include "CreateHashMap.h"

char * convertChar_(char * word, int size) {
    for (int i = 0; i < size; i++) {
        if(word[i] >= 'A' && word[i] <= 'Z') {
            word[i] = word[i] + ' ';
        }
    }
        return word;
}

/*
 * Read the directory.
 * Scan each word to temp[] and put it into hashmap.
 */
void scanDir(char * dir, HashMap * hashMap) {
    struct dirent * entry;
    DIR * d = opendir(dir);
    
    if (d == 0) {
        perror("opendir");
        return;
    }
    
    char directory[] = "/Users/shenguo/Desktop/C_progamming/SearchEngine/SearchEngine/database/";
    while ((entry = readdir(d)) != 0) {
        if(entry->d_name[0] == '.') {
            continue;
        }
        char fileName[100];
        strcpy(fileName, directory);
        strcat(fileName, entry->d_name);
        
        FILE * fp = fopen(fileName, "r");
        char ch;
        char temp[SIZE];
        int i = 0;
        
        while((ch = getc(fp)) != EOF) {
            if(ch == ' ' || ch == '\n' || ch == '\t' || ch == ',' || ch == '.') {
                if(i == 0) {
                    continue;
                }
                temp[i] = '\0';
                set(hashMap, convertChar_(temp, i), entry->d_name);
                i = 0;
            } else {
                temp[i++] = ch;
            }
        }
        if(i != 0) {
            temp[i] = '\0';
            set(hashMap, convertChar_(temp, i), entry->d_name);
        }
        }
    closedir(d);
}
