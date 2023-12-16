#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <cctype>
#include <algorithm>
#include <unordered_set>

using namespace std;

class Indices {
  public:
    unordered_map<int, unordered_map<int, unordered_set<int>>> indices;

    Indices() {
      indices = {};
    }

    void insert(int row, int column, int number) {
      if (indices.find(row) != indices.end()) {
        if (indices[row].find(column) != indices[row].end()) {
          indices[row][column].insert(number);
        } else {
          indices[row][column] = { number };
        }
      } else {
        indices[row] = { { column, { number } } };
      }
    }

    unordered_set<int> search(int row, int column) {
      if (indices.find(row) != indices.end() && indices[row].contains(column)) {
        return indices[row][column];
      }

      return {};
    }
};

int main() {
  ifstream inputFile("test-input3.txt");
  string line;
  string digits = "";
  int sum = 0;
  Indices *indices = new Indices();
  unordered_map<

  int row = 0;
  while (getline(inputFile, line)) {
    vector<int> digitIndices;

    for (int i = 0; i < line.length(); i++) {
      if (isdigit(line[i])) {
        digits += line[i];
        digitIndices.push_back(i);
      } else if (line[i] != '.') {
        // Process last number, if applicable.
        if (digits.length() > 0) {
          int number = stoi(digits);

          // Create map from surrounding indices to the number.
          for (int j = 0; j < digitIndices.size(); j++) {
            if (j == 0) {
              indices->insert(row, i - 1, number);
              indices->insert(row - 1, i - 1, number);
              indices->insert(row + 1, i - 1, number);
            }

            if (j == digitIndices.size() - 1) {
              indices->insert(row, i + 1, number);
              indices->insert(row - 1, i + 1, number);
              indices->insert(row + 1, i + 1, number);
            }

            indices->insert(row - 1, i, number);
            indices->insert(row + 1, i, number);
          }
        }

        specialCharacters->insert(row, i, 0);

        // If these indices match any special character locations, add
        // the associated numbers to the sum.
        unordered_set<int> numbers = indices->search(row, i);
        if (numbers.size() > 0) {
          for (auto n = numbers.begin(); n != numbers.end(); n++) {
            sum += *n;
          }
        }
      }
    }

    row++;
  }

  inputFile.close();

  cout << sum << endl;

  return 0;
}
