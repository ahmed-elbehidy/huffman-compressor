#include <iostream>
#include "../include/Huffman.h"
#include <algorithm>
#include <vector>
#include <string>
#include <unordered_map>
#include <queue>
#include <fstream>
using namespace std;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string testFile = "tests/test.txt";
    unordered_map<char, int> frequencies = calculateFrequency(testFile);

    if (frequencies.empty()) 
    {
        cout << "Map is empty or file not found!" << '\n';
        return 1;
    }

    priority_queue<HuffmanNode*, vector<HuffmanNode*>, CompareNode> minHeap;

    for (auto pair : frequencies) 
    {
        HuffmanNode* newNode = new HuffmanNode(pair.first, pair.second);
        minHeap.push(newNode);
    }

    cout << "--- Min-Heap Contents (Sorted by lowest frequency) ---" << '\n';

    while (!minHeap.empty()) 
    {
        HuffmanNode* topNode = minHeap.top();

        if (topNode->data == '\n')
        {
            cout << "Character: '\\n' | Frequency: " << topNode->frequency << '\n';
        }
        else
        {
            cout << "Character: '" << topNode->data << "' | Frequency: " << topNode->frequency << '\n';
        }

        minHeap.pop();
    }

    return 0;
}