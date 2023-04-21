#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define alphabetsize 26

struct Trie {
    int count;
    struct Trie *c[alphabetsize];
};

void insert(struct Trie **ppTrie, char *word) {
    struct Trie *pTrie = *ppTrie;
    if (pTrie == NULL) {
        pTrie = (struct Trie *)malloc(sizeof(struct Trie));
        if (pTrie == NULL) {
            printf("Memory allocation failed\n");
            exit(1);
        }
        pTrie->count = 0;
        for (int i = 0; i < alphabetsize; i++) {
            pTrie->c[i] = NULL;
        }
        *ppTrie = pTrie;
    }
    while (*word) {
        int index = *word - 'a';
        if (pTrie->c[index] == NULL) {
            pTrie->c[index] = (struct Trie *)malloc(sizeof(struct Trie));
            if (pTrie->c[index] == NULL) {
                printf("Memory allocation failed\n");
                exit(1);
            }
            pTrie->c[index]->count = 0;
            for (int i = 0; i < alphabetsize; i++) {
                pTrie->c[index]->c[i] = NULL;
            }
        }
        pTrie = pTrie->c[index];
        word++;
    }
    pTrie->count++;
}

int numberOfOccurrences(struct Trie *pTrie, char *word) {
    while (pTrie && *word) {
        int index = *word - 'a';
        pTrie = pTrie->c[index];
        word++;
    }
    if (pTrie == NULL || pTrie->count == 0) {
        return 0;
    } else 
        return pTrie->count;
    
}

struct Trie *deallocateTrie(struct Trie *pTrie) {
    if (pTrie != NULL) {
        for (int i = 0; i < alphabetsize; i++) {
            pTrie->c[i] = deallocateTrie(pTrie->c[i]);
        }
        free(pTrie);
        pTrie = NULL;
    }
    return pTrie;
}

int main(void) {
    struct Trie *trie = NULL;
    // read the number of the words in the dictionary
    // parse line by line, and insert each word to the trie data structure
    char *pWords[] = {"notaword", "ucf", "no", "note", "corg"};
    int n = sizeof(pWords) / sizeof(pWords[0]);
    for (int i = 0; i < n; i++) {
        insert(&trie, pWords[i]);
    }
    for (int i = 0; i < n; i++) {
        printf("\t%s : %d\n", pWords[i], numberOfOccurrences(trie, pWords[i]));
    }
    trie = deallocateTrie(trie);
    if (trie != NULL) {
        printf("There is an error in this program\n");
    }
    return 0;
}
