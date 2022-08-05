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
#include <chrono>

//question relevant
int oprand1, oprand2;   //random oprands 
unsigned char oper;     //random operator
enum Diffculty
{
    EASY = 0,
    NORMAL = 1,
    HARD = 2
}diff;
int max_range = 100;

//answer relevant
int ans;
unsigned char correct_times = 0;

struct history  //record every assignment and result
{
    bool is_right = false;
    std::string question = "";
    int right_answer = 0;
    double t = 0;
};

void build_asignment() {
    srand((unsigned)(time(NULL)));
    oprand1 = rand() % (max_range+1);
    oprand2 = rand() % (max_range+1);
    switch (diff) {
    case EASY:      //only addition and substraction
        oper = rand() % 2; break;
    case NORMAL:    //add multiplication and division
        oper = rand() % 4; break;
    case HARD:
        oper = rand() % 4; break;
    default:
        std::cerr << "Difficulty not set!" << std::endl;
        break;
    } 

    switch (oper) {
    case 0:     //addition
        while (oprand1 + oprand2 > max_range) {   //sum should less than max_range
            oprand1 = rand() % (max_range + 1);
            oprand2 = rand() % (max_range + 1);
        }
        std::cout << oprand1 << " + " << oprand2 << " = ?" << std::endl;
        break;
    case 1:     //substraction
        while (oprand1 < oprand2) {       //rebuild while the result is negative
            oprand1 = rand() % (max_range + 1);
            oprand2 = rand() % (max_range + 1);
        }
        std::cout << oprand1 << " - " << oprand2 << " = ?" << std::endl;
        break;
    case 2:     //multiplication
        while (oprand1 * oprand2 > max_range) {   //product should less than max_range
            oprand1 = rand() % (max_range + 1);
            oprand2 = rand() % (max_range + 1);
        }
        std::cout << oprand1 << " \u00d7 " << oprand2 << " = ?" << std::endl;
        break;
    case 3:     //division 
        while (oprand2 == 0 || oprand1 % oprand2 != 0) {   //rebuild if not divisible or zero dividend
            oprand1 = rand() % (max_range + 1);
            oprand2 = rand() % (max_range + 1);
        }
        std::cout << oprand1 << " \u00f7 " << oprand2 << " = ?" << std::endl;
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
    std::chrono::time_point<std::chrono::steady_clock> start, end;
    start = std::chrono::steady_clock::now();     //get current time
    int ret = check_cin();
    while (ret < 0)
    {
        std::cerr << "[ERROR]：Invalid input! Input again.\n";
        ret = check_cin();
    }
    ans = ret;
    end = std::chrono::steady_clock::now();
    std::chrono::duration<double> d = end - start;    //calculate answer use of time(sec)
    his->t = d.count();
}

//face to question
int deal_user_input() {     
    // GET DIFFICULTY CONFIG
    std::cout << "Choose difficuly(0:easy, 1:normal, 2:hard): ";
    int difficuly = check_cin();
    while (difficuly < 0 || difficuly > 2)
    {
        std::cerr << "[ERROR]：Invalid input!\nPlease input a number between 0~2: ";
        difficuly = check_cin();
    }
    switch (difficuly)
    {
    case 0: 
        diff = EASY; break;
    case 1: 
        diff = NORMAL; break;
    case 2: 
        diff = HARD; 
        std::cout << "HARD MODE, choose max generation range(>100): "; 
        max_range = check_cin(); 
        while (max_range < 100)
        {
            std::cerr << "[ERROR]：Invalid input!\nPlease input a number > 100: ";
            max_range = check_cin();
        }break;
    default: break;
    }

    // GET NUM OF QUESTIONS
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
        his->right_answer = oprand1 + oprand2;
        if (ans == (his->right_answer)) {
            std::cout << "you are right." << std::endl;
            his->is_right = true;
            correct_times++;
            break;
        }
        std::cout << "you are wrong." << std::endl;
        his->question = std::to_string(oprand1) + " + " + std::to_string(oprand2) + " = ";
        his->is_right = false;
        break;
    case 1:
        his->right_answer = oprand1 - oprand2;
        if (ans == (his->right_answer)) {
            std::cout << "you are right." << std::endl;
            his->is_right = true;
            correct_times++;
            break;
        }
        std::cout << "you are wrong." << std::endl;
        his->is_right = false;
        his->question = std::to_string(oprand1) + " - " + std::to_string(oprand2) + " = ";
        break;
    case 2:
        his->right_answer = oprand1 * oprand2;
        if (ans == (his->right_answer)) {
            std::cout << "you are right." << std::endl;
            his->is_right = true;
            correct_times++;
            break;
        }
        std::cout << "you are wrong." << std::endl;
        his->is_right = false;
        his->question = std::to_string(oprand1) + " \u00d7 " + std::to_string(oprand2) + " = ";
        break;
    case 3:
        his->right_answer = oprand1 / oprand2;
        if (ans == (his->right_answer)) {
            std::cout << "you are right." << std::endl;
            his->is_right = true;
            correct_times++;
            break;
        }
        std::cout << "you are wrong." << std::endl;
        his->is_right = false;
        his->question = std::to_string(oprand1) + " \u00f7 " + std::to_string(oprand2) + " = ";
        break;
    }
}

void show_result(struct history* his, const int& n) {
    his -= n;       //point to first history
    int num = n;
    int ans_score = 0, timecost_score = 0, final_score = 0;
    int right_n = 0, wrong_n = 0;
    double sum_t = 0, min_t = his->t;

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

    //calculate score
    ans_score = 100.f / n * right_n;
    if ((sum_t / n) < 2)
        timecost_score = 100;
    else
        timecost_score = -12.5f * (sum_t / n) + 125;
    final_score = (ans_score * 7) / 10 + (timecost_score * 3) / 10;

    //print result
    std::cout << "\n\nFinal score: " << final_score << ", timecost score: " << timecost_score
        << ", answer score: " << ans_score << std::endl;
    std::cout << "Totol number of questions: " << n << ", Right: " << right_n
        << ", Wrong: " << wrong_n << std::endl;
    std::cout << "Totol use of time: " << sum_t << "s, Average: " << sum_t / n
        << "s, Minimal: " << min_t << "s" << std::endl;
    num = n;
    his -= n;   //point to first history
    if(wrong_n)
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

    p_h -= N;       //point to first position
    delete[] p_h;   //and destory the object
    return 0;
}
