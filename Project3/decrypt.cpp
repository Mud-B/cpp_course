/*
 * @Author: Chihow Yao
 * @Date: 2022-08-29 22:12:11
 * @LastEditors: Chihow Yao yqh994412@gmail.com
 * @LastEditTime: 2022-09-02 16:55:07
 * @Description:
 */

#include <iostream>
#include <fstream>
#include <string>
#include <map>
std::string code = "";
std::string clear_txt = "";
std::string cipher_txt = "";


void print_usage(){
    std::cout << "Usage: encrypt [OPTION]... [CODEBOOK] [CLEAR_TXT] [CIPHER_TXT]\n"
              << "According to [CODEBOOK] encrypt the [CLEAR_TXT] to [CIPHER_TXT].\n"
              << "Options:\n" 
              << "\t-b  use binary mode encrypt any file\n"
              << std::endl;
}

void read_file(const std::string& filenmae, std::string* text){
    std::ifstream fin;
    fin.open(filenmae, std::ios::in);
    if (!fin.is_open()){
        std::cerr << "[ERROR]: Open file failed!\n";
        exit(1);
    }

    std::string line;
    while(std::getline(fin, line)){
        *text += line;
        *text += '\n';
    }
        
    std::cout << filenmae << " contents:\n" << *text << "\n\n";
}

void write_file(const std::string& filenmae, std::string* text){
    std::ofstream ofs(filenmae);
    if (!ofs.bad())
    {
        ofs << *text ;
        ofs.close();
    }
    std::cout << filenmae << " contents:\n" << *text << "\n";
}

void decrypt_txt(std::string& clear, const std::string& code,const std::string& cipher){
    //build reverse codebook
    std::map<char, char> codebook{};
    for(char c = 'a'; c <= 'z'; c++)
        codebook[code[c-'a']] = c;

    //decryption
    for (int i = 0; i < cipher.length(); i++){
        auto search = codebook.find(cipher[i]);
        if (search != codebook.end())
            clear += search->second;
        else
            clear += cipher[i];
    }
}

void run(int argc, char* argv[]){
    if(argc != 4){
        std::cerr << "[ERROR]: Detect argument mismatched.\n";
        print_usage();
        exit(1);
    }
    for(int i=0; i <= argc; i++){
        switch (i)
        {
        case 0:     //nothing 2 do with prog name
            break;  
        case 1:     //codebook
            read_file(argv[i], &code);
            break;
        case 2:     //ciphertext
            read_file(argv[i], &cipher_txt);
            break;
        case 3:     
            decrypt_txt(clear_txt, code, cipher_txt);
            write_file(argv[i], &clear_txt);
            break;
        default: break;
        }
    }
}

int main(int argc, char** argv){
    run(argc, argv);
    return 0;
}

