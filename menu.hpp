#include <iostream>

// Dependencies

void title(){
    std::cout << "=== Image Encoder ==="    << std::endl;
}

void algorithmList(){
    std::cout << "Algorithms"  << std::endl;
    std::cout << "[1] Simple Caesar"    << std::endl;
    std::cout << "[2] Simple XOR"    << std::endl;
}

void inputPrompt(){
    std::cout << "Enter your option: ";
}

// Menu Screens

void mainMenu(int &menuOption){
    title();
    std::cout << "[1] Encrypt Message"      << std::endl;
    std::cout << "[2] Decrypt Message"      << std::endl;
    std::cout << "[3] Change File"          << std::endl;
    std::cout << "[0] Exit"                 << std::endl;
    inputPrompt();
    std::cin >> menuOption;
}

void encryptMenu(){
    title();
    std::cout << "=== Encrypt ==="      << std::endl;
    algorithmList();
    std::cout << "[0] Back" << std::endl;
    inputPrompt();
}

void decryptMenu(){
    title();
    std::cout << "=== Decrypt ==="      << std::endl;
    algorithmList();
    std::cout << "[0] Back" << std::endl;
    inputPrompt();
}

