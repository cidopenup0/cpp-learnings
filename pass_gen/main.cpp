#include<iostream>
#include<string>
#include<random>
#include<vector>
#include<ctime>
#include<cstdlib>

std::vector<char> alphas = {'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z','A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z'};
std::vector<char> chars = {'!','"','#','$','%','&','\'','(',')','*','+',',','-','.','/',':',';','<','=','>','?','@','[','\\',']','^','_','`','{','|','}','~'};

std::string n_2_pass(int len){
    std::string pass_n_2;
    
    while(len--){
        int random_index = std::rand() % alphas.size();

        pass_n_2+=alphas[random_index];
    }

    return pass_n_2;
}

std::string generatePassword(int len, char nums, char special){
    std::string pass = n_2_pass(len-2);
    
    if(nums == 'Y' || nums == 'y') pass += '0' + (std::rand() % 10);
    else pass += n_2_pass(1);

    if(special == 'Y' || special == 'y') pass += chars[std::rand() % chars.size()];
    else pass += n_2_pass(1);

    return pass;
}

int main(){
    std::srand(std::time(0));
    int pass_len = 0;
    while(pass_len < 5){
        std::cout<<"Enter the length of password(must be a number and greater than 5): ";
        std::cin>>pass_len;
    }

    char nums;
    std::cout<<"Need Numercials?(Y/N): ";
    std::cin>>nums;

    char special;
    std::cout<<"Need Special Characters?(Y/N): ";
    std::cin>>special;

    std::cout<<generatePassword(pass_len, nums, special);
    return 0;
}