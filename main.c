#include <stdio.h>
#include <stdlib.h>
#include "jogo.h"
#include <time.h>

int main(){
    srand(time(NULL));
    int x;
    for(int i=0;i<10;i++){
        printf("você girou o dado e saiu: %i\n", dado());
    }
    return 0;
}
