#include<iostream>
#include<string>
#include<random>
#include<algorithm>
#include<vector>
#include<time.h>

using namespace std;

string scramble_word(string word){
    random_shuffle(word.begin(), word.end());

    return word;
}

int main(){
    int maxGuesses = 3;
    vector<string> words = {"Nigga", "Chigga", "Negro"};
    srand(time(0));
    string word = words[rand() % words.size()];

    string scrambled = scramble_word(word);
    
    while(maxGuesses--){
        cout<<endl;
        cout<<"Guess the word: "<<scrambled<<endl;
        string guess;
        cin>>guess;

        if(guess == word){
            cout<<"Correct! You guessed it!"<<endl;
            break;
        }else{
            if(maxGuesses>0)
            cout<<"Wrong Guess, You have "<<maxGuesses<<" more guess"<<endl;
        }
    }

    if(maxGuesses<=0){
        cout<<"AHH better luck next time"<<endl;
    }
    return 0;
}