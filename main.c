#include <stdio.h>  //Input/output
#include <stdlib.h> //System and rand
#include <time.h>   //For rand seed
#include "sleep.h"  //Maybe for updates

#ifdef _WIN32
#include <windows.h>
#endif // _WIN32

int score;  //SCOOOORE
int matrix[4][4];   //The digits

void refresh(); //Shows the numbers and put a random number
void refreshColor();
void color(int color);
void pause();   //Like 'system("pause")'. Also works on linux(I think...)
int action();  //Moves the numbers
void randomDigit(); //Puts a random digit in the matrix

//Moving
void up();
void down();
void left();
void right();
void devMode(); //Cheating :3

int random(int max);    //Random number from 0 to max

int main()
{
    score = 0;

    printf("Controls:\n");
    printf("1) W - UP\n");
    printf("2) S - DOWN\n");
    printf("3) A - LEFT\n");
    printf("4) D - RIGHT\n");

    pause();
    printf("\n\n");

    randomDigit();
    refresh();

    //Main loop
    for(;;){
        if(action())
            refresh();
    }

    return 0;
}

void refresh(){
    int i, k;

    randomDigit();  //Put a number

    //Clearing
    #ifdef __linux__
        system("clear");
    #else
        system("cls");
    #endif // __linux__

    //Printing
    for(i = 0; i < 4; i++){
        for(k = 0; k < 4; k++){
            color(matrix[i][k]);
            printf("%d     ", matrix[i][k]);
            refreshColor();
        }
        printf("\n");
    }
    printf("\nScore: %d\n", score);
}

void refreshColor(){
    #ifdef _WIN32
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x07);
    #else
    printf("[0m");
    #endif // _WIN32
}

void color(int color){
    #ifdef _WIN32
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);

    switch(color){
    case 0: SetConsoleTextAttribute(handle, 0xf0); break;
    case 2: SetConsoleTextAttribute(handle, 0x70); break;
    case 4: SetConsoleTextAttribute(handle, 0x60); break;
    case 8: SetConsoleTextAttribute(handle, 0x40); break;
    case 16: SetConsoleTextAttribute(handle, 0xc0); break;
    case 32: SetConsoleTextAttribute(handle, 0xe0); break;
    case 64: SetConsoleTextAttribute(handle, 0x50); break;
    case 128: SetConsoleTextAttribute(handle, 0x10); break;
    case 256: SetConsoleTextAttribute(handle, 0x30); break;
    case 512: SetConsoleTextAttribute(handle, 0xb0); break;
    case 1024: SetConsoleTextAttribute(handle, 0x7f); break;
    case 2048: SetConsoleTextAttribute(handle, 0x6f); break;
    case 2050: SetConsoleTextAttribute(handle, 0x4f); break;
    default: system("color"); break;
    }

    #else
    #ifdef __linux__
    switch(color){
    case 0: printf("[30;47m"); break;
    case 2: printf("[47m"); break;
    case 4: printf("[43m"); break;
    case 8: printf("[41m"); break;
    case 16: printf("[45m"); break;
    case 32: printf("[45;1m"); break;
    case 64: printf("[41;1m"); break;
    case 128: printf("[43m"); break;
    case 256: printf("[43;1m");break;
    case 512: printf("[42m"); break;
    case 1024: printf("[42;1m"); break;
    case 2048: printf("[44m"); break;
    case 2050: printf("[46;1m"); break;
    default: printf("[0m"); break;
    }
    #endif // __linux__

    #endif // _WIN32

}

void pause(){
    #ifdef __linux__
        system("read -n1 -r -p \"Press any key to continue...\"");
    #else
        system("pause");
    #endif
}

int action(){
    char c;

    c = fgetc(stdin);

    if(c == 'w' || c == 'W')
        up();
    else if(c == 's' || c == 'S')
        down();
    else if(c == 'a' || c == 'A')
        left();
    else if(c == 'd' || c == 'D')
        right();
    else if(c == 'v' || c == 'V')
        devMode();
    else
        return 0;

    return 1;
}

void randomDigit(){
    int x, y;
    do{
        x = random(15);
        //y = random(4);
    }while(matrix[x / 4][x % 4] > 0);

    //2 or 4?
    if(random(2) == 1)
        matrix[x / 4][x % 4]  = 2;
    else
        matrix[x / 4][x % 4] = 4;
}

int random(int max){
    srand(time(0));
    return rand() % (max + 1);
}

