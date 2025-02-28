#include "vigenere.h"

void show_tabula_recta(char tabula_recta[SIZE][SIZE])
{
  for (int i = 0; i < SIZE; ++i) {
    for (int j = 0; j < SIZE; ++j)
      std::cout << tabula_recta[j][i] << ' ';
    std::cout << '\n';
  }
}

std::string input_keyword()
{
  std::string keyword;
  std::string input;
  std::getline(std::cin, input);
  for (char ch : input) {
    if (std::isalpha(ch))
      keyword += ch;
    else if (ch == ' ') {
      std::cout << "The keyword must be a no whitespaces string. Only the letters before the whitespace will be used.\n";
      break;
    } else {
      std::cout << "Non-alphabetical symbols cannot be used in the keyword. Only the letters before the symbol " << ch << " will be used.\n";
      break;
    }
  }

  return keyword;
}

Mode select_mode(const std::string* keyword_ptr)
{
  while (true) {
    char mode = getchar();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    if (mode == 'E' || mode == 'e') {
      std::cout << "ENCRYPTION MODE SELECTED. YOUR FILE WILL BE ENCIPHERED USING THE KEYWORD " << *keyword_ptr << std::endl;
      return ENCRYPT;
    }
    else if (mode == 'D' || mode == 'd') {
      std::cout << "DECRYPTION MODE SELECTED. YOUR FILE WILL BE DECIPHERED USING THE KEYWORD " << *keyword_ptr << std::endl;
      return DECRYPT;
    }
    else {
      std::cout << "Invalid input: press E or D to select the mode. No other modes exist.\n";
    }
  }
}

void encrypt(std::ifstream& file, const std::string* keyword_ptr, char tabula_recta[SIZE][SIZE])
{
  std::ofstream encrypted_file("encrypted.txt");
  if (!file) {
    std::cerr << "ERROR CREATING OUTPUT FILE!\n";
    return;
  }

  int* keyword = new int[keyword_ptr->length()];
  for (int i = 0; i < keyword_ptr->length(); ++i)
    *(keyword + i) = (*keyword_ptr)[i] - 'a';
  
  char plain_letter;
  int plain_number;
  char encrypted_letter;
  int operation = 0;
  
  while (file.get(plain_letter)) {
    if ((plain_letter >= 'a' && plain_letter <= 'z') || (plain_letter >= 'A' && plain_letter <= 'Z')) {
      if (plain_letter >= 'a' && plain_letter <= 'z') {
	plain_number = plain_letter - 'a';
      	encrypted_letter = tabula_recta[plain_number][*(keyword + operation)];
	encrypted_file.put(encrypted_letter);
      }
      else if (plain_letter >= 'A' && plain_letter <= 'Z') {
	plain_number = plain_letter - 'A';
      	encrypted_letter = tabula_recta[plain_number][*(keyword + operation)];
	encrypted_file.put(encrypted_letter + ('A' - 'a'));
      }

      ++operation;
      if (operation == keyword_ptr->length())
	operation = 0;
    }
    else {
      encrypted_file.put(plain_letter);
    }
  }

  delete[] keyword;
  encrypted_file.close();
  return;
}


void decrypt(std::ifstream& file, const std::string* keyword_ptr, char tabula_recta[SIZE][SIZE])
{
  std::ofstream decrypted_file("decrypted.txt");
  if (!file) {
    std::cerr << "ERROR CREATING OUTPUT FILE!\n";
    return;
  }

  int* keyword = new int[keyword_ptr->length()];
  for (int i = 0; i < keyword_ptr->length(); ++i)
    *(keyword + i) = (*keyword_ptr)[i] - 'a';
  
  char cipher_letter;
  int cipher_number;
  char decrypted_letter;
  int operation = 0;
  
  while (file.get(cipher_letter)) {
    if ((cipher_letter >= 'a' && cipher_letter <= 'z') || (cipher_letter >= 'A' && cipher_letter <= 'Z')) {
      if (cipher_letter >= 'a' && cipher_letter <= 'z') {
	cipher_number = cipher_letter - 'a';
	for (int j = 0; j < SIZE; ++j) {
	  if (tabula_recta[j][*(keyword + operation)] == cipher_letter)
	    decrypted_file.put(tabula_recta[j][0]);
	}
      }
      else if (cipher_letter >= 'A' && cipher_letter <= 'Z') {
	cipher_letter = cipher_letter - 'A' + 'a';
	cipher_number = cipher_letter - 'a';
	for (int j = 0; j < SIZE; ++j) {
	  if (tabula_recta[j][*(keyword + operation)] == cipher_letter)
	    decrypted_file.put(tabula_recta[j][0] + ('A' - 'a'));
	}
      }
      
      ++operation;
      if (operation == keyword_ptr->length())
	operation = 0;
    }

    else {
      decrypted_file.put(cipher_letter);
    }
  }
  
  delete[] keyword;
  decrypted_file.close();
  return;
}
