#include<iostream>
#include<vector>
#include<string>
#include<fstream>
#include<ctime>
#include<random>
#include<cctype>
#include<algorithm>

std::vector<std::string> log_levels = {"INFO", "WARNING", "ERROR"};
std::vector<std::vector<std::string>> log_messages = {
    {"Application started", "User logged in", "User logged off"},
    {"Disk space running low", "Some files are corrupted"},
    {"File not found", "Network is down"}
};

bool open_file(std::fstream& file, std::ios::openmode mode = std::ios::in){
    file.open("log.txt", mode);
    if(!file.is_open()){
        std::cout<<"\nCouldn't find the file log.txt in current directory\n";
        return false;
    }
    return true;
}

void generate_log(){
    std::fstream logFile;
    if(!open_file(logFile, std::ios::app)){
        return;
    }
    int random_level_idx = rand()%log_levels.size();
    std::string random_level = log_levels[random_level_idx];
    std::string random_message = log_messages[random_level_idx][rand()%log_messages[random_level_idx].size()];
    
    std::time_t curr_time = time(0);
    std::tm* local_time = localtime(&curr_time);
    char time_buffer[80];
    
    strftime(time_buffer, sizeof(time_buffer), "%Y-%m-%d %H:%M:%S", local_time);
    logFile<<time_buffer<<" ["<<random_level<<"] "<<random_message<<std::endl;
    std::cout<<"\nNew log entry added!\n"<<std::endl;
    logFile.close();
}

bool is_file_empty(std::fstream& pFile){
    return pFile.peek() == std::fstream::traits_type::eof();
}

void view_logs(){
    std::fstream logFile;
    if(!open_file(logFile)){
        return;
    }
    if(is_file_empty(logFile)){
        std::cout<<"\nNo logs found."<<std::endl;
        logFile.close();
        return;
    }
    
    std::cout<<"\n--- Log Entries ---\n"<<std::endl;
    std::string line;

    while(std::getline(logFile, line)){
        std::cout<<line<<std::endl;
    }

    logFile.close();
}

void filter_logs_by_level(){
    std::string log_level;
    std::cout<<"Enter log level (INFO, WARNING, ERROR): ";
    std::cin>>log_level;
    std::cout<<"\n";

    for(auto& c:log_level){
        c = std::toupper(c);
    }

    if (log_level != "INFO" && log_level != "WARNING" && log_level != "ERROR") {
        std::cout << "\nInvalid log level!\n" << std::endl;
        return;
    }

    std::fstream logFile;
    if(!open_file(logFile)){
        return;
    }

    std::cout<<"--- "<<log_level<<" Logs ---"<<std::endl;
    std::string line;
    bool print_flag = false;
    while(std::getline(logFile, line)){
        if(line.find('['+log_level+']') != std::string::npos){
            std::cout<<line<<std::endl;
            print_flag=true;
        }
    }

    if(!print_flag) std::cout<<"\nNo ["<<log_level<<"] logs found."<<std::endl;
    logFile.close();
}

void search_logs(){
    std::fstream logFile;
    if(!open_file(logFile)){
        return;
    }

    std::cout<<"\nEnter keyword to search in logs: ";
    std::string keyword;
    std::cin>>keyword;

    std::transform(keyword.begin(), keyword.end(), keyword.begin(), [](unsigned char c){ return std::tolower(c); });
    
    std::string line;
    std::vector<std::string> results;
    
    while(std::getline(logFile, line)){
        std::string temp=line;
        std::transform(temp.begin(), temp.end(), temp.begin(), [](unsigned char c){ return std::tolower(c); });

        if(temp.find(keyword)!=std::string::npos){
            results.push_back(line);
        }
    }

    if(results.size()>0){
        std::cout<<"\n--- Logs containing '"<< keyword <<"' ---"<<std::endl;
        for(auto &r:results){
            std::cout<<r<<std::endl;
        }
    }else{
        std::cout<<"\nNo logs found containing '"<< keyword <<"'"<<std::endl;
    }

    logFile.close();
}

void log_statistics(){
    std::fstream logFile;
    if(!open_file(logFile)){
        return;
    }

    if(is_file_empty(logFile)){
        std::cout<<"\nNo logs found to analyze."<<std::endl;
        logFile.close();
        return;
    }

    std::cout<<"\n--- Log Statistics ---"<<std::endl;
    int total_logs=0;
    int info_logs=0;
    int warning_logs=0;
    int error_logs=0;
    
    std::string line;
    std::string prevLine = "";
    while(std::getline(logFile, line)){
        total_logs++;
        if(line.find("INFO")!=std::string::npos){
            info_logs++;
        }else if(line.find("WARNING")!=std::string::npos){
            warning_logs++;
        }else if(line.find("ERROR")!=std::string::npos){
            error_logs++;
        }
        prevLine=line;
    }
    std::cout<<"Total logs: "<<total_logs<<std::endl;
    std::cout<<"INFO logs: "<<info_logs<<std::endl;
    std::cout<<"WARNING logs: "<<warning_logs<<std::endl;
    std::cout<<"ERROR logs: "<<error_logs<<std::endl;
    std::cout<<"Most recent log: "<<prevLine<<std::endl;

    logFile.close();
}

int main(){
    srand(time(0));
    while(true){
        int choice;
        std::cout<<"\n1.Generate a log\n2.View logs\n3.Filter logs\n4.Search logs\n5.View log statistics\n6.Exit";
        std::cout<<"\nEnter your choice: ";
        std::cin>>choice;

        switch(choice){
            case 1:
                generate_log();
                break;
            case 2:
                view_logs();
                break;
            case 3:
                filter_logs_by_level();
                break;
            case 4:
                search_logs();
                break;
            case 5:
                log_statistics();
                break;
            case 6:
                std::cout<<"\nExiting....";
                exit(0);
            default:
                std::cout<<"\nNot a valid choice";
                break;
        }
    }
    return 0;
}