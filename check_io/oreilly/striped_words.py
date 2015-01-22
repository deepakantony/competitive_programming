VOWELS = "AEIOUY"
CONSONANTS = "BCDFGHJKLMNPQRSTVWXZ"

def is_word(word):
    word = word.strip().upper()
    if not word.isalpha() or len(word) == 1: return False
    for i,c in enumerate(word):
        if (i+1) < len(word):
            if word[i] in VOWELS and word[i+1] in VOWELS:
                return False
            if word[i] in CONSONANTS and word[i+1] in CONSONANTS:
                return False
    return True

from string import *
def checkio(text):
    for p in punctuation:
        text = text.replace(p,' ')
    return sum(map(is_word, text.split()))

#These "asserts" using only for self-checking and not necessary for auto-testing
if __name__ == '__main__':
    assert checkio("My name is ...") == 3, "All words are striped"
    assert checkio("Hello world") == 0, "No one"
    assert checkio("A quantity of striped words.") == 1, "Only of"
    assert checkio("Dog,cat,mouse,bird.Human.") == 3, "Dog, cat and human"
