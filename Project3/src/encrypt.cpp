/*
 * @Author: Chihow Yao
 * @Date: 2022-08-29 22:12:11
 * @LastEditors: Chihow Yao yqh994412@gmail.com
 * @LastEditTime: 2022-09-04 22:32:49
 * @Description:
 */

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <map>

std::map<char, char> codeMap{};
std::string clear_txt = "";
std::string cipher_txt = "";

char* buffer_code;
char* buffer_clear;
char* buffer_cipher;


void print_usage(char* argv[]){
    std::cout << "Usage: ./" <<argv[0] << "[OPTION]... [CODEBOOK] [CLEAR_TXT] [CIPHER_TXT]\n"
              << "According to [CODEBOOK] encrypt the [CLEAR_TXT] to [CIPHER_TXT].\n"
              << "Options:\n" 
              << "\t-b  use binary mode encrypt any file\n"
              << std::endl;
}

//overload for dealing binary
int read_bin(const std::string& filename, char* buffer){
    std::ifstream fin;
    fin.open(filename, std::ios::in | std::ios::binary);
    if (!fin.is_open()){
        std::cerr << "[ERROR]: Open " << filename << " failed!\n";
        exit(1);
    }

    // get length of file
    fin.seekg (0, std::ios::end);
    int length = fin.tellg();
    fin.seekg (0, std::ios::beg);
    // allocate memory
    buffer = new char [length];
    // read data as a block:
    fin.read (buffer, length);
    return length;
}

std::string read_file(const std::string& filename){
    std::ifstream fin;
    fin.open(filename, std::ios::in);
    if (!fin.is_open()){
        std::cerr << "[ERROR]: Open " << filename << " failed!\n";
        exit(1);
    }
    
    std::string line, text;
    while(std::getline(fin, line)){
        text += line;
        text += '\n';
    }
    std::cout << filename << " contents:\n" << text << "\n\n";
    return text;
}

void write_file(const std::string& filename, std::string* text){
    std::ofstream ofs(filename);
    if (!ofs.bad())
    {
        ofs << *text ;
        ofs.close();
    }
    std::cout << filename << " contents:\n" << *text << "\n";
}

void print_map(const std::map<char,char>& m)
{ 
// C++11 alternative:
 for (const auto& n : m) {
     std::cout << n.first << " = " << n.second << "; \n";
 }
}

void build_binmap(char* code_buffer, int len){
    std::string code;
    // for(int i=1; i<len; i++){
    //     if(i % 4)
            std::cout << *code_buffer << std::endl;
            // code += code_buffer[i];
        // else{
        //     codeMap[i/4-1] = std::stoi(code);
        //     code = "";
        // }
    // }
}

void build_codemap(const std::string& codebook){
    for(char c = 'a'; c <= 'z'; c++)
        codeMap[c] = codebook[c-'a'];
}

void encrypt_bin(char* buffer_clear, char* buffer_cipher, const int& len){
    buffer_cipher = new char [len];
    
    for (int i = 0; i <= len; i++){
        auto search = codeMap.find(buffer_clear[i]);
        if (search != codeMap.end()){
            buffer_cipher[i] = search->second;
        }
        else
            buffer_cipher[i] = buffer_cipher[i];
    }
}


void encrypt_txt(const std::string& clear_txt, std::string& cipher_txt){
    std::string clear = clear_txt;
    for (int i = 0; i < clear.length(); i++){
        bool is_upper = std::isupper(clear[i]);
        if(is_upper)
            clear[i] = std::tolower(clear[i]);

        auto search = codeMap.find(clear[i]);
        if (search != codeMap.end()){
            if(is_upper)
                cipher_txt += std::toupper(search->second);
            else
                cipher_txt += search->second;
        }
        else
            cipher_txt += clear[i];
    }
}

void run(int argc, char* argv[]){
    if(argc < 4){
        std::cerr << "[ERROR]: Detect argument mismatched.\n";
        print_usage(argv);
        exit(1);
    }

    bool deal_bin = static_cast<std::string>(argv[1]) == "-b" ? true : false;

    if(deal_bin){
        int len_code = read_bin(argv[2], buffer_code);
        build_binmap(buffer_code, len_code);

        int len_clear = read_bin(argv[3], buffer_clear);
        std::cout << len_code << " " << len_clear << "\n";
        // encrypt_bin(buffer_clear, buffer_cipher, len_clear);
        // write_file(argv[4], &cipher_txt);
    }
    else{
        std::string codebook = read_file(argv[1]);
        build_codemap(codebook);

        clear_txt = read_file(argv[2]);

        encrypt_txt(clear_txt, cipher_txt);

        write_file(argv[3], &cipher_txt);
    }
    
}

int main(int argc, char** argv){
    run(argc, argv);
    return 0;
}

