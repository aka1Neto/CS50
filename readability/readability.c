#include <cs50.h>
#include <stdio.h>
#include <string.h>

int count_sentences(string text, int lenght, int sentences);
int count_words(string text, int lenght, int words);
int count_letters(string text, int lenght, int letters);

int main(void){
    int sentences = 0;
    float words = 1.00;
    int letters = 0;
    string text = get_string("Text: ");
    int lenght = strlen(text);
    sentences = count_sentences(text, lenght, sentences);
    words = count_words(text, lenght, words);
    letters = count_letters(text, lenght, letters);
    float L = (letters/words) * 100;
    float S = (sentences/words) * 100;
    float index = 0.0588 * L - 0.296 * S - 15.8;
    if(index<1 ) printf("Before Grade 1\n");
    else if(index<16) printf("Grade %.0f\n", index);
    else printf("Grade 16+\n");
}
int count_sentences(string text, int lenght, int sentences){
    for(int i=0;i<lenght;i++){
        if(text[i]=='.'||text[i]=='?'||text[i]=='!'){
            sentences = sentences + 1;
        }
    }
    return sentences;
}

int count_words(string text, int lenght, int words){
    for(int i=0;i<lenght;i++){
        if(text[i]==' '){
            words = words + 1;
        }
    }
    return words;
}

int count_letters(string text, int lenght, int letters){
    for(int i=0; i<lenght; i++){
        if(text[i]>=65&&text[i]<=90){
            letters = letters + 1;
        }
        if(text[i]>=97&&text[i]<=122){
            letters = letters + 1;
        }
    }
    return letters;
}