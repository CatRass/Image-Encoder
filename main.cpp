#include <iostream>
// #include <conio.h>

#include "objs/file.hpp"
#include "objs/algorithms.hpp"
#include "menu.hpp"

#define clearCon system("cls")

// Menu option macros

// Encoding Menu
#define MENU_ENC    1
// Decoding Menu
#define MENU_DEC    2
// Change the file we're working with
#define MENU_FILE   3
// Exit
#define EX          0
// Return to Main Menu
#define RETURN_MM clearCon; menuOption = -1; mainMenu(menuOption);


// Cipher options

// Simple Caesar Cipher
#define SIM_CAES    1
#define SIM_XOR     2

/**
 * Gets the file extension for a given file name
 * @param fileName: Name of the file
 * @returns String of the file extension, without the '.'
*/
std::string getExtension(std::string);
/**
 * 
*/
bool isValidFile(std::string);
void operator <<(std::ostream& lhs, std::deque<char>& rhs);
bool setWorkingFile(File* workingFile, std::string &fileExtension);

int main(void){

    int menuOption;
    File* workingFile = nullptr;
    EncryptedFile* outputFile = nullptr;
    std::string fileExtension;

    // if(!setWorkingFile(workingFile, fileExtension)){
    //     return 0;
    // }

    std::string file;

    std::cout << "What file will we be working with?" << std::endl;
    std::getline(std::cin, file);
    fileExtension = getExtension(file);
    
    if(!isValidFile(file)){
        std::cout << "Error: Invalid File" << std::endl;
        return 0;
    }

    if(fileExtension == "png"){
        workingFile = new PNG(file);
    } else if(fileExtension == "jpg"){
        workingFile = new JPG(file);
    } else {
        std::cout << "Extension not currently supported." << std::endl;
        return 0;
    }

    std::cout << workingFile->getStart();

    clearCon;
    mainMenu(menuOption);
    clearCon;

    while(menuOption != EX){

        if(menuOption == MENU_ENC){                                                 // Encoding Menu
            encryptMenu();
            int encrOption;
            std::cin >> encrOption;
            std::cin.ignore(1000, '\n');

            if(encrOption == SIM_CAES){              
                std::string message;
                std::cout << "--Encrypting with Simple Caesers--" << std::endl;

                std::cout << "What would you like to encrypt?" << std::endl;
                std::getline(std::cin, message);

                std::deque<char> outputMessage = algorithms::simpleCaesar(message);

                outputFile = new EncryptedFile(fileExtension,outputMessage);
                // std::deque<char> testMessage = {'t','e','s','t'};
                // EncryptedFile testFile("png",testMessage);
                *outputFile << *workingFile;
                
            } else if (encrOption == SIM_XOR){
                std::string message;
                std::string key;

                std::cout << "--Encrypting with Simple XOR--" << std::endl;

                std::cout << "What would you like to encrypt?" << std::endl;
                std::getline(std::cin, message);
                std::cout << "What is your key?" << std::endl;
                std::getline(std::cin, key);

                std::deque<char> outputMessage = algorithms::simpleXor(message,key);

                outputFile = new EncryptedFile(fileExtension,outputMessage);
                *outputFile << *workingFile;

            } else if (encrOption == EX) {
                RETURN_MM
            } else {
                std::cout << "Error: Invalid option" << std::endl;
            }
            std::cout << std::endl;

        } else if (menuOption == MENU_DEC){                                         // Decoding Menu
            decryptMenu();
            int decrOption;
            std::cin >> decrOption;
            std::cin.ignore(1000, '\n');

            if(decrOption == SIM_CAES){
                std::cout << "--Decrypting with Simple Caesers--" << std::endl;
                std::string message = workingFile->getMessage();
                std::deque<char> decryptedMsg = algorithms::simpleCaesar(message, true);
                std::cout << decryptedMsg;

            } else if (decrOption == SIM_XOR){
                std::string key;

                std::cout << "--Decrypting with Simple XOR--" << std::endl;
                
                std::string message = workingFile->getMessage();

                std::cout << "What is your key?" << std::endl;
                std::getline(std::cin, key);

                std::deque<char> decryptedMsg = algorithms::simpleXor(message,key);

                std::cout << decryptedMsg;

            } else if (decrOption == EX) {
                RETURN_MM
            } else {
                std::cout << "Error: Invalid option" << std::endl;
            }
            std::cout << std::endl;
        } else if(menuOption == MENU_FILE){                                         // Change the current working file
                std::cin.ignore(1000, '\n');
                // if(!setWorkingFile(workingFile, fileExtension)){
                //     return 0;
                // }
                std::cout << "What file will we be working with?" << std::endl;
                std::getline(std::cin, file);
                fileExtension = getExtension(file);
                
                if(!isValidFile(file)){
                    std::cout << "Error: Invalid File" << std::endl;
                    return 0;
                }

                if(fileExtension == "png"){
                    workingFile = new PNG(file);
                } else if(fileExtension == "jpg"){
                    workingFile = new JPG(file);
                } else {
                    std::cout << "Extension not currently supported." << std::endl;
                    return 0;
                }
                RETURN_MM
        } else if (menuOption == EX){
            clearCon;
            mainMenu(menuOption);
        } else {
            std::cout << "Error: Not a valid entry" << std::endl;
            mainMenu(menuOption);
        }
    }

    clearCon;
    return EXIT_SUCCESS;
}

std::string getExtension(std::string fileName){
    unsigned int extensionStart = fileName.find_last_of('.') + 1;
    std::string extension = fileName.substr(extensionStart);
    return extension;
}

bool isValidFile(std::string fileName){
    std::ifstream inFS;

    inFS.open(fileName);
    bool valid = inFS.good();
    inFS.close();
    return valid;
}

void operator <<(std::ostream& lhs, std::deque<char>& rhs){
    for(unsigned int i=0; i<rhs.size(); i++){
        lhs << rhs.at(i);
    }
}

bool setWorkingFile(File* workingFile, std::string &fileExtension){
    std::string file;

    std::cout << "What file will we be working with?" << std::endl;
    std::getline(std::cin, file);
    fileExtension = getExtension(file);
    
    if(!isValidFile(file)){
        std::cout << "Error: Invalid File" << std::endl;
        return false;
    }

    if(fileExtension == "png"){
        workingFile = new PNG(file);
    } else {
        std::cout << "Extension not currently supported." << std::endl;
        return false;
    }

    return true;
}