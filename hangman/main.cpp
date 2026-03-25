#include<iostream>
#include<random>
#include<ctime>
#include<string>
#include<vector>
#include<cctype>

std::vector<std::string> words = {"codechef", "programming", "learning", "practice"};

void checkGuess(std::vector<int> &state, std::string word, char guess){
    for(int i=0; i<state.size(); i++){
        if(word[i] == guess && state[i] == 0){
            state[i]=1;
        }
    }
}

void wordDisplay(std::vector<int> &state, std::string word){
    for(int i=0; i<state.size(); i++){
        if(state[i] == 1){
            std::cout<<(char)toupper(word[i])<<" ";
        }else{
            std::cout<<"_ ";
        }
    }
}

int main(){
    srand(time(0));
    std::string word = words[rand() % words.size()];
    int guessesLeft = word.size();
    std::vector<int> state(word.size(), 0);
    std::vector<int> finalState(word.size(), 1);

    for(auto &c:word) std::cout<<"_ ";
    
    while(guessesLeft){
        char guess;
        std::cout<<"\nGuesses Left: "<<guessesLeft;
        std::cout<<"\n\nTake the guess: ";
        std::cin>>guess;
        tolower(guess);
        checkGuess(state, word, guess);
        wordDisplay(state, word);
        if(state == finalState && guessesLeft) {
            std::cout<<"\n\n===== You guessed the word =====\n\n";
            break;
        }
        guessesLeft--;
    }
    
    if(state != finalState){
        std::cout<<"\n\n===== GG boi, the word is \""<<word<<"\" =====\n\n";
    }

    return 0;
}