#include "main.h"
#include <iostream>
#include "cmd_console_tools.h"
#include <conio.h>
using namespace std;

void start_page()
{
    
}
int main(int argc, char const *argv[])
{
    int cont = 1;
    setconsoleborder(80, 25);
    while (cont)
    {
        setcolor();
        setconsoleborder(80, 25);
        cls();
        cout << "---------------------------------------------" << endl;
        cout << "1.�ڲ����飬������ɳ�ʼ5����" << endl;
        cout << "2.�ڲ����飬�������60%����Ѱ���ƶ�·��" << endl;
        cout << "3.�ڲ����飬������" << endl;
        cout << "4.����n*n�Ŀ�ܣ��޷ָ��ߣ��������ʾ5����" << endl;
        cout << "5.����n*n�Ŀ�ܣ��зָ��ߣ��������ʾ5����" << endl;
        cout << "6.n*n�Ŀ�ܣ�60%����֧����꣬���һ���ƶ�" << endl;
        cout << "7.cmdͼ�ν���������" << endl;
        cout << "8.cmdͼ�ν���������-֧��ͬʱ����������ӷ֣�" << endl;
        cout << "0.�˳�" << endl;
        cout << "---------------------------------------------" << endl;
        cout << "[��ѡ��0-8]" << endl;

        switch (_getch())
        {
        case '1':
            func1();
            break;
        case '2':
            func2();
            break;
        case '3':
            func3();
            break;
        case '4':
            func4();
            break;
        case '5':
            func5();
            break;
        case '6':
            func6();
            break;
        case '7':
            func7();
            break;
        case '8':
            func8();
            break;
        case '0':
            cont = 0;
            break;
        default:
            continue;
        }
    }
    return 0;
}