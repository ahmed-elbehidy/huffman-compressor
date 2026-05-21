#ifndef HUFFMAN_H
#define HUFFMAN_H

#include <unordered_map>
#include <string>
#include <queue>
#include <vector>

struct HuffmanNode 
{
    char data;
    int frequency;
    HuffmanNode* left;
    HuffmanNode* right;

    HuffmanNode(char d, int f) : data(d), frequency(f), left(nullptr), right(nullptr) {}
};


struct CompareNode 
{
    bool operator()(HuffmanNode* const& n1, HuffmanNode* const& n2) 
    {
        return n1->frequency > n2->frequency;
    }
};

std::unordered_map<char, int> calculateFrequency(const std::string& filePath);

HuffmanNode* buildHuffmanTree(std::priority_queue<HuffmanNode*, std::vector<HuffmanNode*>, CompareNode>& minHeap);

void generateCodes(HuffmanNode* root, std::string code, std::unordered_map<char, std::string>& huffmanCodes);

#endif