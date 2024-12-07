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

int main(int argc, char* argv[]);
void show_tabula_recta(char tabula_recta[SIZE][SIZE]);
std::string input_keyword(void);
Mode select_mode(const std::string* keyword_ptr);
void encrypt(std::ifstream& file, const std::string* keyword_ptr, char tabula_recta[SIZE][SIZE]);
void decrypt(std::ifstream& file, const std::string* keyword_ptr, char tabula_recta[SIZE][SIZE]);

int main(int argc, char* argv[])
{
  if (argc < 2) {
    std::cout << "Please, provide the input file for enciphering/deciphering as argument.\n";
    return 6969;
  }

  std::ifstream file(argv[1]);
  if (!file) {
    std::cerr << "UNABLE TO OPEN THE INPUT FILE!\n";
    return 6969;
  }
  
  char abc[SIZE + 1] = "abcdefghijklmnopqrstuvwxyz";
  char tabula_recta[SIZE][SIZE];
  for (int i = 0; i < SIZE; ++i)
    for (int j = 0; j < SIZE; ++j)
      tabula_recta[j][i] = abc[(i + j) % SIZE];

  std::cout << "This program uses the Vigenère cipher to encrypt/decrypt the texts contained in text files.\n";
  std::cout << "If you'd like to take a look at the infamous tabula recta used as a foundation for the Vigenère cipher,\n";
  std::cout << "press any letter-key. Press ENTER key twice to proceed.\n";
  
  char choice = getchar();
  std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
  if ((choice >= 'a' && choice <= 'z') || (choice >= 'A' && choice <= 'Z')) {
    show_tabula_recta(tabula_recta);
  }
  
  std::cout << "The Vigenère cipher was improved by Bellaso who added the concept of the secret keyword.\n";
  std::cout << "To enhance encryption, a keyword in a form of the whole string (no whitespaces) needed.\n";
  std::cout << "Your keyword: ";
  std::string keyword;
  keyword = input_keyword();
  std::transform(keyword.begin(), keyword.end(), keyword.begin(), [](unsigned char c) { return std::tolower(c); }); 
  
  std::cout << "The keyword that will be used is: " << keyword << std::endl;
  std::cout << "Now, select the mode. Press E to encrypt and D to decrypt the file.\n";

  Mode mode = select_mode(&keyword); 
  if (mode == ENCRYPT) {
    encrypt(file, &keyword, tabula_recta);
    std::cout << "The enciphered file encrypted.txt is ready!\n";
  }
  else if (mode == DECRYPT) {
    decrypt(file, &keyword, tabula_recta);
    std::cout << "The deciphered file decrypted.txt is ready!\n";
  }
 			       
  file.close();
  return 0;
}

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

  decrypted_file.close();
  return;
}
