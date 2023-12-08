#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>

using namespace std;

class TrieNode {
  public:
    bool isEndOfString;
    TrieNode *children[26];

    TrieNode() {
      isEndOfString = false;
      for (int i = 0; i < 26; i++) children[i] = NULL;
    }
};

class Trie {
  public:
    TrieNode *root;

    Trie() {
      root = new TrieNode();
    }

    void insert(string s) {
      TrieNode *pointer = root;

      for (int i = 0; i < s.length(); i++) {
        int index = s[i]  - 'a';

        if (!pointer->children[index]) {
          pointer->children[index] = new TrieNode();
        }

        pointer = pointer->children[index];
      }

      pointer->isEndOfString = true;
    }

    string search(string s) {
      string match = "";
      TrieNode *pointer = root;

      for (int i = 0; i < s.length(); i++) {
        int index = s[i] - 'a';

        if (!pointer->children[index]) {
          return match;
        }

        if (pointer->children[index]->isEndOfString) {
          match = s.substr(0, i + 1);
        }

        pointer = pointer->children[index];
      }

      return match;
    }
};

int main() {
  ifstream inputFile("input1.txt");
  string line;
  int sum = 0;

  unordered_map<string, int> numbers = {
    { "one", 1 },
    { "two", 2 },
    { "three", 3 },
    { "four", 4 },
    { "five", 5 },
    { "six", 6 },
    { "seven", 7 },
    { "eight", 8 },
    { "nine", 9 },
  };

  Trie *trie = new Trie();
  for (auto it = numbers.begin(); it != numbers.end(); it++) {
    trie->insert(it->first);
  }

  while (getline(inputFile, line)) {
    int digit;
    int firstDigit = -1;
    int secondDigit = -1;

    for (int i = 0; i < line.length(); i++) {
      if (isdigit(line[i])) {
        digit = line[i] - '0';

        if (firstDigit < 0) {
          firstDigit = digit;
          secondDigit = digit;
        } else {
          secondDigit = digit;
        }
      } else {
        string word = trie->search(line.substr(i, line.length()));

        if (word.length() > 0) {
          digit = numbers[word];

          if (firstDigit < 0) {
            firstDigit = digit;
            secondDigit = digit;
          } else {
            secondDigit = digit;
          }
        }
      }
    }

    if (firstDigit > -1 && secondDigit > -1) {
      sum += 10 * firstDigit + secondDigit;
    }
  }

  inputFile.close();

  cout << sum << endl;

  return 0;
}
