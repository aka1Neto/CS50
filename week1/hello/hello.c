#include <stdio.h>
#include <cs50.h>

int main(void){
    //gets the user's name
    string name = get_string("What is your name?\n");
    //prints hello with the name of the user
    printf("Hello, %s!\n", name);
}