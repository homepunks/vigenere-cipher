# The Vigenère cipher 
One of the most widely known multi-alphabet ciphers, it was first created in 1553 by Giovan Battista Bellaso, though it is misattributed to 19th century cryptographer Blaise de Vigenère (Singh 2000).  
Essentially, the Vigenère cipher uses the tabula recta (which can be displayed in your terminal, the program will offer this) with a keyword.
The compiled executable requires one input file, otherwise it will terminate the program. During the runtime, the user will be prompted for a keyword which is the key to encryption/decryption process; then, the program will create an output file containing the enciphered/deciphered text.
```bash
# compile the source code
clang++ vigenere.cpp main.cpp -o vigenere
# run the executable with a file
./vigenere sometext.txt
```
