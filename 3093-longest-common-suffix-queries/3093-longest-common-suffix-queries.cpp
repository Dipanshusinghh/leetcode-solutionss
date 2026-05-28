class Solution {
    struct TrieNode {
        int next[26];
        int shortestLength;
        int bestWordIndex;
        TrieNode() {
            fill(begin(next), end(next), -1);
            shortestLength = INT_MAX;
            bestWordIndex = INT_MAX;
        }
    };
public:
    vector<int> stringIndices(vector<string>& wordsContainer,
                              vector<string>& wordsQuery) {
        vector<TrieNode> trie;
        trie.push_back(TrieNode()); // root node
        // Build reverse trie
        for (int i = 0; i < wordsContainer.size(); i++) {
            string &word = wordsContainer[i];
            int wordLength = word.size();
            int node = 0;
            // Update root with best candidate
            updateBest(trie[node], wordLength, i);
            // Insert reversed word
            for (int j = wordLength - 1; j >= 0; j--) {
                int ch = word[j] - 'a';
                if (trie[node].next[ch] == -1) {
                    trie[node].next[ch] = trie.size();
                    trie.push_back(TrieNode());
                }
                node = trie[node].next[ch];
                updateBest(trie[node], wordLength, i);
            }
        }
        vector<int> answer;
        // Process queries
        for (string &query : wordsQuery) {
            int node = 0;
            // Traverse using reversed query
            for (int j = query.size() - 1; j >= 0; j--) {
                int ch = query[j] - 'a';
                if (trie[node].next[ch] == -1) {
                    break;
                }
                node = trie[node].next[ch];
            }
            answer.push_back(trie[node].bestWordIndex);
        }
        return answer;
                              }
private:
    void updateBest(TrieNode &node, int len, int index) {
        if (len < node.shortestLength) {
            node.shortestLength = len;
            node.bestWordIndex = index;
        }
        else if (len == node.shortestLength &&
                 index < node.bestWordIndex) {
            node.bestWordIndex = index;
        }
    }
};