#ifndef PROJECT_H 
#define PROJECT_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>
typedef struct Task{
    int id;
    char description[500];
    char titre[500];
    char deadline[500];
    bool    real;
    bool    final;
    bool    en_cours;
    int remaining_days;
}t_tache;

int iden = 0;
t_tache book[600];

#endif