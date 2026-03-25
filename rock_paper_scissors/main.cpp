#include<iostream>
#include<random>
#include<string>
#include<vector>
#include<ctime>
#include<algorithm>
#include<cctype>

std::vector<std::string> choices = {"rock", "paper", "scissors"};
int rounds = 3;
int user_wins = 0;
int comp_wins = 0;

std::string getRandomChoice() {
    srand(static_cast<unsigned int>(time(0)));
    return choices[rand() % choices.size()];
}

std::string get_user_choice(){
    std::string user_choice = "";
    
    while((std::find(choices.begin(), choices.end(), user_choice) == choices.end())){
        std::cout<<"Choose Rock or Paper or Scissors\n\n";
        std::cout<<"Enter a valid choice: ";
        std::cin>>user_choice;
        std::transform(user_choice.begin(), user_choice.end(), user_choice.begin(), [](unsigned char c){ return std::tolower(c); });
    }

    return user_choice;
}

void judge(std::string user_choice, std::string comp_choice){
    if(user_choice == "rock" && comp_choice == "scissors" || user_choice == "scissors" && comp_choice == "paper" || user_choice == "paper" && comp_choice == "rock") {
        user_wins++;
    }
    
    if(comp_choice == "rock" && user_choice == "scissors" || comp_choice == "scissors" && user_choice == "paper" || comp_choice == "paper" && user_choice == "rock") {
        comp_wins++;
    }
}

int main(){
    std::cout<<"====== Rock, Paper and Scissors Game ======\n";
    
    for(int i=1; i<=rounds; i++){
        std::cout<<"\nRound - "<<i<<std::endl;
        std::string user_choice = get_user_choice();
        std::string comp_choice = getRandomChoice();

        std::cout<<"Computer Choice: "<<comp_choice<<std::endl;

        judge(user_choice, comp_choice);
        std::cout<<"Score: You - "<<user_wins<<" | Computer - "<<comp_wins<<std::endl;
    }

    std::string won = user_wins>comp_wins ? "You" : "Computer";
    std::cout<<"\n\n\n========= "<<won<<" Won this match =========\n\n\n";

    return 0;
}