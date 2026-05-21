#include "../include/Huffman.h"
#include <fstream>
#include <iostream>
#include <queue>

std::unordered_map<char, int> calculateFrequency(const std::string& filePath)
{
    std::unordered_map<char, int> freqMap;
    std::ifstream inFile(filePath, std::ios::binary);

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

void compressFile(const std::string& inputPath, const std::string& outputPath, const std::unordered_map<char, int>& frequencies, std::unordered_map<char, std::string>& huffmanCodes)
{
    std::ifstream inFile(inputPath, std::ios::binary);
    std::ofstream outFile(outputPath, std::ios::binary);

    if (!inFile || !outFile)
    {
        std::cerr << "Error opening files for compression.\n";
        return;
    }

    int mapSize = frequencies.size();
    outFile.write(reinterpret_cast<const char*>(&mapSize), sizeof(mapSize));

    for (auto pair : frequencies)
    {
        outFile.write(&pair.first, sizeof(pair.first));
        outFile.write(reinterpret_cast<const char*>(&pair.second), sizeof(pair.second));
    }

    unsigned char buffer = 0;
    int bitCount = 0;        
    char ch;

    while (inFile.get(ch))
    {
        std::string code = huffmanCodes[ch]; 

        for (char bit : code)
        {
            buffer = buffer << 1; 
            if (bit == '1')
            {
                buffer = buffer | 1; 
            }
            bitCount++;

            if (bitCount == 8)
            {
                outFile.write(reinterpret_cast<const char*>(&buffer), sizeof(buffer)); 
                buffer = 0;  
                bitCount = 0;
            }
        }
    }

    if (bitCount > 0)
    {
        buffer = buffer << (8 - bitCount);
        outFile.write(reinterpret_cast<const char*>(&buffer), sizeof(buffer));
    }

    inFile.close();
    outFile.close();
    std::cout << "--- File Compressed Successfully into: " << outputPath << " ---" << '\n';
}

void decompressFile(const std::string& inputPath, const std::string& outputPath)
{
    std::ifstream inFile(inputPath, std::ios::binary);
    std::ofstream outFile(outputPath);
    if (!inFile || !outFile)
    {
        std::cerr << "Error opening files for decompression.\n";
        return;
    }

    int mapSize = 0;
    inFile.read(reinterpret_cast<char*>(&mapSize), sizeof(mapSize));

    if (mapSize == 0) return;

    std::unordered_map<char, int> frequencies;
    for (int i = 0; i < mapSize; i++)
    {
        char ch;
        int freq;
        inFile.read(&ch, sizeof(ch));
        inFile.read(reinterpret_cast<char*>(&freq), sizeof(freq));
        frequencies[ch] = freq;
    }

    std::priority_queue<HuffmanNode*, std::vector<HuffmanNode*>, CompareNode> minHeap;
    for (auto pair : frequencies)
    {
        HuffmanNode* newNode = new HuffmanNode(pair.first, pair.second);
        minHeap.push(newNode);
    }

    HuffmanNode* root = buildHuffmanTree(minHeap);

    int totalChars = root->frequency;
    int decodedChars = 0;
    HuffmanNode* curr = root;
    unsigned char byte;

    while (inFile.read(reinterpret_cast<char*>(&byte), sizeof(byte)))
    {
        for (int i = 7; i >= 0; i--)
        {
            int bit = (byte >> i) & 1; 

            if (bit == 0) curr = curr->left;
            else curr = curr->right;

            if (curr->left == nullptr && curr->right == nullptr)
            {
                outFile.put(curr->data);
                decodedChars++;
                curr = root; 

                if (decodedChars == totalChars) break; 
            }
        }
        if (decodedChars == totalChars) break;
    }


    inFile.close();
    outFile.close();
    freeTree(root);
    std::cout << "--- File Decompressed Successfully into: " << outputPath << " ---" << '\n';
}

void freeTree(HuffmanNode* root) {
    if (!root) return;
    freeTree(root->left);
    freeTree(root->right);
    delete root;
}