/*
 * @Author: Chihow Yao
 * @Date: 2022-08-16 20:54:30
 * @Last Modified Time: 2022-08-21 14:28:47
 * @Description: long integer addition
 */
#include <fstream>
#include <string>
#include <math.h>
#include <unistd.h>     //for parse short option
#include <iostream>

#define RED "\033[31m"
#define RESET "\033[0m"

std::string filename = "sample.txt";
std::string oper[2];
std::string result;

int input_base = 10, output_base = 10;

void print_usage(){
    std::cout << "Usage: add [OPTION]... [FILE]...\n"
              << "Deal with long integer addition from file input.\n"
              << "Options:\n" 
              << "\t-f  set input file path\n"
              << "\t-i  set input base format(2-36)\n"
              << "\t-o  set output base format(2-36)\n"
              << "\t-h  give this help list\n";
}

void convertion2base_ten(std::string* op){ 
    unsigned long long ull = 0;
    int v = 0, iter = 0; 
    for(size_t i = op->size(); i > 0;){
        if(op->at(--i) == '+' || op->at(i) == '-')
            break;
        v = op->at(i) >= 'A' ? op->at(i)-'A'+10 : op->at(i)-'0';
        ull += v * pow(input_base, iter++);
    }
    
    if(op->at(0) == '-')
        *op = "-" + std::to_string(ull);
    else
        *op = std::to_string(ull);
}

void check_file_input(std::string* op){
    for(auto k = 0;k <2; k++){
        int i = 0;
        while(i < op->size()){
            if(op->at(i) >= 'a' && op->at(i) <= 'z' )
                op->at(i) -= 32;
            if(input_base <= 10 && op->at(i) > static_cast<char>(input_base + '0' -1)){
                std::cerr << RED << "[ERROR]: Invalid base detect.\n" << RESET;
                print_usage();
                exit(1);
            }
            if(op->at(i++) > static_cast<char>(input_base + 86)){
                std::cerr << RED << "[ERROR]: Invalid base detect.\n" << RESET;
                print_usage();
                exit(1);
            }
        }
        if(input_base != 10)
            convertion2base_ten(op++);
    }
}

void read_file(const std::string& fn, std::string* op){
    std::ifstream fin;
    fin.open(fn, std::ios::in);
    if (!fin.is_open()){
        std::cerr << RED << "[ERROR]: Open file failed!\n" << RESET;
        exit(1);
    }

    std::getline(fin, *op);
    std::cout << "original data:\n" 
              << *op++ << std::endl;
    std::getline(fin, *op);
    std::cout << *op-- << std::endl
              << "after conversion:\n";
    check_file_input(op);
    std::cout << *op++ << "\n" << *op << std::endl;
}

