#define JSON_HAS_STATIC_RTTI 0
#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<cctype>
#include "json.hpp"

using json = nlohmann::json;

const std::string file_name = "students.json";

std::vector<json> load_data(){
    std::ifstream file(file_name);
    if(!file.is_open()){
        std::cout<<"\nFailed to open file for reading."<<std::endl;
        return {};
    }

    std::vector<json> students;
    json data;
    try{
        file >> data;
    }catch(const std::exception&){
        std::cout<<"\nInvalid JSON format in file."<<std::endl;
        file.close();
        return {};
    }

    if(!data.is_array()){
        std::cout<<"\nInvalid data format: expected a JSON array."<<std::endl;
        file.close();
        return {};
    }

    for(int i=0; i<data.size(); i++){
        students.push_back(data[i]);
    }
    file.close();
    return students;
}

void view_all_records(){
    std::vector<json> data = load_data();
    if(data.empty()) {
        std::cout<<"\nNo student records found.\n";
        return;
    }

    std::cout<<"\n----- Students Records -----"<<std::endl;
    for(auto& it:data){
        std::cout<<"ID: "<<it["id"]<<std::endl;
        std::cout<<"Name: "<<it["name"]<<std::endl;
        std::cout<<"Age: "<<it["age"]<<std::endl;
        std::cout<<"Department: "<<it["department"]<<std::endl;
        std::cout<<"Year: "<<it["year"]<<std::endl;
        std::cout<<"CGPA: "<<it["cgpa"]<<std::endl;
        std::cout<<"Email: "<<it["email"]<<std::endl;
        std::cout<<"---------------------\n"<<std::endl;
    }
}

void search_student(){
    std::string ID;
    std::cout<<"\nEnter student ID to search: ";
    std::cin>>ID;
    
    for(auto& it:ID){
        if(!isdigit(it)){
            std::cout<<"\nInvalid input! Please enter a valid numeric ID."<<std::endl;
            return;
        }
    }
    
    std::vector<json> data = load_data();
    if(data.empty()) {
        std::cout<<"\nNo student records found.\n";
        return;
    }

    json student = {};
    for(int i=0; i<data.size(); i++){
        if(data[i]["id"] == stoi(ID)){
            student = data[i];
            std::cout<<"\n--- Student Found ---"<<std::endl;
        }
    }

    if(student.empty()){
        std::cout<<"\nNo student found with ID "<<ID<<std::endl;
        return;
    }

    std::cout<<"ID: "<<student["id"]<<std::endl;
    std::cout<<"Name: "<<student["name"]<<std::endl;
    std::cout<<"Age: "<<student["age"]<<std::endl;
    std::cout<<"Department: "<<student["department"]<<std::endl;
    std::cout<<"Year: "<<student["year"]<<std::endl;
    std::cout<<"CGPA: "<<student["cgpa"]<<std::endl;
    std::cout<<"Email: "<<student["email"]<<std::endl;    
}

bool compare(const json& value, const std::string& op, float filter_val){
    if(op == ">"){
        return value > filter_val;
    }else if(op == "<"){
        return value < filter_val;
    }else if(op == ">="){
        return value >= filter_val;
    }else if(op == "<="){
        return value <= filter_val;
    }else if(op == "=="){
        return value == filter_val;
    }
}

void filter_students(){
    std::string key;
    std::cout<<"\nEnter key to key by (cgpa/age): ";
    std::cin>>key;
    
    if(key != "cgpa" && key != "age"){
        std::cout<<"\nInvalid key! You can only key by 'cgpa' or 'age'."<<std::endl;
        return;
    }
    
    std::string op;
    std::cout<<"\nEnter condition operator (>, <, >=, <=, ==): ";
    std::cin>>op;
    
    if(op != ">" && op != "<" && op != ">=" && op != "<=" && op != "=="){
        std::cout<<"\nInvalid operator! You can only use (>, <, >=, <=, ==)."<<std::endl;
        return;
    }
    
    float filter_val;
    std::cout<<"\nEnter "<<key<<": ";
    std::cin>>filter_val;
    
    std::vector<json> data = load_data();
    if(data.empty()) {
        std::cout<<"\nNo student records found.\n";
        return;
    }
    
    std::vector<json> filtered;
    for(auto it:data){
        if(compare(it[key], op, filter_val)){
            filtered.push_back(it);
        }
    }
    
    if(filtered.empty()){
        std::cout<<"\nNo students found with "<<key<<" "<<op<<" "<<filter_val<<std::endl;
        return;
    }
    
    std::cout<<"\n--- Students with "<<key<<" "<<op<<" "<<filter_val<<" ---"<<std::endl;
    for(auto& it:filtered){
        std::cout<<"ID: "<<it["id"]<<std::endl;
        std::cout<<"Name: "<<it["name"]<<std::endl;
        std::cout<<"Age: "<<it["age"]<<std::endl;
        std::cout<<"Department: "<<it["department"]<<std::endl;
        std::cout<<"Year: "<<it["year"]<<std::endl;
        std::cout<<"CGPA: "<<it["cgpa"]<<std::endl;
        std::cout<<"Email: "<<it["email"]<<std::endl;
        std::cout<<"---------------------\n"<<std::endl;
    }
}

void write_and_save(std::vector<json> updated_students){
    std::ofstream file(file_name, std::ios::out | std::ios::trunc);
    if(!file.is_open()){
        std::cout<<"\nFailed to open file for writing."<<std::endl;
        return;
    }

    json data = json::array();
    for(const auto& student : updated_students){
        data.push_back(student);
    }

    file<<data.dump(4);
    file.close();
}

void delete_student(){
    std::string ID;
    std::cout<<"\nEnter student ID to delete: ";
    std::cin>>ID;
    
    for(auto& it:ID){
        if(!isdigit(it)){
            std::cout<<"\nInvalid input! Please enter a valid numeric ID."<<std::endl;
            return;
        }
    }

    std::vector<json> data = load_data();
    std::vector<json> updated_students;
    bool found = false;
    for(auto& it:data){
        if(it["id"] != stoi(ID)){
            updated_students.push_back(it);
            continue;
        }
        found = true;
    }

    if(found){
        std::cout<<"\nStudent with ID "<<ID<<" deleted successfully."<<std::endl;
        write_and_save(updated_students);
    }else {
        std::cout<<"\nNo student found with this ID"<<std::endl;
        return;
    }
}

int main(){
    std::string choice;
    while(true){
        std::cout<<"\nJSON Data Processor - Students records"<<std::endl;
        std::cout<<"\n1.View All\n2.Search\n3.Filter\n4.Delete\n5.Exit"<<std::endl;
        std::cout<<"\nEnter a valid choice: ";
        std::cin>>choice;

        if(choice == "1"){
            view_all_records();
        }else if(choice == "2"){
            search_student();
        }else if(choice == "3"){
            filter_students();
        }else if(choice == "4"){
            delete_student();
        }else if(choice == "5"){
            std::cout<<"\nExiting...Goodbye!"<<std::endl;
            break;
        }else{
            std::cout<<"\nInvalid choice. Please try again."<<std::endl;
        }
    }

    return 0;
}