#include<stdio.h>

int squareadd(int i){

    int sum = 0;
    int input = i;
    int count = 1;
    while (count <= i){

        sum += input;
        count++;
    }

    return sum;
}


int squarebit(int i){
    int sum = 0;
    int multi = i;
    int bit = 1;
    while (bit <= i){

        if (bit & i){

            sum += multi;
        }

        multi -= bit;
        bit = bit << 1;
        multi = multi << 1;

    }

    return sum;
}


int main(){

    int count = 1;
    while (count <= 20){

        printf("%d  ", count);

        int x = squareadd(count);
        printf("%d", x);

        int y = squarebit(count);
        printf(" ");
        printf("%d\n", y);
        count++;
    }

    return 0;
}
