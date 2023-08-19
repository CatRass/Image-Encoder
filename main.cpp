#include <iostream>
#include <fstream>
#include <vector>

std::string getFileFormat(std::string& fileName);
std::string getFileName(std::string& fileName);
void encode(std::string& fileName, std::string& textForEncoding, std::string& encodeKey);
std::string decode(std::string fileName, std::string keyForDecoding);
void xorEncrypt(std::string& inputString, std::string key);

int main(void){

    char inputChoice;
    std::string emptyInput;
    std::cout << "What would you like to do?" << std::endl;
    std::cout << "[1] Encode" << std::endl << "[2] Decode" << std::endl << "Option: ";
    std::cin >> inputChoice;
    std::getline(std::cin,emptyInput);

    std::string encodeText, encodeFile, encodedFile, encodeKey;
    std::string decodeText, decodeFile, decodeKey;

    switch(inputChoice){
        case('1'):
            std::cout << "What file would you like to encode: ";
            getline(std::cin,encodeFile);
            std::cout << "What text would you like to encode: ";
            getline(std::cin,encodeText);
            std::cout << "What key would you like to use: ";
            getline(std::cin,encodeKey);
            encode(encodeFile,encodeText, encodeKey);
            break;
        case('2'):
            std::cout << "What file would you like to decode: ";
            getline(std::cin,decodeFile);
            std::cout << "What was the key used to encode: ";
            getline(std::cin,decodeKey);
            decodeText = decode(decodeFile,decodeKey);
            std::cout << decodeText << std::endl;
            break;
        default:
            std::cout << "Unknown option. kys.";
            return -1;
    }



    
    std::string exitString;
    std::cout << "Press Enter to Exit ";
    std::cin >> exitString;
       

    return 0;

}

void encode(std::string& fileName, std::string& textForEncoding, std::string& encodeKey){
    std::ifstream inFS;
    std::ofstream outFS;
    std::vector<char> fileVec;
    std::string outputFile = "Output.";
    unsigned int textLen = textForEncoding.size();

    inFS.open(fileName, std::ios::binary);

    while(!inFS.eof()){
        char text;
        text = inFS.get();
        fileVec.push_back(text);
    }

    int encryptionLocation;
    std::string fileFormat = getFileFormat(fileName);
    outputFile.append(fileFormat);
    if(fileFormat == "jpg"){
        encryptionLocation = 0;
    } else if (fileFormat == "png") {
        encryptionLocation = 9;
    }

    xorEncrypt(textForEncoding,encodeKey);
    // std::cout << "Encoded text: " << textForEncoding << std::endl;
    for(char inputChar: textForEncoding){
        fileVec.insert(fileVec.end()-encryptionLocation,inputChar);
    }
    // fileVec.insert(fileVec.end()-encryptionLocation,'/');
    fileVec.insert(fileVec.end()-encryptionLocation,textLen);

    
    outFS.open(outputFile,std::ios::binary);
    for(char byte:fileVec){
        outFS << byte;
    }
}
std::string decode(std::string fileName, std::string keyForDecoding){
    std::ifstream inFS;
    std::vector<char> fileString;
    std::string resultString;
    inFS.open(fileName, std::ios::binary);

    while(!inFS.eof()){
        char text;
        text = inFS.get();
        fileString.push_back(text);
    }

    unsigned int numChars = fileString.at(fileString.size()-11) + 11;

    for(unsigned int i=numChars; i>11; i--){
        resultString += fileString.at(fileString.size()-i);
    }
    
    // xorEncrypt(resultString,keyForDecoding);
    xorEncrypt(resultString,keyForDecoding);
    return resultString;

}

void xorEncrypt(std::string& inputString, std::string key){
    unsigned int keyIndex = 0;
    for(unsigned int i=0; i<inputString.size(); i++){
        inputString.at(i) = key.at(keyIndex) ^ inputString.at(i);
        if(keyIndex == key.size()-1){
            keyIndex = 0;
        } else {
            keyIndex++;
        }
    }
}

std::string getFileFormat(std::string& fileName){
    std::string fileFormat = "";

    fileFormat.push_back(fileName.at(fileName.size()-3));
    fileFormat.push_back(fileName.at(fileName.size()-2));
    fileFormat.push_back(fileName.at(fileName.size()-1));

    return fileFormat;

}

std::string getFileName(std::string& fileName){
    int lastDotIndex = fileName.find_last_of('.');
    std::string fileNameReturn = fileName.substr(0,lastDotIndex);
    return fileNameReturn;
}