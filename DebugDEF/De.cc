#include<iostream>
#define ADD(x) x
#define BDD(x) (ADD(x)+100)
using namespace std;
int main()
{
    for(int i = 0;i < 100;i++)
    {
        int a = ADD(1);
        cout << BDD(2) <<endl;
    }
    return 0;
}
