#include <stdio.h>
#include <stdlib.h>
#include "get.h"
#include "set.h"
#define MENU 255
#define SET 1
#define GET 2
int main(){
    int set_number = SET;
    int get_number = GET;
    int choose = 255;
    do{
        switch (choose)
        {
            case SET:
                set();
                choose = MENU;
            break;
            case GET:
                get();
                choose = MENU;
            break;
            default:
                printf("%d para registrar compra\n", set_number);
                printf("%d para mostrar faturamento\n", get_number);
                printf("0 para sair\n");
                if(scanf("%d", &choose) == -1){
                    exit(1);
                }
            break;
        }
    }while (choose != 0);
    
}