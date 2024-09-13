#include <cs50.h>
#include <stdio.h>
#include <string.h>

int main(int argc, string argv[]){
    if(argv[1]==00 || argv[2]!=00){
        printf("Usage: ./substitution key\n");
        return 1;
    }
    string key, text;
    char upperkey[26], lowerkey[26];
    key = argv[1];
    int size;
    size = strlen(key);
    if (size!=26){
        printf("Key must contain 26 characters.\n");
        return 1;
    }
    for(int i=0; i<size; i++){
        if(key[i]>=65 && key[i]<=90){
            lowerkey[i] = key[i]+32;
            upperkey[i] = key[i];
        }
        else if(key[i]>=97 && key[i]<=122){
            lowerkey[i] = key[i];
            upperkey[i] = key[i]-32;
        }
        else return 1;
    }
    for(int i=0; i<size-1; i++){
        for(int j=1; j<size; j++){
            if(i!=j){
                if(key[i]==key[j] || key[i]==key[j]+32){
                    return 1;
                }
            }
        }
    }
    text = get_string("plaintext: ");
    int size_text = strlen(text);
    for(int i=0; i<size_text; i++){
        if(text[i]>=65 && text[i]<=90){
            text[i] = upperkey[text[i]-65];
        }
        else if(text[i]>=97 && text[i]<=122){
            text[i] = lowerkey[text[i]-97];
        }
    }
    printf("ciphertext: %s\n", text);
}