#include <iostream>
#include <vector>
#include <queue>
#include <fstream>
#include "../include/Huffman.h"
using namespace std;

long long getFileSize(const string& filename)
{
    ifstream file(filename, ios::binary | ios::ate);
    if (!file) return 0;
    return file.tellg();
}

int main(int argc, char* argv[])
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    if (argc < 4)
    {
        cout << "Usage:\n";
        cout << "  Compress:   " << argv[0] << " -c <input_file> <output_file>\n";
        cout << "  Decompress: " << argv[0] << " -d <input_file> <output_file>\n";
        return 1;
    }
    string mode = argv[1];
    string inputFile = argv[2];
    string outputFile = argv[3];

    if (mode == "-c")
    {
        unordered_map<char, int> frequencies = calculateFrequency(inputFile);

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

        compressFile(inputFile, outputFile, frequencies, huffmanCodes);

        long long originalSize = getFileSize(inputFile);
        long long compressedSize = getFileSize(outputFile);

        cout << "\n--- Compression Metrics ---\n";
        cout << "Original Size:   " << originalSize << " bytes\n";
        cout << "Compressed Size: " << compressedSize << " bytes\n";

        if (originalSize > 0)
        {
            double saved = 100.0 - ((double)compressedSize / originalSize * 100.0);
            cout << "Space Saved:     " << saved << "%\n";
        }

        freeTree(root);
    }
    else if (mode == "-d")
    {
        decompressFile(inputFile, outputFile);
    }
    else
    {
        cout << "Error: Unknown command '" << mode << "'\n";
        return 1;
    }

    return 0;
}