#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <fstream>
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
        cout << "File is empty! Creating an empty compressed file." << '\n';
        ofstream emptyFile("tests/compressed.bin");
        return 0;
    }

    if (frequencies.size() == 1)
    {
        auto it = frequencies.begin();
        char dummy = (it->first == '\0') ? '\1' : '\0';
        frequencies[dummy] = 1;
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

    string compressedFile = "tests/compressed.bin";

    compressFile(testFile, compressedFile, frequencies, huffmanCodes);
    decompressFile(compressedFile, "tests/decompressed.txt");

    freeTree(root);
    return 0;
}