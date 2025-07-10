#ifndef VIGENERE_H_
#define VIGENERE_H_

#include <iostream>
#include <string>
#include <cctype>
#include <limits>
#include <fstream>
#include <algorithm>
#include <vector>

constexpr size_t SIZE = 26;

enum Mode {
  ENCRYPT,
  DECRYPT
};

void show_tabula_recta(const char tabula_recta[SIZE][SIZE]);
std::string input_keyword(void);
Mode select_mode(const std::string& keyword_ptr);
void encrypt(std::ifstream& file, const std::string& keyword, const char tabula_recta[SIZE][SIZE]);
void decrypt(std::ifstream& file, const std::string& keyword, const char tabula_recta[SIZE][SIZE]);

#endif /* VIGENERE_H_ */
