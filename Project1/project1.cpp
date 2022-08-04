/*
 * @Author: Chihow Yao
 * @Created Time: 7-29-2022
 * @Last Modified Time: 8-4-2022
 * @Description: Base Calculation within 100
 */
#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>

int v1, v2;         //random oprands 
unsigned char oper; //random operator

int ans;
unsigned char correct_times = 0;
time_t t0, t;       //calculate use of time

struct history  //record every assignment and result
{
    bool is_right = false;
    std::string question = "";
    int right_answer = 0;
    time_t t = 0;
};

void build_asignment() {
    srand((unsigned)(time(NULL)));
    v1 = rand() % 101;
    v2 = rand() % 101;
    oper = rand() % 4;

    switch (oper) {
    case 0:     //addition
        while (v1 + v2 > 100) {   //sum <= 100
            v1 = rand() % 101;
            v2 = rand() % 101;
        }
        std::cout << v1 << " + " << v2 << " = ?" << std::endl;
        break;
    case 1:     //substraction
        while (v1 < v2) {       //rebuild while the result is negative
            v1 = rand() % 101;
            v2 = rand() % 101;
        }
        std::cout << v1 << " - " << v2 << " = ?" << std::endl;
        break;
    case 2:     //multiplication
        while (v1 * v2 > 100) {   //product <= 100
            v1 = rand() % 101;
            v2 = rand() % 101;
        }
        std::cout << v1 << " \u00d7 " << v2 << " = ?" << std::endl;
        break;
    case 3:     //division 
        while (v2 == 0 || v1 % v2 != 0) {   //rebuild if not divisible or zero dividend
            v1 = rand() % 101;
            v2 = rand() % 101;
        }
        std::cout << v1 << " \u00f7 " << v2 << " = ?" << std::endl;
        break;
    }
}

int check_cin() {
    char str[1024];
    std::cin >> str;
    //deal with illegal input
    for (int i = 0; i < 1024; i++)
    {
        if ('\0' == str[i])
            break;
        if (str[i] < '0' || str[i] > '9')
            return -1;
    }
    return std::stoi(str);
}

//face to answer
void deal_user_input(struct history* his) { 
    t0 = time(nullptr);     //get current time
    int ret = check_cin();
    while (ret < 0)
    {
        std::cerr << "[ERROR]：Invalid input! Input again.\n";
        ret = check_cin();
    }
    ans = ret;
    t = time(nullptr) - t0; //calculate answer use of time
    his->t = t;
}

//face to question
int deal_user_input() {     
    std::cout << "How many questions? ";
    int ret = check_cin();
    while (ret < 0)
    {
        std::cerr << "[ERROR]：Invalid input!\nPlease input a positive integer: ";
        ret = check_cin();
    }
    return ret;
}

void check_user_answer(struct history* his) {
    // check answer
    switch (oper) {
    case 0:
        his->right_answer = v1 + v2;
        if (ans == (his->right_answer)) {
            std::cout << "you are right." << std::endl;
            his->is_right = true;
            correct_times++;
            break;
        }
        std::cout << "you are wrong." << std::endl;
        his->question = std::to_string(v1) + " + " + std::to_string(v2) + " = ";
        his->is_right = false;
        break;
    case 1:
        his->right_answer = v1 - v2;
        if (ans == (his->right_answer)) {
            std::cout << "you are right." << std::endl;
            his->is_right = true;
            correct_times++;
            break;
        }
        std::cout << "you are wrong." << std::endl;
        his->is_right = false;
        his->question = std::to_string(v1) + " - " + std::to_string(v2) + " = ";
        break;
    case 2:
        his->right_answer = v1 * v2;
        if (ans == (his->right_answer)) {
            std::cout << "you are right." << std::endl;
            his->is_right = true;
            correct_times++;
            break;
        }
        std::cout << "you are wrong." << std::endl;
        his->is_right = false;
        his->question = std::to_string(v1) + " \u00d7 " + std::to_string(v2) + " = ";
        break;
    case 3:
        his->right_answer = v1 / v2;
        if (ans == (his->right_answer)) {
            std::cout << "you are right." << std::endl;
            his->is_right = true;
            correct_times++;
            break;
        }
        std::cout << "you are wrong." << std::endl;
        his->is_right = false;
        his->question = std::to_string(v1) + " \u00f7 " + std::to_string(v2) + " = ";
        break;
    }
}

void show_result(struct history* his, const int& n) {
    his -= n;       //point to first history
    int num = n;
    int right_n = 0, wrong_n = 0;
    time_t sum_t = 0, min_t = his->t;

    //deal with answer result
    while (num--) {
        sum_t += his->t;
        if (his->t < min_t)
            min_t = his->t;
        if (his->is_right)
            right_n++;
        else
            wrong_n++;
        his++;
    }
    std::cout << "\n\nTotol number of questions: " << n << ", Right: " << right_n
        << ", Wrong: " << wrong_n << std::endl;
    std::cout << "Totol use of time: " << sum_t << "s, Average: " << sum_t / n
        << "s, Minimal: " << min_t << "s" << std::endl;

    num = n;
    his -= n;   //point to first history
    std::cout << "THE RIGHT ANSWER:" << std::endl;
    //show right answer
    while (num--) {
        if (!his->is_right) {   //if user answer is wrong
            std::cout << his->question << his->right_answer << std::endl;
        }
        his++;
    }
    std::cout << "BYE!" << std::endl;
}

int main()
{
    int N = 10;         //Number of question
    N = deal_user_input();
    struct history* p_h = new struct history[N]();

    for (int i = 0; i < N; i++) {
        build_asignment();
        deal_user_input(p_h);
        check_user_answer(p_h++);
    }
    show_result(p_h, N);

    p_h -= N;       //point to started position
    delete[] p_h;   //and destory the object
    return 0;
}
