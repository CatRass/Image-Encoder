#include <iostream>
#include <fstream>
#include <vector>

std::string getFileFormat(std::string& fileName);
std::string getFileName(std::string& fileName);
void encode(std::string& fileName, std::string& textForEncoding);
void xorEncrypt(std::string& inputString, std::string key);

int main(void){

    std::string encodeText, encodeFile;
    std::string encodedFile;

    std::cout << "What file would you like to encode: ";
    getline(std::cin,encodeFile);
    std::cout << "What text would you like to encode: ";
    getline(std::cin,encodeText);

    encode(encodeFile,encodeText);
    
    std::string exitString;
    std::cout << "Press Enter to Exit ";
    std::cin >> exitString;
    return 0;

}

void encode(std::string& fileName, std::string& textForEncoding){
    std::ifstream inFS;
    std::ofstream outFS;
    std::vector<char> fileVec;
    std::string outputFile = "Output.";

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

    xorEncrypt(textForEncoding,"Key Here");
    for(char inputChar: textForEncoding){
        fileVec.insert(fileVec.end()-encryptionLocation,inputChar);
    }

    
    outFS.open(outputFile,std::ios::binary);
    for(char byte:fileVec){
        outFS << byte;
    }
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