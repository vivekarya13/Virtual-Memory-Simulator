#include<iostream>
#include<thread>
using namespace std;
void function1()
{
    for(int i =0;i<100;i++);
    cout<<" + ";
}
void function2()
{
    for(int i =0;i<100;i++);
    cout<<" - ";
}
int main()
{
    std::thread work1(function1);
    std::thread work2(function2);
    system("pause>nul");
}