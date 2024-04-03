#include <iostream>
using namespace std;

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
        toStore = new MinHeapNode[minHeapCapacity];
        size = 0;
        minHeapCapacity = cap;
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
}

int main(void)
{
}