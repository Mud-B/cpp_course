#	作业思路
##	Feature
1.	实现了一百以内的加减乘除运算
2.	支持用户自定义题目数量
3.	支持对非法输入的检查，如字符串的输入处理
4.	具备历史记录，打印最终结果与用时情况

##	核心函数
1.	build_asignment():  
随机生成符合计算规则的计算题
2.	deal_user_input():  
处理用户输入的答案，并记录用时
3.	check_user_answer():    
检查答案是否正确，并记录
4.	show_result():  
打印最终结果
5.	history结构体:  
历史记录，保存每个问题答题情况

#	编译环境
1.	Windows10 下使用Microsoft Visual Studio Community 2019 集成开发环境
采用ISO C++14 Standard编译通过
2.	Ubuntu20.04 下使用g++ 9.4.0版本
采用c++11、c++14、c++17、c++2a Standard编译通过

#	运行截图
![Console_snapshot](./run.png)