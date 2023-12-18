#ifndef ALGO
#define ALGO

#include <iostream>

#define INPUT std::string message

namespace algorithms {
    /**
     * A simple Caesar Cipher that shifts the ASCII code by three digits up.
     * It does not take into account 'alphabet looping' (Z does not loop back to C, etc.)
     * @param message: String of the message the user wants to encrypt
     * @param decrypt: Boolean for determining if the algorithm is being used for encryption or decryption
     * @returns A deque containing the encrypted message
    */
    std::deque<char> simpleCaesar(INPUT, bool decrypt=false){
        std::deque<char> returnMsg;
        for(unsigned int i=0; i < message.size(); i++){
            // If decrypting, you will be adding: 3 + -6*1 = -3
            // If encrypting, you will be adding: 3 + -6*0 =  3
            returnMsg.push_back(message.at(i)+= 3+(-6*decrypt));
        }
        return returnMsg;
    }

    /**
     * A simple XOR encryption algorithm
     * It does not take into account 'alphabet looping'
     * @param message: String of the message the user wants to encrypt
     * @returns A deque containing the encrypted message
     * @note XOR encryption does not require a decryption check by the nature of how XOR works.
    */
    std::deque<char> simpleXor(INPUT, std::string key){
        std::deque<char> returnMsg;
        unsigned int keyIndex = 0;
        for(unsigned int i=0; i< message.size(); i++){
            returnMsg.push_back(message.at(i) xor key.at(keyIndex));
            if(keyIndex == key.size()-1){
                keyIndex = 0;
            } else {
                keyIndex++;
            }
        }
        return returnMsg;
    }
}

#endif //ALGO