#include <iostream>
#include <fstream>
#include <deque>

#ifndef FILE
#define FILE

#define MSG_START fileContents.size() - (this->start)
#define MSG_LEN this->fileContents.at(this->fileContents.size()-2)

/**
 * Abstract parent class for all filetypes
*/
class File {

    public:

        /**
         * @returns The files start value in char form.
        */
        char getStart() const {
            return this->start;
        }

        /**
         * @returns The files size, in the number of chars in the file
        */
        unsigned int getFileSize() const {
            return this->fileContents.size();
        }

        /**
         * @param index: The index that you wish to copy
         * @returns The value at the specified index
        */
        char copyFileContents(unsigned int index) const {
            return this->fileContents.at(index);
        }

        /**
         * @returns The message in a file
        */
        std::string getMessage(){
            std::string imageMessage;
            for(int i=0; i<(int)MSG_LEN; i++){
                unsigned int currentPos = (fileContents.size()-2) - this->start - MSG_LEN + i;
                imageMessage.push_back(fileContents.at(currentPos));
            }

            return imageMessage;
        }

    protected:
        std::string fileName;
        std::deque<char> fileContents;

        /**
         * The amount of characters from the end that you need to go back to place the encoded text.
        */
        unsigned char start;

        void readFileContents(){
            std::ifstream inFS;
            inFS.open(this->fileName, std::ios::binary);

            while(!inFS.eof() && inFS.is_open()){
                char byte = inFS.get();
                this->fileContents.push_back(byte);
            }

            inFS.close();
        }

        void writeFileContents(){
            std::ofstream outFS;
            outFS.open(this->fileName, std::ios::binary);

            for(unsigned int i=0; i<this->fileContents.size(); i++){
                outFS << this->fileContents.at(i);
            }

            outFS.close();
        }

};

class EncryptedFile: public File {
    
    public:
        EncryptedFile(std::string fileExtension, std::deque<char> message){
            this->fileName = "Output."+fileExtension;
            this->message = message;
        }

        void operator<<(File &rhs){

            // Copy everything from the original file up until the start
            for(unsigned int i = 0; i<rhs.getFileSize()-(int)rhs.getStart()-1; i++){
                this->fileContents.push_back(rhs.copyFileContents(i));
            }

            // Insert the message
            for(unsigned int i=0; i<message.size(); i++){
                this->fileContents.push_back(message.at(i));
            }

            // Continue with the file Insertion
            for(unsigned long i=rhs.getFileSize()-(int)rhs.getStart()-1; i<rhs.getFileSize()-1; i++){
                this->fileContents.push_back(rhs.copyFileContents(i));
            }

            this->fileContents.push_back(this->message.size());

            this->writeFileContents();
        }

    private:
        std::deque<char> message;

};

// File types currently supported

class PNG: public File {
    public:
        PNG(std::string fileName){
            this->fileName = fileName;
            this->start = 9;
            this->readFileContents();
        }
};

class JPG: public File {
    public:
        JPG(std::string fileName){
            this->fileName = fileName;
            this->start = 1;
            this->readFileContents();
        }
};

#endif // FILE