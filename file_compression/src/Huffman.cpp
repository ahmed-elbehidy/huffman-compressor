#include "../include/Huffman.h"
#include <fstream>
#include <iostream>
#include <queue>

std::unordered_map<char, int> calculateFrequency(const std::string& filePath)
{
    std::unordered_map<char, int> freqMap;
    std::ifstream inFile(filePath);

    if (!inFile)
    {
        std::cerr << "Error opening file: " << filePath << '\n';
        return freqMap;
    }

    char ch;
    while (inFile.get(ch))
    {
        freqMap[ch]++;
    }
    inFile.close();
    return freqMap;
}

HuffmanNode* buildHuffmanTree(std::priority_queue<HuffmanNode*, std::vector<HuffmanNode*>, CompareNode>& minHeap) 
{
    while (minHeap.size() > 1) 
    {
        HuffmanNode* left = minHeap.top();
        minHeap.pop();

        HuffmanNode* right = minHeap.top();
        minHeap.pop();

        HuffmanNode* parent = new HuffmanNode('\0', left->frequency + right->frequency);

        parent->left = left;
        parent->right = right;

        minHeap.push(parent);
    }

    return minHeap.top();
}

void generateCodes(HuffmanNode* root, std::string code, std::unordered_map<char, std::string>& huffmanCodes)
{
    if (!root) return;

    if (root->data != '\0')
    {
        huffmanCodes[root->data] = code;
    }

    generateCodes(root->left, code + "0", huffmanCodes);
    generateCodes(root->right, code + "1", huffmanCodes);
}