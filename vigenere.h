#ifndef VIGENERE_H_
#define VIGENERE_H_

#include <iostream>
#include <string>
#include <cctype>
#include <limits>
#include <fstream>
#include <algorithm>

#define SIZE 26

enum Mode {
  ENCRYPT,
  DECRYPT
};

void show_tabula_recta(char tabula_recta[SIZE][SIZE]);
std::string input_keyword(void);
Mode select_mode(const std::string* keyword_ptr);
void encrypt(std::ifstream& file, const std::string* keyword_ptr, char tabula_recta[SIZE][SIZE]);
void decrypt(std::ifstream& file, const std::string* keyword_ptr, char tabula_recta[SIZE][SIZE]);

#endif