void up(){
    int i, j, k;

    do{
        j = 0;
        for(k = 0; k < 4; k++){ //Coloana
            for(i = 0; i < 3; i++){ //Linie
                if(matrix[i][k] == matrix[i + 1][k] && matrix[i][k] != 0){
                    matrix[i][k] = matrix[i][k] * 2;
                    matrix[i + 1][k] = 0;
                    score += matrix[i][k];
                    j = 1;
                }
                else if(((matrix[i][k] == 2048 && matrix[i][k] == 2) || (matrix[i][k] == 2 && matrix[i][k] == 2048))){
                    matrix[i][k] = 2050;
                    matrix[i + 1][k] = 0;
                    score += 99;
                    printf("You are smart! You won!\n");
                    pause();
                    j = 1;
                }
                if(matrix[i][k] == 0 && matrix[i + 1][k]){
                    matrix[i][k] = matrix[i + 1][k];
                    matrix[i + 1][k] = 0;
                    j = 1;
                }
            }
        }
    }while(j == 1);
}

void down(){
    int i, j, k;

    do{
        j = 0;
        for(k = 0; k < 4; k++){
            for(i = 3; i > 0; i--){
                if(matrix[i][k] == matrix[i - 1][k] && matrix[i][k] != 0){
                    matrix[i][k] = matrix[i][k] * 2;
                    matrix[i - 1][k] = 0;
                    score += matrix[i][k];
                    j = 1;
                }
                else if((matrix[i][k] == 2048 && matrix[i - 1][k] == 2) || (matrix[i][k] == 2 && matrix[i - 1][k] == 2048)){
                    matrix[i][k] = 2050;
                    matrix[i + 1][k] = 0;
                    score += 99;
                    printf("You are smart! You win!\n");
                    pause();
                    j = 1;
                }
                if(matrix[i][k] == 0 && matrix[i - 1][k] != 0){
                    matrix[i][k] = matrix[i - 1][k];
                    matrix[i - 1][k] = 0;
                    j = 1;
                }
            }
        }
    }while(j == 1);
}

void left(){
    int i, j, k;

    do{
        j = 0;
        for(i = 0; i < 4; i++){
            for(k = 0; k < 3; k++){
                if(matrix[i][k] == matrix[i][k + 1] && matrix[i][k] != 0){
                    matrix[i][k] = matrix[i][k] * 2;
                    matrix[i][k + 1] = 0;
                    score += matrix[i][k];
                    j = 1;
                }
                else if((matrix[i][k] == 2048 && matrix[i][k + 1] == 2) || (matrix[i][k] == 2 && matrix[i][k + 1] == 2048)){
                    matrix[i][k] = 2050;
                    matrix[i][k + 1] = 0;
                    score += 99;
                    printf("You are smart! You win!\n");
                    pause();
                    j = 1;
                }
                if(matrix[i][k] == 0 && matrix[i][k + 1] != 0){
                    matrix[i][k] = matrix[i][k + 1];
                    matrix[i][k + 1] = 0;
                    j = 1;
                }
            }
        }
    }while(j == 1);
}

void right(){
    int i, j, k;

    do{
        j = 0;
        for(i = 0; i < 4; i++){
            for(k = 3; k > 0; k--){
                if(matrix[i][k] == matrix[i][k - 1] && matrix[i][k] != 0){
                    matrix[i][k] = matrix[i][k] * 2;
                    matrix[i][k - 1] = 0;
                    score += matrix[i][k];
                    j = 1;
                }
                else if((matrix[i][k] == 2048 && matrix[i][k - 1] == 2) || (matrix[i][k] == 2 && matrix[i][k - 1] == 2048)){
                    matrix[i][k] = 2050;
                    matrix[i][k - 1] = 0;
                    score += 99;
                    printf("You are smart! You win!\n");
                    pause();
                    j = 1;
                }
                if(matrix[i][k] == 0 && matrix[i][k - 1] != 0){
                    matrix[i][k] = matrix[i][k - 1];
                    matrix[i][k - 1] = 0;
                    j = 1;
                }
            }
        }
    }while(j == 1);
}

void devMode(){
    int i, j;

    for(i = 0; i < 4; i++)
        for(j = 0; j < 4; j++)
        matrix[i][j] = 0;

    matrix[0][0] = 2048;
    matrix[1][0] = 2;
    matrix[0][1] = 2;
}