void processing(std::string& op1, std::string& op2, std::string& result){
    //-----preprocessing-----
    //check substruction
    bool op1_is_negative = (op1[0] == '-' ? true :false);
    bool op2_is_negative = (op2[0] == '-' ? true :false);
    //drop worthless flag
    while(op1.size() > 1 && (op1[0] == '+' || op1[0] == '0' || op1[0] == '-'))
        op1.erase(0, 1);
    while(op2.size() > 1 && (op2[0] == '+' || op2[0] == '0' || op2[0] == '-'))
        op2.erase(0, 1);
    //get operator size
    size_t size1 = op1.size();
    size_t size2 = op2.size();
    //all zero situation
    if(op1[0] == '0' && op2[0] == '0'){
        result = "0";
        return;
    }

    //-----process addition-----
    int carry_flag = 0;
    if(!(op1_is_negative ^ op2_is_negative)){   //both ++ or --
        do{
            //STEP 1: process every bit
            int n;
            if(size1 && size2)
                n = op1.at(--size1) + op2.at(--size2) + carry_flag - '0' - '0';
            else if(size1)
                n = op1.at(--size1) + carry_flag - '0';
            else if(size2)
                n = op2.at(--size2) + carry_flag - '0';
            else{
                if(carry_flag)
                    result = '1' + result;
                break;
            }
                
            //STEP 2: process carry flag
            carry_flag = n >= 10 ? 1 : 0;
            n = n % 10;

            //STEP 3: add bit to result
            result = static_cast<char>(n + '0') + result;
        }while(1);
        if(op1_is_negative || op2_is_negative)  //-- condition
            result = '-' + result;
    }//end additon

    //-----process substruction-----
    else{   
        //preprocessing
        bool op1_is_greater = false;
        if(size1 > size2)
            op1_is_greater = true;
        else if(size1 == size2){
            for(size_t i = 0; i < size1; i++){
                if(op1[i] > op2[i]){
                    op1_is_greater = true;
                    break;
                }
                else if(op1[i] == op2[i])
                    continue;
                else{
                    op1_is_greater = false;
                    break;
                }
            }
        }
        else
            op1_is_greater = false;
        
        //situation 1
        if(op1_is_greater){
            do{           
                int n;
                if(size2 == 0){
                    if(op1.at(--size1) - '0' - carry_flag >= 0){
                        n = op1.at(size1) - '0' - carry_flag;
                        carry_flag = 0;
                    }
                    else{
                        n = op1.at(size1) + 10 - '0' - carry_flag;
                        carry_flag = 1;
                    }
                    result = static_cast<char>(n + '0') + result;
                    continue;
                }
                if(op1.at(--size1) >= op2.at(--size2) + carry_flag){
                    n = op1.at(size1) - op2.at(size2) - carry_flag;
                    carry_flag = 0;
                }
                else{
                    n = op1.at(size1) + 10 - op2.at(size2) - carry_flag;
                    carry_flag = 1;
                }
                result = static_cast<char>(n + '0') + result;
            }while(size1);
            if(op1_is_negative)
                result = '-' + result;
        }
        //situation 2
        else{   //op2 is greater than op1
            do{
                int n;
                if(size1 == 0){
                    if((op2.at(--size2) - '0' - carry_flag) >= 0){
                        n = op2.at(size2) - '0' - carry_flag;
                        carry_flag = 0;
                    }
                    else{
                        n = op2.at(size2) + 10 - '0' - carry_flag;
                        carry_flag = 1;
                    }
                    result = static_cast<char>(n + '0') + result;
                    continue;
                }
                if(op2.at(--size1) >= op1.at(--size2) + carry_flag){
                    n = op2.at(size1) - op1.at(size2) - carry_flag;
                    carry_flag = 0;
                }
                else{
                    n = op2.at(size1) + 10 - op1.at(size2) - carry_flag;
                    carry_flag = 1;
                }
                result = static_cast<char>(n + '0') + result;
            }while(size1);
            if(op2_is_negative)
                result = '-' + result;
        }
    }//end substruction

    //detect result is 00...0xx format
    unsigned long long ull = 0;
    bool sub_flag = false;
    for(size_t i = 0; i < result.size();i++){
        if(result[i] == '-'){
            sub_flag = true;
            continue;
        }
        if(result[i] - '0')
            break;
        else{
            if(sub_flag)
                result.erase(1,1);
            else
                result.erase(0,1);
        }
    }
    if(result == "-0")
        result = "0";
}

std::string convert2other_base(const std::string& res){
    std::string final_result = "";
    std::string tmp = res;
    if(res[0] == '-')
        tmp.erase(0,1);
    unsigned long long ull = std::stoull(tmp);
    int n = 0;
    while(ull >= output_base){
        n = ull % output_base;
        ull /= output_base;
        final_result = std::to_string(n) + final_result;
    }
    final_result = std::to_string(ull) + final_result;
    return final_result;
}

void deal_user_input(char* optarg, int io){
    std::string s  = "";
    while(*optarg != '\0')
        s += *optarg++;
    if(s.size() > 2){
        std::cerr << RED << "[ERROR]: Pass too long parameter.\n" << RESET;
        print_usage();
        exit(1);
    }
    for(auto c : s){
        if(c < '0' || c > '9'){
            std::cerr << RED << "[ERROR]: Detect illegal input.\n" << RESET;
            print_usage();
            exit(1);
        }
    }
    if(std::stoi(s) < 2 || std::stoi(s) > 36){
        std::cerr << RED << "[ERROR]: Detect illegal input.\n" << RESET;
        print_usage();
        exit(1);
    }
    if(io){
        input_base = std::stoi(s);
    }
    else{
        output_base = std::stoi(s);
    }
}

void get_option(int argc, char* argv[]){
    int opt = 0;
    while((opt = getopt(argc, argv, "hf:i:o:")) != -1){
        switch (opt)
        {
        case 'h':
            print_usage();
            exit(0);
        case 'f':
            filename = optarg;
            while(*optarg++ != '\0')
                ;
            continue;
        case 'i':
            deal_user_input(optarg, 1);
            output_base = input_base;
            continue;
        case 'o':
            deal_user_input(optarg, 0);
            continue;
        case '?':
            std::cerr << RED << "[ERROR]: Invalid option!\n" << RESET;
            print_usage(); 
            exit(1);
        }
    }

}

int main(int argc, char* argv[]){
    get_option(argc, argv);
    read_file(filename, oper);
    processing(oper[0], oper[1], result);
    std::cout << "\nresult: " << result 
              << " (base 10)" << std::endl;
    std::cout << "final: " 
              << convert2other_base(result) 
              << " (base " << output_base << ")" << std::endl;
}
