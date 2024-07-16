//  github repository: https://github.com/omarhosny66/Prefix_Search_Performance.git

#include <iostream>
#include <unordered_set>
#include <vector>
#include <chrono>
#include <unordered_map>
#include <string>
#include <memory>
#include <boost/core/demangle.hpp> // For type name demangling

// Represents a node in a Trie data structure
struct TrieNode {
    // Map of child nodes, indexed by character
    std::unordered_map<char, std::unique_ptr<TrieNode>> children;
    // Flag indicating whether this node represents the end of a word
    bool is_end_of_word = false;
};

// Trie data structure for efficient prefix search
class Trie {
public:
    // Constructor initializes the root node
    Trie() : root(std::make_unique<TrieNode>()) {}

    // Inserts a word into the Trie
    void insert(const std::string& word) {
        // Start at the root node
        TrieNode* node = root.get();
        
        // Iterate over characters in the word
        for (char ch : word) {
            // If the character doesn't exist as a child, create a new node
            if (!node->children.count(ch)) node->children[ch] = std::make_unique<TrieNode>();
            // Move to the child node
            node = node->children[ch].get();
        }
        // Mark the end of the word
        node->is_end_of_word = true;
    }

    // Checks if a prefix exists in the Trie
    bool search(const std::string& prefix) const {
        // Start at the root node
        TrieNode* node = root.get();
        
        // Iterate over characters in the prefix
        for (char ch : prefix) {
            // If the character doesn't exist as a child, prefix not found
            if (!node->children.count(ch)) return false;
            // Move to the child node
            node = node->children.at(ch).get();
        }
        // Prefix found
        return true;
    }

private:
    // Root node of the Trie
    std::unique_ptr<TrieNode> root;
};

// Hash table for storing words
class HashTable {
public:
    // Inserts a word into the hash table
    void insert(const std::string& word) {
        words.insert(word);
    }

    // Checks if a prefix exists in the hash table
    bool search(const std::string& prefix) const {
        // Check if the prefix itself is in the hash table
        if (words.find(prefix) != words.end()) return true;
        // Iterate over words in the hash table
        for (const auto& word : words) {
            // If the word is shorter than the prefix, it can't be a match
            if (word.size() < prefix.size()) continue;
            // Check if the word starts with the prefix
            if (word.compare(0, prefix.size(), prefix) == 0) return true;
        }
        return false;  // Prefix not found
    }

private:
    // Set of words
    std::unordered_set<std::string> words;
};

// Tests the performance of a container for insertion and prefix search
template<class T>
void test(T& container, const std::vector<std::string>& words, const std::vector<std::string>& prefixes) {
    // Measure insertion time
    auto start = std::chrono::high_resolution_clock::now();
    for (const auto& word : words) {
        container.insert(word);
    }
    auto end = std::chrono::high_resolution_clock::now();
    std::cout << boost::core::demangle(typeid(container).name()) << " Insertion Time: ";
    std::cout << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() << " microseconds\n";

    // Measure prefix search time
    start = std::chrono::high_resolution_clock::now();
    for (const auto& prefix : prefixes) {
        container.search(prefix);
    }
    end = std::chrono::high_resolution_clock::now();
    std::cout << boost::core::demangle(typeid(container).name()) << " Prefix Search Time: ";
    std::cout << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() << " microseconds\n";
}

int main() {
    // Create a large set of words for testing
    const std::vector<std::string> words = {
        "the", "of", "and", "to", "in", "a", "is", "it", "that", "for",
        "with", "on", "as", "at", "by", "from", "up", "into", "or", "have",
        "be", "not", "are", "but", "this", "all", "their", "they", "an", "which",
        "one", "you", "had", "were", "when", "more", "so", "what", "said", "he",
        "she", "who", "will", "would", "about", "other", "there", "then", "time", "these",
        "like", "her", "can", "two", "just", "make", "people", "and", "some", "only",
        "my", "own", "over", "now", "do", "get", "out", "use", "day", "good",
        "go", "could", "see", "first", "come", "think", "know", "water", "than", "call",
        "his", "its", "way", "look", "new", "now", "too", "little", "use", "man",
        "thing", "find", "give", "tell", "work", "much", "home", "here", "said",
        "should", "like", "how", "our", "life", "very", "even", "back", "any", "after",
        "also", "many", "number", "part", "year", "different", "too", "place", "little", "world",
        "international", "organization", "computer", "science", "algorithm",
        "database", "programming", "language", "artificial", "intelligence",
        "javascript", "python", "java", "c++", "typescript",
    };

    // Create a set of prefixes for testing
    const std::vector<std::string> prefixes = {
        // Prefixes from words
        "the", "of", "and", "to", "in", "a", "is", "it", "that", "for",
        "with", "on", "as", "at", "by", "from", "up", "into", "or", "have",
        // Random prefixes
        "abc", "def", "ghi", "jkl", "mno", "pqr", "stu", "vwx", "yz",
        "123", "456", "789",
        // Longer prefixes
        "internationali", "organizationa", "computer", "science", "algorithm",
    };

    // Instantiate a Trie and a HashTable for testing
    Trie trie;
    HashTable hashtable;

    // Test the performance of the Trie with the given words and prefixes
    test(trie, words, prefixes);

    // Test the performance of the HashTable with the same words and prefixes
    test(hashtable, words, prefixes);

    return 0;
}
