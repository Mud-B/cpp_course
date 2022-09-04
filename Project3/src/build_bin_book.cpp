/*
 * @Author: Chihow Yao
 * @Date: 2022-08-29 22:12:11
 * @LastEditors: Chihow Yao yqh994412@gmail.com
 * @LastEditTime: 2022-09-04 20:43:34
 * @Description: Build binary coebook(255-0)
 */

#include <iostream>
#include <fstream>
#include <iomanip>

void write_file(const std::string& filename){
    std::ofstream ofs(filename);
    for(int i=255; i>=0; i--){
        if (!ofs.bad())
            ofs << std::setw(4) << i;
    }
    ofs.close();
}

int main(){
    write_file("bin_codebook.txt");
    return 0;
}

