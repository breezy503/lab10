#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Trie structure
struct Trie
{	
    struct Trie* children[26];
    int count;
};

// computes the number of occurances of the word
int numberOfOccurances(struct Trie *pTrie, char *word)
{
    struct Trie* alpha = pTrie;
    while (*word) 
    {
        int index = *word - 'a';
        if (!alpha->children[index]) 
        {
            return 0;
        }
        alpha = alpha->children[index];
        word++;
    }
    return alpha->count;
}

// deallocate the trie structure
struct Trie *deallocateTrie(struct Trie *pTrie)
{
    if (pTrie) 
    {
        for (int i = 0; i < 26; i++) 
        {
            if (pTrie->children[i]) 
            {
                deallocateTrie(pTrie->children[i]);
            }
        }
        free(pTrie);
        return NULL;
    }
    return pTrie;
}

// Initializes a trie structure
struct Trie *createTrie()
{
    struct Trie* node = malloc(sizeof(struct Trie));
    node->count = 0;
    for (int i = 0; i < 26; i++) 
    {
        node->children[i] = NULL;
    }
    return node;
}

// Inserts the word to the trie structure
void insert(struct Trie *pTrie, char *word)
{
    struct Trie* ins = pTrie;
    while (*word) 
    {
        int index = *word - 'a';
        if (!ins->children[index]) 
        {
            ins->children[index] = createTrie();
        }
        ins = ins->children[index];
        word++;
    }
    ins->count++;
}

// this function will return number of words in the dictionary,
// and read all the words in the dictionary to the structure words
int readDictionary(char *filename, char **pInWords)
{
    FILE* file = fopen(filename, "r");
    if (!file) 
    {
        printf("Error opening file\n");
        return 0;
    }

    int amnWords;
    fscanf(file, "%d", &amnWords);
    for (int i = 0; i < amnWords; i++) 
    {
        pInWords[i] = malloc(100 * sizeof(char));
        fscanf(file, "%s", pInWords[i]);
    }

    fclose(file);
    return amnWords;
}

int main(void)
{
	char *inWords[256];
	
	//read the number of the words in the dictionary
	int numWords = readDictionary("dictionary.txt", inWords);
	for (int i=0;i<numWords;++i)
	{
		printf("%s\n",inWords[i]);
	}
	
	struct Trie *pTrie = createTrie();
	for (int i=0;i<numWords;i++)
	{
		insert(pTrie, inWords[i]);
	}
	// parse lineby line, and insert each word to the trie data structure
	char *pWords[] = {"notaword", "ucf", "no", "note", "corg"};
	for (int i=0;i<5;i++)
	{
		printf("\t%s : %d\n", pWords[i], numberOfOccurances(pTrie, pWords[i]));
	}
	pTrie = deallocateTrie(pTrie);
	if (pTrie != NULL)
		printf("There is an error in this program\n");
	return 0;
}