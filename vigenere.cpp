#include "vigenere.h"

void show_tabula_recta(const char (&tabula_recta)[SIZE][SIZE]) {
  for (size_t i = 0; i < SIZE; ++i) {
    for (size_t j = 0; j < SIZE; ++j) std::cout << tabula_recta[j][i] << ' ';
    std::cout << '\n';
  }
}

std::string input_keyword() {
  std::string keyword;
  std::string input;
  std::getline(std::cin, input);
  for (char ch : input) {
    if (std::isalpha(ch))
      keyword += ch;
    else if (ch == ' ') {
      std::cout << "The keyword must be a no whitespaces string. Only the "
                   "letters before the whitespace will be used.\n";
      break;
    } else {
      std::cout << "Non-alphabetical symbols cannot be used in the keyword. "
                   "Only the letters before the symbol "
                << ch << " will be used.\n";
      break;
    }
  }

  return keyword;
}

Mode select_mode(const std::string& keyword) {
  while (true) {
    char mode = getchar();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    if (mode == 'E' || mode == 'e') {
      std::cout << "ENCRYPTION MODE SELECTED. YOUR FILE WILL BE ENCIPHERED "
                   "USING THE KEYWORD "
                << keyword << std::endl;
      return ENCRYPT;
    } else if (mode == 'D' || mode == 'd') {
      std::cout << "DECRYPTION MODE SELECTED. YOUR FILE WILL BE DECIPHERED "
                   "USING THE KEYWORD "
                << keyword << std::endl;
      return DECRYPT;
    } else {
      std::cout << "Invalid input: press E or D to select the mode. No other "
                   "modes exist.\n";
    }
  }
}

void encrypt(std::ifstream& file, const std::string& keyword,
             const char (&tabula_recta)[SIZE][SIZE]) {
  if (!file.is_open()) throw std::runtime_error("INPUT FILE NOT OPEN!\n");

  std::ofstream encrypted_file("encrypted.txt");
  if (!encrypted_file)
    throw std::runtime_error("FAILED TO CREATE OUTPUT FILE!\n");

  std::vector<int> keyword_indices;
  keyword_indices.reserve(keyword.size());
  for (char c : keyword) keyword_indices.push_back(c - 'a');
  if (keyword_indices.empty()) throw std::runtime_error("EMPTY KEYWORD!\n");

  char plain_letter;
  size_t operation = 0;

  while (file.get(plain_letter)) {
    if (std::isalpha(plain_letter)) {
      const bool is_upper = std::isupper(plain_letter);
      const int plain_number = std::tolower(plain_letter) - 'a';

      char encrypted_letter =
          tabula_recta[plain_number][keyword_indices[operation]];
      if (is_upper) encrypted_letter = std::toupper(encrypted_letter);
      encrypted_file.put(encrypted_letter);

      operation = (operation + 1) % keyword_indices.size();
    } else {
      encrypted_file.put(plain_letter);
    }
  }

  return;
}

void decrypt(std::ifstream& file, const std::string& keyword,
             const char (&tabula_recta)[SIZE][SIZE]) {
  if (!file.is_open()) {
    throw std::runtime_error("INPUT FILE NOT OPEN\n");
  }

  std::ofstream decrypted_file("decrypted.txt");
  if (!decrypted_file)
    throw std::runtime_error("FAILED TO CREATE OUTPUT FILE!\n");

  std::vector<int> keyword_indices;
  keyword_indices.reserve(keyword.size());
  for (char c : keyword) keyword_indices.push_back(c - 'a');
  if (keyword_indices.empty()) throw std::runtime_error("EMPTY KEYWORD!\n");

  char cipher_letter;
  size_t operation = 0;

  while (file.get(cipher_letter)) {
    if (std::isalpha(cipher_letter)) {
      const bool is_upper = std::isupper(cipher_letter);
      const char lower_letter = std::tolower(cipher_letter);
      const int key_index = keyword_indices[operation];

      bool found = false;
      for (size_t row = 0; row < SIZE; ++row) {
        if (std::tolower(tabula_recta[row][key_index]) == lower_letter) {
          char decrypted = tabula_recta[row][0];
          decrypted_file.put(is_upper ? std::toupper(decrypted) : decrypted);

          found = true;
          break;
        }
      }

      if (!found)
        throw std::runtime_error("INVALID CHARACTER IN CIPHERTEXT!\n");

      operation = (operation + 1) % keyword_indices.size();
    } else {
      decrypted_file.put(cipher_letter);
    }
  }

  return;
}
