#include <fstream>
#include <string>
#include <numeric>
#include <unistd.h>     //for parse short option
#include <iostream>

#define RED "\033[31m"
#define RESET "\033[0m"

std::string filename = "sample.txt";
std::string oper[2];
std::string result;

void print_usage(){
    std::cout << "Usage: add [OPTION]... [FILE]...\n"
              << "Deal with long integer addition from file input.\n"
              << "Options:\n" 
              << "\t-f  set input file path\n"
              << "\t-i  set input base format\n"
              << "\t-o  set output base format\n"
              << "\t-h  give this help list\n";
}

bool read_operator(const std::string& fn, std::string* op){
    std::ifstream fin;
    fin.open(fn, std::ios::in);
    if (!fin.is_open()){
        std::cerr << RED << "[ERROR]: Open file failed!\n" << RESET;
        return false;
    }
    std::getline(fin, *op);
    std::cout << *op++ << std::endl;
    std::getline(fin, *op);
    std::cout << *op << std::endl;
    return true;
}

void addition(std::string& op1, std::string& op2, std::string& result){
    bool sub = false;
    sub =  op1[0] == '-' ? true : (op2[0] == '-' ? true : false);
    // if(sub)
    //     std::cout << "substraction";
    if(op1[0] == '+' || op1[0] == '0' || op1[0] == '-')
        op1.erase(0, 1);
    if(op2[0] == '+' || op2[0] == '0' || op2[0] == '-')
        op2.erase(0, 1);
    // std::cout << op1 << std::endl;
    // std::cout << op2 << std::endl;
    bool op1_is_greater = op1.size() > op2.size() ? true : false;

    unsigned char carry_flag = 0;
    if(!sub){
        if(op1_is_greater){
            auto o2 = op2.rbegin();
            for (auto o1 = op1.rbegin(); o1 != op1.rend(); o1++){
                if(o2 != op2.rend()){
                    std::cout << *o1 << " " << *o2 << "\n";
                    if(*o1 + *o2 + carry_flag > 'a'){
                        std::cout << *o1+*o2+carry_flag-'\x60' << "\n";
                        result.insert(0,1,*o1+*o2+carry_flag-'a');
                        carry_flag = 1;
                    }
                    else{
                        result.insert(0,1,*o1+*o2);
                        carry_flag = 0;
                    } 
                    o2++;   
                }
            }
        }
    }
}

void run(int argc, char* argv[]){
    int opt = 0;
    int flag_i = 10, flag_o = 10;
    while((opt = getopt(argc, argv, "f:hi:o:")) != -1){
        switch (opt)
        {
        case 'h':
            print_usage();
            exit(0);
        case 'f':
            filename = optarg;
            break;
        case 'i':
            flag_i = static_cast<int>(*optarg - '0');
            std::cout << *optarg << std::endl;
            break;
        case 'o':
            flag_o = static_cast<int>(*optarg - '0');
            std::cout << *optarg << std::endl;
            break;
        case '?':
            std::cerr << RED << "[ERROR]: Invalid option!\n" << RESET;
            print_usage(); 
            exit(1);
        }
    }
    read_operator(filename, oper);
    addition(oper[0], oper[1], result);
    std::cout << "res: " << result ;
}

int main(int argc, char* argv[]){
    run(argc, argv);
}
