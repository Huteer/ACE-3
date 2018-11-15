//
// Created by rositsa on 11/11/18.
//

#include "helpfunctions.h"


int binToDec12(char* array, struct reg* cpu){

    int count=0;
    int total=0;
    char* start = array + cpu->pc*16 + 4;

    while(count < 12){
        total *= 2;
        if(*start++ == '1'){
            total++;
        }
        count++;
    }
    return total;
}

int binToDec16(char* array, struct reg* cpu){

    int count=0;
    int total=0;
    char* first = array + cpu->mar*16;
    char* start = array + cpu->mar*16;

    while(count < 16){
        total *= 2;
        if(*start++ == '1'){
            total++;
        }
        count++;
    }

    if(*first == '1'){
        total = total - 65536;
    }

    return total;
}

char* decToBin(int x){

    char binary[17];
    char* first = binary;
    char* store = binary;
    int count = 0;

    while(count < 15){
        *store++ = '0';
        count++;
    }

    if(x > 0){
        while(x>0){
            if(x%2 == 1){
                *store-- = '1';
            }
            else if(x%2 == 0){
                *store-- = '0';
            }
            x=x/2;
        }
    }
    else if(x < 0){
        x = x + 65536;
        while(x>0){
            if(x%2 == 1){
                *store-- = '1';
            }
            else if(x%2 == 0){
                *store-- = '0';
            }
            x=x/2;
        }
    }

    *(binary + 16) = '\0';

    return first;

}
