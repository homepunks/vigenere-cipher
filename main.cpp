#include "vigenere.h"

int main(int argc, char* argv[])
{
  if (argc != 2) {
    std::cout << "Please, provide ONE input file for enciphering/deciphering as argument.\n";
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
  if ((choice >= 'a' && choice <= 'z') || (choice >= 'A' && choice <= 'Z'))
    show_tabula_recta(tabula_recta);
  
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
