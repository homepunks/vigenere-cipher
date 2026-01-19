# The Vigenère cipher 
One of the most widely known multi-alphabet ciphers, it was first created in 1553 by Giovan Battista Bellaso, though it is misattributed to 19th century cryptographer Blaise de Vigenère (Singh 2000).  
The Vigenère cipher uses the tabula recta with a keyword.
The compiled executable expects just one input text file, otherwise it exits. The mode and the keyword for encryption/decryption are prompted in the runtime. 

## Quickstart
``` console
make
./vigenere example/t8.shakespeare.txt
```

In the ./examples, you can find a showcase of successful encryption and following decryption of Shakespeare's work using keyword "helloworld".
``` console
diff ./examples/t8.shakespeare.txt ./decrypted.txt
```
