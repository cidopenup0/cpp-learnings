#include<iostream>
#include<string>
#include<vector>
#include<unordered_map>
#include<limits>
#include<fstream>
#include<iomanip>

std::unordered_map<std::string, std::string> shortenedURLs;
std::unordered_map<std::string, std::string> longerURLs;
const std::string DB_FILE = "url_store.txt";

void loadFromDisk(){
    std::ifstream input(DB_FILE);
    if(!input){
        return;
    }

    std::string shortCode;
    std::string longURL;
    while(input >> std::quoted(shortCode) >> std::quoted(longURL)){
        shortenedURLs[shortCode] = longURL;
        longerURLs[longURL] = shortCode;
    }
}

void saveToDisk(){
    std::ofstream output(DB_FILE, std::ios::trunc);
    if(!output){
        std::cout<<"\nWarning: unable to persist URLs to disk.\n";
        return;
    }

    for(const auto& entry : shortenedURLs){
        output << std::quoted(entry.first) << " " << std::quoted(entry.second) << "\n";
    }
}

void shortenURL(){
    std::string longURL;
    std::cout<<"\nEnter long URL: ";
    std::cin>>longURL;

    if(longURL.size() == 0) {
        std::cout<<"\nError: URL cannot be empty\n";
        return;
    }
    
    int hash = 0;
    for(int i=0; i<longURL.length(); i++){
        hash = (hash * 31 + longURL[i]) % 1000000;
    }
    
    std::string hashCode = "";
    for(int i=1; i<=6; i++){
        hashCode += 'a' + (hash % 26);
        hash/=26;
    }
    
    if(longerURLs.count(longURL)){
        std::cout<<"\nShort URL already exists: http://short.ly/"<<hashCode<<"\n";
    }else{
        shortenedURLs[hashCode] = longURL;
        longerURLs[longURL] = hashCode;
        saveToDisk();

        std::cout<<"\nShort URL created: http://short.ly/"<<hashCode<<"\n";
    }
}

void retrieveURL(){
    std::string shortenURL;
    std::cout<<"\nEnter shortened URL: ";
    std::cin>>shortenURL;

    const std::string prefix = "http://short.ly/";
    if(shortenURL.rfind(prefix, 0) == 0){
        shortenURL = shortenURL.substr(prefix.length());
    }

    if(shortenedURLs.count(shortenURL)){
        std::cout<<"\nOriginal URL: "<<shortenedURLs[shortenURL]<<"\n";
    }else{
        std::cout<<"\nShort URL not found!\n";
    }
}

int main(){
    loadFromDisk();

    while(true){
        int choice;
        std::cout<<"\n\n1. Shorten URL\n2. Retrieve URL\n3. Exit\n";
        std::cout<<"Enter your choice: ";
        if(!(std::cin>>choice)){
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout<<"Invalid Choice!! Enter valid choice\n";
            continue;
        }
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');    

        switch(choice){
            case 1:
                shortenURL();
                break;
            case 2:
                retrieveURL();
                break;
            case 3:
                std::cout<<"\nExiting... GoodBye\n";
                exit(0);
            default:
                std::cout<<"\nInvalid Choice!! Enter valid choice\n";
        }
    }
}