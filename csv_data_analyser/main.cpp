#include<iostream>
#include<string>
#include<vector>
#include<sstream>
#include<fstream>
#include<iomanip>
#include<algorithm>

std::vector<std::vector<std::string>> data;

void load_csv(){
    std::string filepath;
    std::fstream csvFile;
    std::cout<<"\nEnter CSV file path: ";
    std::cin>>filepath;
    csvFile.open(filepath);
    if (!csvFile.is_open()) {
        std::cerr<<"\n\nError: Could not open the file : "<<filepath<<std::endl;
        return;
    }

    std::string line;
    // std::getline(csvFile, line); //exclude headers
    std::vector<std::string> rows; // vector to store all records

    while(std::getline(csvFile, line)){
        std::stringstream ss(line);
        std::string field;

        while(std::getline(ss, field, ',')){
            rows.push_back(field);
        }
        data.push_back(rows);
        rows.clear();
    }

    std::cout<<"\n\n=== Successfully loaded data from CSV file ==="<<std::endl;
}

void display_info(){
    std::cout<<"\n\nInformation: "<<std::endl;
    std::cout<<"Total Rows: "<<data.size()-1<<std::endl;
    std::cout<<"Total Columns: "<<data[0].size()<<std::endl;

    std::cout<<"\n\nData:"<<std::endl;
    for(auto &row:data){
        for(auto &ele:row){
            std::cout<<ele<<"\t";
        }
        std::cout<<std::endl;
    }
}

void basic_statistics(){
    try{
        std::cout << "\n\nBasic Statistics (Numeric Columns):\n";

        for (int col = 0; col < data[0].size(); col++) {
            std::vector<double> numeric_values;

            for (int row = 1; row < data.size(); row++) {
                if (col >= data[row].size()) continue;

                const std::string &field = data[row][col];
                if (field.empty()) continue;

                try {
                    size_t parsed_chars = 0;
                    double value = std::stod(field, &parsed_chars);

                    if (parsed_chars == field.size()) {
                        numeric_values.push_back(value);
                    }
                } catch (...) {
                    // Skip non-numeric values for this column.
                }
            }

            // Skip non-numeric/text columns.
            if (numeric_values.empty()) {
                continue;
            }

            double sum = 0.0;
            for (double value : numeric_values) {
                sum += value;
            }

            double mean = sum / (double)(numeric_values.size());
            double min_val = *std::min_element(numeric_values.begin(), numeric_values.end());
            double max_val = *std::max_element(numeric_values.begin(), numeric_values.end());

            std::cout << "\nColumn: " << data[0][col] << std::endl;
            std::cout << "Total Non-Null Values: " << numeric_values.size() << std::endl;
            std::cout << "Mean (Average): " << std::fixed << std::setprecision(2) << mean << std::endl;
            std::cout << "Minimum Value: " << min_val << std::endl;
            std::cout << "Maximum Value: " << max_val << std::endl;
        }
    } 
    catch(const std::exception& e){
        std::cerr << e.what() << '\n';
    }
}

void filter_data(){
    std::cout<<"\nAvailable columns: ";
    for(int i=0; i<data[0].size(); i++){
        std::cout<<" "<<data[0][i]<<",";
    }
    std::string column;
    std::cout<<"\nEnter column name to filter (case-sensitive): ";
    std::cin>>column;
    int col_idx=-1;
    for(int i=0; i<data[0].size(); i++){
        if(column==data[0][i]){
            col_idx=i;
            break;
        }
    }

    if (col_idx == -1) {
        std::cout << "\nInvalid column name!";
        return;
    }

    std::string filter;
    std::cout<<"\nEnter value to filter by: ";
    std::cin>>filter;

    std::vector<std::vector<std::string>> filtered_data;
    for(int i=1; i<data.size(); i++){
        if(col_idx < data[i].size() && data[i][col_idx] == filter){
            filtered_data.push_back(data[i]);
        }
    }

    std::cout<<std::endl;
    if(filtered_data.empty()){
        std::cout<<"No matching rows found."<<std::endl;
        return;
    }
    
    std::cout<<"\nData: "<<std::endl;
    for(int i=0; i<data[0].size(); i++){
        std::cout<<data[0][i]<<"\t";
    }

    for(int i=0; i<filtered_data.size(); i++){
        for(int j=0; j<filtered_data[i].size(); j++){
            std::cout<<filtered_data[i][j]<<"\t";
        }
        std::cout<<std::endl;
    }
}

int main(){
    std::cout<<"CSV Data Analyser"<<std::endl;
    load_csv();
    if(data.empty()) {
        std::cout<<"\n\n ==== No data available. === \n"<<std::endl;
        return 0;
    }
    
    while(true){
        std::cout<<"\n\n1. Display Data Information\n2. Show Basic Stats\n3. Filter Data\n4. Exit"<<std::endl;
        std::cout<<"Choose an option: ";
        int choice;
        std::cin>>choice;
        switch(choice){
            case 1:
                display_info();
                break;
            case 2:
                basic_statistics();
                break;
            case 3:
                filter_data();
                break;
            case 4:
                std::cout<<"\n\nExiting...."<<std::endl;
                exit(0);
            default:
                std::cout<<"\n\n\nBruh wtf!! you didn't choose a correct option. Iam leaving....\n\n\n";
                exit(0);
        }
    }

    return 0;
}
