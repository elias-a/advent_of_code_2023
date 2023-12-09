#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

vector<string> split(string s, string delimiter) {
  vector<string> v;
  int index = s.find(delimiter);

  while (index > -1) {
    v.push_back(s.substr(0, index));
    s.erase(0, index + 1);
    index = s.find(delimiter);
  }

  v.push_back(s);

  return v;
}

string trim(string s, string tokens = " ") {
  int startIndex = s.find_first_not_of(tokens);
  int endIndex = s.find_last_not_of(tokens);
  return s.substr(startIndex, 2 * s.length() - startIndex + endIndex + 1);
}

int main() {
  ifstream inputFile("input2.txt");
  string line;
  int sum = 0;

  unordered_map<string, int> limits = {
    { "blue", 14 },
    { "red", 12 },
    { "green", 13 },
  };

  while (getline(inputFile, line)) {
    int invalidGame = false;
    vector<string> data = split(line, ":");
    int gameId = stoi(trim(split(trim(data[0]), " ")[1]));
    vector<string> games = split(trim(data[1]), ";");

    for (auto game = games.begin(); game != games.end(); game++) {
      unordered_map<string, int> colors = {
        { "blue", 0 },
        { "red", 0 },
        { "green", 0 },
      };

      vector<string> draws = split(trim(*game), ",");
      for (auto draw = draws.begin(); draw != draws.end(); draw++) {
        vector<string> strings = split(trim(*draw), " ");
        int count = stoi(trim(strings[0]));
        string color = trim(strings[1]);

        colors[color] += count;
      }

      for (auto it = colors.begin(); it != colors.end(); it++) {
        if (it->second > limits[it->first]) {
          invalidGame = true;
        }
      }
    }

    if (!invalidGame) {
      sum += gameId;
    }
  }

  inputFile.close();

  cout << sum << endl;

  return 0;
}
