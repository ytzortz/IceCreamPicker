#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib> 
#include <ctime>
#include "fun.hpp"



struct IceCream {
    std::string name;
    int timesTried =0;
    int rating =0;
    bool exist = true;  //maybe there no ice cream in that place in the shelf
    std::pair<int, int> location; // Assuming coordinates as (row, column)
};

std::vector<IceCream> loadIceCreamData() {
    std::vector<IceCream> iceCreams;
    std::ifstream file("ice_cream_data.txt");
    if (file.is_open()) {
        std::string name;
        int timesTried, rating, row, col;
        bool exist;
        while (file >> name >> timesTried >> rating >> exist >>row >> col) {
            iceCreams.push_back({name, timesTried, rating, exist, {row, col}});
        }
        file.close();
    }else{
        std::cerr<< "An error has accured regarding the file."<<std::endl;
        std::exit(EXIT_FAILURE);
    }
    return iceCreams;
}

void saveIceCreamData(std::vector<IceCream>& iceCreams) {
    std::ofstream file("ice_cream_data.txt");
    if (file.is_open()) {
        for (const auto& iceCream : iceCreams) {
            file << iceCream.name << " "
                 << iceCream.timesTried << " "
                 << iceCream.rating << " "
                 << iceCream.location.first << " "
                 << iceCream.location.second << "\n";
        }
        file.close();
    }
}

bool fileExists(const std::string& filename) {
    std::ifstream file(filename);
    return file.good();
}

int getIntegerInput() {
    int input;
    std::string line;

    while (true) { 

        line = "";
        std::getline(std::cin, line);

        // Attempt to convert to an integer
        try {
            
            if(line!="\0"){
                input = std::stoi(line);
                if(input == 0)
                random_zero_phrase();
                else
                    if(input <0)
                        random_negative_int_phrase();
                    else
                        break; // If successful, break out of the loop                
            }

        } catch (const std::invalid_argument& e) {
            random_int_input_phrase();
        } catch (const std::out_of_range& e) {
            random_out_of_range_int_phrase();
        }
    }

    return input;
}   

std::pair<int, int> init_shelf(){
    bool ready = false;
    int rows;
    int columns;
    std::pair<int, int> layout;
    do
    {
        std::cout<< "How many rows does the shelf hold? ";
        rows = getIntegerInput();
        std::cout << "How many columns does the shelf hold? ";
        columns = getIntegerInput();

        std::string input;
        char answer;
        std::cout<< "\nYour shelf holds " <<rows<<" rows and "<<columns<<" columns. \nIs this correct? (type y/n)\n";
        std::cin>> input;

        if (input.length()>5){
            random_buffer_overflow_phrase();
        }else
            if(input.length() != 1){
                std::cout<< "Next time answer with either \"y\" or \"n\" :P \n\n";
            }else{
                    answer = input[0];
                }
                

        if(answer == 'y')
            ready = true;

    }while(!ready);

    layout.first = rows;
    layout.second = columns;
    
    return layout;
    
}

std::vector<IceCream> init_vector(std::pair<int, int> coords){
    std::vector<IceCream> v;
    for(int i=0; i<coords.first; i++)
        for(int j=0; j<coords.second; j++){
            IceCream new_iceCream;
            new_iceCream.location.first = i;
            new_iceCream.location.second = j;
            new_iceCream.name = "No-name";
            new_iceCream.rating = 0;
            new_iceCream.timesTried =0;

            v.push_back(new_iceCream);
        }

    return v;
}

/**
 * r = recomendations
 * t = top3
 * e = edit
 * p = print vector
 * x = exit
 * else, do nothing.
*/
int userStringInput(std::vector<IceCream> v) {
    std::string userInput;
    std::cout << ">> ";
    std::getline(std::cin, userInput);
    
    if(userInput == "r"){
        return 0;
    }else
        if(userInput == "t"){
            return 1;
        }else
            if(userInput == "e"){
                return 2;
            }else
                if(userInput == "p"){
                    return 3;
                }else
                    if(userInput == "x"){
                        return 4;
                    }else
                        if(userInput == "s"){
                            return 5;
                        }else
                            return 6;


}

void print_vector(std::vector<IceCream>& iceCreams) {
    //add 1 to the coords so the shelves start from 1 and not 0
    for (const auto& iceCream : iceCreams) {
        std::cout << "Name: " << iceCream.name << ", "
            << "Times Taken: " << iceCream.timesTried << ", "
            << "Rate: " << iceCream.rating << ", "
            << "Coordinates: (" << iceCream.location.first +1<< ", " << iceCream.location.second +1<< ")"
            << std::endl;
        } 
}

