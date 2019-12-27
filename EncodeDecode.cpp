#include <iostream> //print out result to console
#include <fstream> //read/write to text file
#include <string> //Use .at() and .length()
#include <conio.h> //Use _getch()

//Jamie Griffiths C++

void CompressFile(std::string FileName); //Compress chosen file and print out compression ratio
void DecompressFile(std::string FileName); //Decompress chosen file

int main()
{
    //Compress / decompress first text file
    CompressFile("compress_decompress_1.txt");
    DecompressFile("compress_decompress_1.txt");

    //Compress / decompress second text file
    CompressFile("compress_decompress_2.txt");
    DecompressFile("compress_decompress_2.txt");

    _getch(); //Used so console doesn't immediately close when running executable, not required

    return 0;
}

void CompressFile(std::string FileName)
{
    //Create ifstream class to read from files
    std::ifstream ReadFromTextFile;
    
    //Open the selected file
    ReadFromTextFile.open(FileName);

    //If file doesn't exist then warn user and close program
    if (ReadFromTextFile.fail()) 
    {
        std::cout << "Failed to find text file name, reset program" << std::endl;
        return;
    }

    //Store contents of text file into string FileContents. Using getline to preserve whitespaces in textfile
    std::string FileContents = "";
    getline(ReadFromTextFile, FileContents);
    
    //Save the run-length encoing result into CompressionResult
    std::string CompressionResult = "";

    //Save size of uncompressed text into UncompressedSize
    float UncompressedSize = FileContents.length();

    //CharAmount to store how many times a character repeats
    int CharAmount = 0;

    //PreviousChar used to hold the previously checked character to see if the next character changes or not. Set to null at start
    char PreviousChar = '\0';

    //Loop that goes through text file to perform run-length encoding
    for (int i = 0; i != UncompressedSize; i++)
    {

        //If first time looking in text file then set PreviousChar to the first character in text file
        if (i == 0) { PreviousChar = FileContents.at(0); };

        //If next character in text file is the same as previous character then increment CharAmount
        if (FileContents.at(i) == PreviousChar) 
        {
            CharAmount++;
        }
        //Otherwise next character is different so save the character and how many times it appears into CompressionResult
        else 
        {
            //If a character appears more then 9 times then add , around it so the decompression method knows when the next character to be added starts
            if (CharAmount >= 10) { CompressionResult += ","; }

            CompressionResult += std::to_string(CharAmount);

            if (CharAmount >= 10) { CompressionResult += ","; }

            CompressionResult += PreviousChar;

            
            
            //Reset CharAmount to 1 as checked character was different to previous
            CharAmount = 1;
        }

        //Move SecondCompareChar to next position ready for next loop through
        PreviousChar = FileContents.at(i);
    }

    //Once program has reached the end of the text file, add the remaining character and number to the CompressionResult 
    if (CharAmount != 0)
    {
        if (CharAmount >= 10) { CompressionResult += ","; }

        CompressionResult += std::to_string(CharAmount);

        if (CharAmount >= 10) { CompressionResult += ","; }

        CompressionResult += PreviousChar;
    }

    //Close the text file when done
    ReadFromTextFile.close();

    //Create ofstream class to write to files
    std::ofstream WriteToTextFile;

    //Open the selected file
    WriteToTextFile.open(FileName);

    //Write the string CompressionResult to the selected file
    WriteToTextFile << CompressionResult;

    //Close the file when done
    WriteToTextFile.close();

    //Print to console what file has been encoded and reports the compression ratio (found by dividing uncompressed size by compressed size)
    std::cout << "Run-length encoded " << FileName << " with a compression ratio of " << UncompressedSize / CompressionResult.length() << std::endl;

}


void DecompressFile(std::string FileName)
{
    //Create ifstream class to read from files
    std::ifstream ReadFromTextFile;

    //Open the selected file
    ReadFromTextFile.open(FileName);

    //If file doesn't exist then warn user and close program
    if (ReadFromTextFile.fail())
    {
        std::cout << "Failed to find text file name, reset program" << std::endl;
        return;
    }

    //Store contents of text file into string FileContents. Using getline to preserve whitespaces in textfile
    std::string FileContents = "";
    getline(ReadFromTextFile, FileContents);

    //The decompression result will be saved into DecompressionResult
    std::string DecompressionResult = "";
    
    //Letter is the character that needs to be added to DecompressionResult
    char Character = '\0';

    //NumberOfTimes is how many times the letter needs to be added to DecompressionResult
    int NumberOfTimes = 0;
    
    //value is used to convert the number in the text file to an int
    std::string value = "";

    //Used to read different positions within the file contents, looking at either a character that needs to be added or how many times the character needs to be added
    int NumberReadingPosition = 0;
    int CharacterReadingPosition = 1;

    //Used when a character needs to be added more then 9 times
    std::string AmountToAdd = "";
    
    //Loops until the reading position reaches the end of the text file
    while (CharacterReadingPosition < FileContents.length())
    {
        //Find how many times a character needs to be added   
        value = FileContents.at(NumberReadingPosition);

        //If , is in compressed text file then need to find the next comma to know how many times a character needs to be added
        if (value == ",") 
        {
            //Add the value after the comma to AmountToAdd 
            NumberReadingPosition++;
            value = FileContents.at(NumberReadingPosition);
            AmountToAdd += value;

            //Loops until the second comma is found
            while (value != ",") 
            {
                //Looks in the next position for the comma
                NumberReadingPosition++;
                value = FileContents.at(NumberReadingPosition);

                //If comma still not found then add the next number to AmountToAdd
                if (value != ",") 
                {
                    AmountToAdd += value;
                }
            }

            //NumberOfTime equals how many times a character needs to be added
            NumberOfTimes = stoi(AmountToAdd);

            //Move the character reading position to after the second comma
            CharacterReadingPosition = NumberReadingPosition + 1;

            //Clear string ready for next repeated character
            AmountToAdd = "";
        }
        //Otherwise the character is added a single digit number of times
        else 
        {
            NumberOfTimes = stoi(value);
        }
        
        
        //Find the character that needs to be added
        Character = FileContents.at(CharacterReadingPosition);

        //Adds the character to DecompressionResult how many times it needs to be added
        for (int AddLetter = 0; AddLetter != NumberOfTimes; AddLetter++)
        {
            DecompressionResult += Character;
        }

        //Move the number and character reading positions to the next position
        NumberReadingPosition += 2;
        CharacterReadingPosition += 2;
        
    }

    //Close the text file when done
    ReadFromTextFile.close();
    
    //Create ofstream class to write to files
    std::ofstream WriteToTextFile;

    //Open the selected file
    WriteToTextFile.open(FileName);

    //Write the string CompressionResult to the selected file
    WriteToTextFile << DecompressionResult;

    //Close the file when done
    WriteToTextFile.close();
    

    //Print to console what file has been decompressed
    std::cout << "Decompressed the file " << FileName << std::endl;
      
}
