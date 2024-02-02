#include <cs50.h>
#include <stdio.h>

int main(void){
    int height;
    do{
      height = get_int("Height: \n");
    }while (height<1 || height>8);
    for(int i=1; i<=height; i++){
      for(int j=1; j<=height; j++){
        if(i+j<=height) printf(" ");
        else printf("#");
      }
      printf("  ");
      for(int j=1; j<=height; j++){
        if(j<=i) printf("#");
      }
      printf("\n");
    }
    return 0;
}