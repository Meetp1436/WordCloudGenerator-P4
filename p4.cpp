#include <iostream>
using namespace std;
#include<string.h>

class TrieNode
{
public:
    bool hasEnded;
    int MinheapIndex;
    int frequency;
    TrieNode *childrenArray[26];

    TrieNode()
    {
        MinheapIndex = -1;
        for (int i = 0; i < 26; i++)
        {
            childrenArray[i] = NULL;
        }
        hasEnded = false;
    }
};

class MinHeapNode
{
public:
    TrieNode *root;
    int freq;
    char *word;
    MinHeapNode()
    {
        root = nullptr;
        freq = 0;
        word = nullptr;
    }
};

class MinHeap
{
public:
    MinHeapNode *toStore;
    int size; // number of slots filled in minheap
    int minHeapCapacity;

    MinHeap(int cap)
    {   
        minHeapCapacity = cap;
        toStore = new MinHeapNode[minHeapCapacity];
        size = 0;
    }
};

void swapMinheapNodes(MinHeapNode *x, MinHeapNode *y)
{
    MinHeapNode temp = *x;
    *x = *y;
    *y = temp;
}

void minHeapify(MinHeap *minheap, int index)
{
    int smallest = index;
    int left = 2 * index + 1;
    int right = 2 * index + 2;

    if (left < minheap->size && minheap->toStore[left].freq < minheap->toStore[smallest].freq)
    {
        smallest = left;
    }

    if (right < minheap->size && minheap->toStore[right].freq < minheap->toStore[smallest].freq)
    {
        smallest = right;
    }

    if (smallest != index)
    {
        minheap->toStore[smallest].root->MinheapIndex = index;
        minheap->toStore[index].root->MinheapIndex = smallest;
    }

    swapMinheapNodes(&minheap->toStore[smallest], &minheap->toStore[index]);

    minHeapify(minheap, smallest);
}

// a function to create minheap
void buildingMinHeap(MinHeap *minHeap)
{
    int n = minHeap->size - 1;

    for (int i = (n - 1) / 2; i >= 0; i--)
    {
        minHeapify(minHeap, i);
    }
}

void insertInMinHeap(MinHeap *minheap, TrieNode **root, char *word)
{

    // word present in the heap so updating the frequency of the occurance of the word
    if ((*root)->MinheapIndex != -1)
    {
        (minheap->toStore[(*root)->MinheapIndex].freq)++;

        // checking the same for others!
        minHeapify(minheap, (*root)->MinheapIndex);
    }


    // if word is not present in the minheap

    // checking whether the minheap is empty or not
    else if (minheap->size < minheap->minHeapCapacity)
    {
        int count = minheap->size;

        minheap->toStore[count].freq = (*root)->frequency;

        minheap->toStore[count].word = new char[strlen(word) + 1];

        strcpy(minheap->toStore[count].word, word);

        minheap->toStore[count].root = *root;

        (*root)->MinheapIndex = minheap->size;

        ++(minheap->size);

        buildingMinHeap(minheap);
    }

    // case when minheap would be full and word is not present in it.
}

void insertInBothTrieAndHeap(char* word, TrieNode** root, MinHeap* minHeap){

    //base case
    if(*root == NULL){
        *root = new TrieNode();
    }

    TrieNode* current = *root;

    for (char* ch = word; *ch != '\0'; ch++) {

        int index = tolower(*ch) - 'a';

        if (current->childrenArray[index] == NULL){

        current->childrenArray[index] = new TrieNode();
        current = current->childrenArray[index];

        }
           
    }

    // Word processing is complete, update the Trie node
    if (current->hasEnded)
        (current->frequency)++;

    else {

        current->hasEnded = 1;
        current->frequency = 1;
    }

    // Insert into Min Heap also
    insertInMinHeap(minHeap, &current, word);
}


void displayMinHeap(MinHeap* minHeap)
{
    for (int i = 0; i < minHeap->size; i++) {
       cout << minHeap->toStore[i].word << " -> " << minHeap->toStore[i].freq << endl;
    }
}
 
void printKMostFreq(FILE* fp, int k)
{
    // Create a Min Heap of Size k
    MinHeap* minHeap = new MinHeap(k);
 
    // Create an empty Trie
    TrieNode* root = NULL;
 
    // A buffer to store one word at a time
    char buffer[50];
 
    while (fscanf(fp, "%s", buffer) != EOF)
        insertInBothTrieAndHeap(buffer, &root, minHeap);

    displayMinHeap(minHeap);
}

int main(void)
{

    FILE* fileName = fopen("input.txt", "r");

    if (fileName == NULL) {
        cout << "File doesn't exist enter valid name" << endl;
    } 
    else {
        printKMostFreq(fileName, 10);
        fclose(fileName);
    }
}