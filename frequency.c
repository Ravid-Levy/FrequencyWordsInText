#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define Letters 26

struct Trie
{
	int EndWord;
	struct Trie *character[Letters];
	int wordcount;
};

struct Trie *getNewTrieNode()
{
	struct Trie *node = (struct Trie *)malloc(sizeof(struct Trie));
	node->EndWord = 0;
	for (int i = 0; i < Letters; i++)
		node->character[i] = NULL;
	return node;
}

void insert(struct Trie *head, char *str)
{
	struct Trie *curr = head;
	while (*str)
	{
		if (curr->character[*str - 'a'] == NULL)
			curr->character[*str - 'a'] = getNewTrieNode();
		curr = curr->character[*str - 'a'];
		str++;
	}

	curr->EndWord = 1;
	curr->wordcount += 1;
}

int haveChildren(struct Trie *curr)
{
	for (int i = 0; i < Letters; i++)
		if (curr->character[i])
			return 1;
	return 0;
}

void printTrie(struct Trie *curr, char *pos, int size, struct Trie *freecurr)
{
	if (curr->EndWord)
	{
		char *word = calloc(size + 1, sizeof(char));
		memcpy(word, pos, size);
		*(word + size) = '\0';
		if (freecurr != NULL)
		{
			free(freecurr);
		}
		if (word)
		{
			printf("%s %d\n", word, curr->wordcount);
			free(word);
		}
	}
	if (haveChildren(curr))
	{
		for (int i = 0; i < Letters; i++)
		{
			if (curr->character[i])
			{
				char *word = calloc(size + 1, sizeof(char));
				memcpy(word, pos, size);
				*(word + size) = 'a' + i;
				printTrie(curr->character[i], word, size + 1, curr->character[i - 1]);
			}
		}
	}
	return;
}

void printTrieR(struct Trie *curr, char *pos, int size, struct Trie *freecurr)
{
	if (curr->EndWord)
	{
		char *word = calloc(size + 1, sizeof(char));
		memcpy(word, pos, size);
		*(word + size) = '\0';
		if (freecurr != NULL)
		{
			free(freecurr);
		}
		if (word)
		{
			printf("%s %d\n", word, curr->wordcount);
			free(word);
		}
	}
	if (haveChildren(curr))
	{
		for (int i = Letters - 1; i >= 0; i--)
		{
			if (curr->character[i])
			{
				char *word = calloc(size + 1, sizeof(char));
				memcpy(word, pos, size);
				*(word + size) = 'a' + i;
				printTrieR(curr->character[i], word, size + 1, curr->character[i + 1]);
			}
		}
	}
	return;
}

void RemoveChars(char *s, char c)
{
    int writer = 0, reader = 0;

    while (s[reader])
    {
        if (s[reader]!=c)
        {
            s[writer++] = s[reader];
        }

        reader++;
    }

    s[writer]=0;
}

int main(int argc, char *argv[])
{
struct Trie *head = getNewTrieNode();
char *s;
while (scanf("%ms", &s) != EOF)
	{
		for(int i=0;i<strlen(s);i++)
		{
    if ((s[i] >= 'a' && s[i] <= 'z') || (s[i] >= 'A' &&s[i] <= 'Z'))
	{
		s[i] = tolower(s[i]);
	}
	else
	{
		    RemoveChars(s, s[i]);
	}
		}
		insert(head,s);
		s="";
	}
	char at[0];
	if (argc > 1)
	{
		printTrieR(head, at, sizeof(at), NULL);
		free(head);
		free(s);
	}
	else
	{
		printTrie(head, at, sizeof(at), NULL);
		free(head);
		free(s);
	}
	return 0;
}
