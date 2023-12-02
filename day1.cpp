#include <iostream>
#include <fstream>
#include <string>

int main() {
  std::ifstream inputFile("input.txt");
  std::string line;
  int digit;
  int lineNumber;
  int sum;

  while (std::getline(inputFile, line)) {
    lineNumber = -1;

    for (auto it = line.begin(); it != line.end(); it++) {
      if (std::isdigit(*it)) {
        digit = *it - '0';
        
        if (lineNumber < 0) {
          lineNumber = 10 * digit;
        }
      }
    }

    if (lineNumber < 0) {
      lineNumber = 10 * digit + digit;
    } else {
      lineNumber += digit;
    }

    sum += lineNumber;
  }

  inputFile.close();

  std::cout << sum << std::endl;

  return 0;
}
