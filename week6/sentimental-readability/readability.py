def main():
    text = input("Text: ");
    lenght = len(text);
    sentences = count_sentences(text, lenght);
    words = count_words(text, lenght);
    letters = count_letters(text, lenght);
    L = (letters/words) * 100;
    S = (sentences/words) * 100;
    index = 0.0588 * L - 0.296 * S - 15.8;
    if(index < 1):
        print("Before Grade 1");
    elif(index < 16):
        print(f"Grade {index:.0f}");
    else:
        print("Grade 16+\n");

def count_sentences(text, lenght):
    sentences = 0;
    for i in range(lenght):
        if(text[i]=='.' or text[i]=='?' or text[i]=='!'):
            sentences = sentences + 1;

    return sentences;


def count_words(text, lenght):
    words = 1;
    for i in range(lenght):
        if(text[i]==' '):
            words = words + 1;

    return words;


def count_letters(text, lenght):
    letters = 0;
    for i in range(lenght):
        if(text[i].isalpha()):
            letters = letters + 1;

    return letters;

main();