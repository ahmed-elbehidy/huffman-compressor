#include "../include/Huffman.h"
#include <fstream>
#include <iostream>

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