#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include "../include/Huffman.h"
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

    HuffmanNode* root = buildHuffmanTree(minHeap);

    unordered_map<char, string> huffmanCodes;
    generateCodes(root, "", huffmanCodes);

    cout << "--- Huffman Codes ---" << '\n';
    for (auto pair : huffmanCodes)
    {
        if (pair.first == '\n')
        {
            cout << "Character: '\\n' | Code: " << pair.second << '\n';
        }
        else
        {
            cout << "Character: '" << pair.first << "' | Code: " << pair.second << '\n';
        }
    }

    return 0;
}