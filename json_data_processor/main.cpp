#include<iostream>
#include<fstream>
#include<string>
#include<vector>

void view_all_records(){

}

int main(){
    while(true){
        std::cout<<"\n1.View All\n2.Search\n3.Filter\n4.Delete\n5.Exit"<<std::endl;
        std::cout<<"\nEnter a valid choice: ";
        int choice;
        std::cin>>choice;

        switch(choice){
            case 1:
                view_all_records();
                break;
            case 2:
                // search_record();
                break;
            case 3:
                // filter_record();
                break;
            case 4:
                // delete_record();
                break;
            case 5:
                std::cout<<"\nExiting...."<<std::endl;
                exit(0);
            default:
                std::cout<<"\nEnter a valid choice"<<std::endl;
        }
    }

    return 0;
}