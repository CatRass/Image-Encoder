#ifndef ALGO
#define ALGO

#include <iostream>

#define INPUT std::string message

/**
 * A simple Caesar Ciphe that shifts by three letters up.
 * It does not take into account looping (Z does not loop back to C, etc.)
 * @returns A deque containing the encrypted message
*/
std::deque<char> simpleCaesar(INPUT, bool decrypt=false){
    std::deque<char> returnMsg;
    for(unsigned int i=0; i < message.size(); i++){
        returnMsg.push_back(message.at(i)+= 3+(-6*decrypt));
    }
    return returnMsg;
}

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

#endif //ALGO