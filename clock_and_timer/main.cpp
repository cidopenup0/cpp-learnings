#include <iostream>
#include <ctime>
#include <iomanip>
#include <windows.h>

void digital_clock() {
    while(true){
        // Get the current time
        std::time_t current_time = std::time(nullptr);
        std::tm * local_time = std::localtime(&current_time);
        // Format the time as a string
        std::cout << "\r" <<"Current Time: " << std::put_time(local_time, "%Y-%m-%d %H:%M:%S") << std::flush;
        Sleep(1000);
    }
}

void countdown_timer(){
    long seconds;
    std::cout<<"Enter the number of seconds to countdown: ";
    std::cin>>seconds;

    while(seconds--){
        std::time_t current_time = std::time(nullptr);
        std::tm * local_time = std::localtime(&current_time);
        // Format the time as a string
        std::cout << "\r" <<"Current Time: " << std::put_time(local_time, "%H:%M:%S") << std::flush;
        Sleep(1000);
    }
    std::cout<<std::endl;
    std::cout<<"Time's up\n";
}

int main(){
    int input;
    
    std::cout<<"1. Digital clock\n2.Countdown timer\n";
    std::cout<<"Enter your choice: \n";
    std::cin>>input;

    switch (input){
        case 1:
        digital_clock();
        break;

        case 2:
        countdown_timer();
        break;

        default:
        std::cout<<"Invalid input\n";
        break;
    }
}