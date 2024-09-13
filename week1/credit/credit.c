#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>

int invalid();
int count(long card, int numbers);
void check_numbers(int numbers);
void check_luhn(int numbers, int digits[]);
void check_brand(int numbers, int digits[]);

int main(void){
    int numbers=1;
    long card, aux;
    card = get_long("Number: ");
    numbers = count(card,numbers);
    check_numbers(numbers);
    aux = card;
    int digits[numbers];
    for(int i=numbers; i>0; i--){
        digits[i] = aux%10;
        aux = aux / 10;
    }
    check_luhn(numbers,digits);
    check_brand(numbers,digits);
    return 0;
}

int invalid(){
    printf("INVALID\n");
    exit(0);
}

int count(long card, int numbers){
     while(card>=10){
        card = card/10;
        numbers++;
    }
    return numbers;
}

void check_numbers(int numbers){
    if(numbers<13||numbers>16) invalid();
    else if(numbers==14) invalid();
}

void check_luhn(int numbers, int digits[]){
    int mul=0, t1=0, t2=0, total=0;
    if(numbers==16){
        for(int i=1; i<=numbers; i++){
            if(i%2!=0){
                mul = digits[i]*2;
                if(mul>=10) t1 = t1 + ((mul/10) + (mul%10));
                else t1 = t1 + mul;
            }
            else t2 = t2 + digits[i];
        }
        total = t1 + t2;
        if(total%10!=0) invalid();
    }
    else{
        for(int i=1; i<=numbers; i++){
            if(i%2==0){
                mul = digits[i]*2;
                if(mul>=10) t1 = t1 + ((mul/10) + (mul%10));
                else t1 = t1 + mul;
            }
            else t2 = t2 + digits[i];
        }
        printf("%d %d\n", t1, t2);
        total = t1 + t2;
        if(total%10!=0) invalid();
    }
}

void check_brand(int numbers, int digits[]){
    if(numbers==15 && digits[1]==3){
        if(digits[2]==4||digits[2]==7) printf("AMEX\n");
        else invalid();
    }
    else if(numbers==13||numbers==16){
        if(digits[1]==4) printf("VISA\n");
        else if(digits[1]==5){
            if(digits[2]<6 && digits[2]!=0) printf("MASTERCARD\n");
            else invalid();
        }
        else invalid();
    }
    else invalid();
}