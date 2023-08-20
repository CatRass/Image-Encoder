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
    std::cout << "\t[1] Encode" << std::endl << "\t[2] Decode" << std::endl << "Option: ";
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
            std::cout << "Text encoded as: " << encodeText << std::endl;
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
            std::cout << "Unknown option." << std::endl;
            break;
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
    std::string outputFile = "Output.";                                             // Output file will be saved to Output.FORMAT
    unsigned int textLen = textForEncoding.size();

    inFS.open(fileName, std::ios::binary);                                          // Opens the file in binary mode so the bytes can be read properly

    if(!inFS.fail()){
        while(!inFS.eof()){
            char text;
            text = inFS.get();
            fileVec.push_back(text);
        }

        int encryptionLocation, trim;
        std::string fileFormat = getFileFormat(fileName);
        outputFile.append(fileFormat);
        if(fileFormat == "jpg"){                                                    
            encryptionLocation = 0;                                                 // As different files have different structures, the text has to be placed in different locations as
            trim = 0;
        } else if (fileFormat == "png") {                                           // to not corrupt the file.
            encryptionLocation = 9;                                                 // This whole block of code is used to determine where in the output file the text will be placed.    
            trim = 5;
        }

        xorEncrypt(textForEncoding,encodeKey);

        for(char inputChar: textForEncoding){
            fileVec.insert(fileVec.end()-encryptionLocation,inputChar);
        }

        fileVec.insert(fileVec.end()-encryptionLocation,textLen);                   // To properly decrypt later, we store the length of the encrypted text
                                                                                    // TODO: Create a proper structure to encrypted text, as opposed to just shoving a number at the end of the encrypted text and calling it a day
 
        outFS.open(outputFile,std::ios::binary);                                    // Opens the file in binary mode so the bytes can be read properly
        // for(char byte:fileVec){
        //     outFS << byte;
        // }
        for(unsigned int i=0; i<fileVec.size()-trim; i++){
            char byte = fileVec.at(i);
            outFS << byte;
        }
    } else {
        std::cout << "Failure: Something went wrong" << std::endl;
    }
}
std::string decode(std::string fileName, std::string keyForDecoding){
    std::ifstream inFS;
    std::vector<char> fileString;
    std::string resultString;
    inFS.open(fileName, std::ios::binary);

    if(!inFS.fail()){
        while(!inFS.eof()){
            char text;
            text = inFS.get();
            // std::cout << "At Char: " << text <<std::endl;
            fileString.push_back(text);
        }
                                                                                            // Currently decoding only works for .PNG files.
        unsigned int numChars = fileString.at(fileString.size()-6);                   // TODO: Implement this for any file, not just .PNG
        std::cout << "Length of decode string is: " << numChars << std::endl;

        for(unsigned int i=numChars; i>0; i--){
            resultString += fileString.at(fileString.size()-i-6);
        }
        
        xorEncrypt(resultString,keyForDecoding);                                            // XOR encryption, just like XOR operations are symmetric, but also reversible
    } else {
        resultString = "Failure: Something went wrong";
    }

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