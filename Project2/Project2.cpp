#include <fstream>
#include <string>
#include <numeric>
#include <unistd.h>     //for parse short option
#include <iostream>

#define RED "\033[31m"
#define RESET "\033[0m"

std::string filename = "sample.txt";
std::string oper[2];

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
}

int main(int argc, char* argv[]){
    run(argc, argv);
}
