#include<bits/stdc++.h>
using namespace std;

class TrieNode {
public:
    char ch;
    int frequency;
    bool isTerminal;
    unordered_map<char, TrieNode*> children;

    TrieNode(char c) : ch(c), frequency(0), isTerminal(false) {}
};

static bool comparator(const pair<string, int> &a, const pair<string, int> &b){
    return a.second > b.second;
}

class Trie {
private:
    TrieNode* root;

    // Helper function to add words and update frequency
    void addWord(const string &word, int freq) {
        TrieNode* node = root;
        for (char ch : word) {
            if (node->children.find(ch) == node->children.end())
                node->children[ch] = new TrieNode(ch);
            node = node->children[ch];   // move the node
        }
        node->isTerminal = true;
        node->frequency += freq; // Add to frequency
    }

    // Helper function to perform DFS for finding suggestions
    void dfs(TrieNode* node, string &prefix, vector<pair<string, int>> &suggestions) {
        if (!node) return;
        if (node->isTerminal) 
            suggestions.push_back({prefix, node->frequency});

        for (auto &child : node->children) {
            prefix.push_back(child.first);
            dfs(child.second, prefix, suggestions);
            prefix.pop_back(); // Backtrack
        }
    }

public:
    Trie() { root = new TrieNode(' '); }

    // Function to insert a word with frequency
    void insert(const string &word, int freq = 1) {
        addWord(word, freq);
    }

    // Function to retrieve suggestions based on a given prefix
    vector<string> getAutocompleteSuggestions(const string &prefix) {
        TrieNode* node = root;
        vector<pair<string, int>> suggestions;
        string currentPrefix = prefix;

        // Traverse to the end of the prefix in the Trie
        for (char ch : prefix) {
            if (node->children.find(ch) == node->children.end())
                return {}; // If prefix not found, return empty list
            node = node->children[ch];
        }

        // Perform DFS from the end of the prefix node
        dfs(node, currentPrefix, suggestions);

        // Sort suggestions by frequency in descending order
        sort(suggestions.begin(), suggestions.end(), comparator);

        // Collect sorted results
        vector<string> result;
        for (auto &pair : suggestions)
            result.push_back(pair.first);

        return result;
    }
};

int main() {
    Trie trie;

    // Insert some words with frequency
    trie.insert("hello", 5);
    trie.insert("hell", 3);
    trie.insert("helicopter", 2);
    trie.insert("help", 8);
    trie.insert("hero", 6);
    trie.insert("heat", 4);
    trie.insert("heater", 7);

    string prefix;
    cout << "Enter a prefix to get autocomplete suggestions: ";
    cin >> prefix;

    // Get autocomplete suggestions
    vector<string> suggestions = trie.getAutocompleteSuggestions(prefix);
    
    if (suggestions.empty()) {
        cout << "No suggestions found for the prefix '" << prefix << "'\n";
    } else {
        cout << "Suggestions:\n";
        for (const string &suggestion : suggestions) {
            cout << suggestion << "\n";
        }
    }

    return 0;
}
