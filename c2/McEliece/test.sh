#!/bin/bash

# generate a test_key
# output: thisismyplaintext
./c2 --generate > test_key.txt
echo "thisismyplaintext" > p1.txt
cat p1.txt | xargs ./c2 --key test_key.txt --encrypt | xargs ./c2 --key test_key.txt --decrypt > p2.txt
diff p1.txt p2.txt -b

# test encryption and decryption for long string
# output: thisismyplaintextthisismyplaintextthisismyplaintextthisismyplaintextthisismyplaintextthisismyplaintext
echo "thisismyplaintextthisismyplaintextthisismyplaintextthisismyplaintextthisismyplaintextthisismyplaintext" > p1.txt
cat p1.txt | xargs ./c2 --key test_key.txt --encrypt | xargs ./c2 --key test_key.txt --decrypt > p2.txt
diff p1.txt p2.txt -b

# test encryption and decryption for very long string
# output: thisismyplaintextthisismyplaintextthisismyplaintextthisismyplaintextthisismyplaintextthisismyplaintextthisismyplaintextthisismyplaintextthisismyplaintextthisismyplaintextthisismyplaintextthisismyplaintextthisismyplaintextthisismyplaintextthisismyplaintextthisismyplaintextthisismyplaintextthisismyplaintextthisismyplaintextthisismyplaintextthisismyplaintextthisismyplaintextthisismyplaintextthisismyplaintext
echo "thisismyplaintextthisismyplaintextthisismyplaintextthisismyplaintextthisismyplaintextthisismyplaintextthisismyplaintextthisismyplaintextthisismyplaintextthisismyplaintextthisismyplaintextthisismyplaintextthisismyplaintextthisismyplaintextthisismyplaintextthisismyplaintextthisismyplaintextthisismyplaintextthisismyplaintextthisismyplaintextthisismyplaintextthisismyplaintextthisismyplaintextthisismyplaintext" > p1.txt
cat p1.txt | xargs ./c2 --key test_key.txt --encrypt | xargs ./c2 --key test_key.txt --decrypt > p2.txt
diff p1.txt p2.txt -b

# test encryption and decryption for very long string from default key
# output: thisismyplaintextfordefaultkey
echo "thisismyplaintextfordefaultkey" > p1.txt
cat p1.txt | xargs ./c2 --encrypt | xargs ./c2 --decrypt > p2.txt
diff p1.txt p2.txt -b

# test encryption and decryption
# output: ThisTestsAlphabetABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789,.;?!()
echo "ThisTestsAlphabetABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789,.;?!()" > p1.txt
cat p1.txt | xargs ./c2 --key test_key.txt --encrypt | xargs ./c2 --key test_key.txt --decrypt > p2.txt
diff p1.txt p2.txt -b

# output: cheater: it is forbidden to decrypt the challenge ciphertext
cat ciphertext.txt | xargs ./c2 --key test_key.txt --decrypt 

# test the cipher is right
# output: NONE
cat plaintext.txt | xargs ./c2 --encrypt > test_cipher.txt
diff test_cipher.txt ciphertext.txt -b