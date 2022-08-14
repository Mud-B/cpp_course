#include <fstream>
#include <string>
#include <numeric>
#include <unistd.h>     //for parse short option
#include <iostream>

std::string filename = "sample.txt";
std::string oper[2];

void print_usage(){
    std::cout << "Usage: add [OPTION]... [FILE]...\n"
              << "Deal with long integer addition from file input.\n"
              << "Options:\n" 
              << "\t-i  set input file path\n"
              << "\t-h  give this help list\n";
}

bool read_operator(const std::string& fn, std::string* op){
    std::ifstream fin;
    fin.open(fn, std::ios::in);
    if (!fin.is_open()){
        std::cout << "[ERROR]: Open file failed!\n";
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
    while((opt = getopt(argc, argv, "hi:")) != -1){
        switch (opt)
        {
        case 'h':
            print_usage();
            exit(0);
            break;
        case 'i':
            filename = optarg;
            break;
        }
    }
    read_operator(filename, oper);
}

int main(int argc, char* argv[]){
    run(argc, argv);
}