void recomendation(std::vector<IceCream>& iceCreams){
    
    std::vector<IceCream> untastedIceCreams;

    for(IceCream& IceCream : iceCreams){
        if(IceCream.timesTried == 0){
            untastedIceCreams.push_back(IceCream);
        }
    }
            

    bool accepted = false;

    while (!accepted){
        int randomNumber = std::rand() % (untastedIceCreams.size());
        std::cout<< "\nI recomend you the flavor at the row #"<<untastedIceCreams.at(randomNumber).location.first;
        std::cout<<" and column #"<<untastedIceCreams.at(randomNumber).location.second<<".\n";
        std::cout<< "The name is \'"<<untastedIceCreams.at(randomNumber).name<<"\'.\nWould you like to try it?\n";
        std::cout<< "Type y for yes, n for no.\n";

        std::string input;
        std::getline(std::cin, input);
        
        if(input == "y"){
            accepted = true;
            std::pair<int, int> tastePair = untastedIceCreams.at(randomNumber).location;
            
            for(int i=0; i<iceCreams.size(); i++){
                if(iceCreams.at(i).location == tastePair){
                    iceCreams.at(i).timesTried++;
                    break;
                }
            }

            
        }
        else
            if(input == "n")
                std::cout<< "\nI'll recommend you something else then."<< std::endl;
            else{
                std::cout<<"\nIncorrect answer. I'll show you another option."<<std::endl;
            }
    
    }

    
    std::cout<< "\n\nGood choice! Enjoy!\nDon't forget to save before you go :)\n\n";

}

void editVector(std::vector<IceCream>& iceCreams){


}

void top3(std::vector<IceCream>& iceCreams){


}

void doNothing(std::vector<IceCream>& iceCreams){
    random_no_option_dialog();
}

void finishProgram(std::vector<IceCream>& iceCreams){
    std::cout<< "\nEnjoy your ice cream :)\n"<<std::endl;
    std::exit(EXIT_SUCCESS);
}

bool passValuesToFile(std::ofstream& outFile, std::vector<IceCream> iceCreams){

    if(outFile.is_open()){
        for (const IceCream& iceCream : iceCreams) {
            outFile << "\"" << iceCream.name << "\" " << iceCream.timesTried << " "
                        << iceCream.rating << " " << iceCream.exist << " "
                        << iceCream.location.first<< " " << iceCream.location.second << "\n";
        }        
    
    outFile.close();

    }else
        return false;


    std::cout << "Saved!\n";
    return true;
}

int main() {
    std::srand(std::time(0));

    setDialogCounter();

    std::vector<IceCream> iceCreamVector;

    void (*functionality[])(std::vector<IceCream>&) = {recomendation, top3, editVector, print_vector, finishProgram, saveIceCreamData, doNothing};

    if(!fileExists("ice_cream_data.txt")){
        std::cout<< "File \"ice_cream_data.txt\" does not exist!"<<std::endl;
        std::cout<<"Creating file..."<<std::endl;
        std::ofstream outFile("ice_cream_data.txt");
        std::pair<int, int> layout = init_shelf();

        std::cout<< "Shelf has #"<< layout.first<<" rows and #"<<layout.second<<" columns.\n";

        std::cout<<"\nDefault settings applied. Name = No-name, Times tasted = 0, Rating = 0, and Exist = yes.\n"<<"You can edit these attributes later on.\n"<<std::endl;

        iceCreamVector = init_vector(layout);

        if(!passValuesToFile(outFile, iceCreamVector)){
            std::cerr<< "An error has accured regarding the file."<<std::endl;
            std::exit(EXIT_FAILURE);
            }

    }else{
        std::cout<< "File already exists. \nLoading content of file...\n"<<std::endl;
        
        iceCreamVector= loadIceCreamData();
    }


    while (true)
    {
        std::cout<<"Type \'r\' for a recomendation of a new ice cream, \nType \'t\' for the top 3 ice creams you tasted already,\nType \'e\' to edit any attribute of a spesific ice cream.\nType \'p\' to print all the ice creams with all their attributes.\nType \'s\' to save. \nType \'x\' to exit the program (Don't forget to save before you go ;) ).\n"<<std::endl;
        
        functionality[userStringInput(iceCreamVector)](iceCreamVector);
    }


    return 0;
}
