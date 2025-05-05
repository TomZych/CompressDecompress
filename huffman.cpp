#include <iostream>
#include <unordered_map>
#include <queue>
#include <vector>
#include <string>
#include <iomanip>
using namespace std;

struct HuffmanNode{
    char ch;
    int freq;
    HuffmanNode *left, *right;

    HuffmanNode(char ch, int freq) : ch(ch) , freq(freq), left(nullptr), right(nullptr) {}
};

struct Compare{
    bool operator()(HuffmanNode* a, HuffmanNode* b){
        return a->freq > b->freq;
    }
};

void buildTable(HuffmanNode* root, string code, unordered_map<char,string>& huffmanCode){
    if (!root) return;
    if (!root->left && !root->right){
        huffmanCode[root->ch] = code;
    }
    buildTable(root->left, code + "0",huffmanCode);
    buildTable(root->right, code + "1",huffmanCode);
}

pair<string, unordered_map<char, string>> compress(const string& text){
    unordered_map<char, int> freq;
    for (char ch : text){
        freq[ch]++;
    }
    priority_queue<HuffmanNode*, vector<HuffmanNode*>, Compare> pq;
    for (auto pair : freq){
        pq.push(new HuffmanNode(pair.first,pair.second));
    }
    while (pq.size() > 1){
        HuffmanNode *left = pq.top(); pq.pop();
        HuffmanNode *right = pq.top(); pq.pop();

        HuffmanNode* merged = new HuffmanNode('\0', left->freq +right->freq);
        merged->left = left;
        merged->right = right;
        pq.push(merged);
    }
    HuffmanNode* root = pq.top();
    unordered_map<char,string> huffmanCode;
    buildTable(root, "", huffmanCode);

    string encoded = "";
    for (char ch : text){
        encoded += huffmanCode[ch];
    }
    return {encoded, huffmanCode};
}

string decompress(const string& encoded, const unordered_map<char, string>& huffmanCode){
    unordered_map<string, char> reverseHuffmanCode;
    for (auto pair : huffmanCode){
        reverseHuffmanCode[pair.second] = pair.first;
    }
    string decoded = "";
    string curr = "";
    for (char bit : encoded){
        curr += bit;
        if (reverseHuffmanCode.count(curr)){
            decoded += reverseHuffmanCode[curr];
            curr = "";
        }
    }
    return decoded;
}
int main() {
    string input;
    cout << "Enter a string: ";
    getline(cin, input);

    auto [encoded, huffmanCode] = compress(input);

    unordered_map<char,int> frequency;
    for (char ch : input){
        frequency[ch]++;
    }
    cout << left;
    cout << "\n" << setw(10) << "Symbol" 
         << setw(10) << "Frequency"
         << setw(10) << "Code" << endl;

    cout << setfill('-') << setw(30) << '-' <<endl;
    cout << setfill(' ');

    for (auto& pair : huffmanCode){
        string symbol = (pair.first == ' ') ? "space" : string(1, pair.first);
        cout << setw(10) << symbol
             << setw(10) << frequency[pair.first]
             << setw(10) << pair.second << endl;

    }

    cout << "Encoded string: " << encoded << endl;

    string decoded = decompress(encoded, huffmanCode);
    cout << "Decoded string: " << decoded << endl;
    return 0;
}
