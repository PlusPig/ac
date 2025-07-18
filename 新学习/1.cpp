#include <iostream>
using namespace std;
int main()
{
    int T, month, day, money;
    cin >> T;
    while (T--)
    {
        cin >> month >> day >> money;
        if (month >= 7 && day > 11)
        {
            cout << "Too late!" << endl;
        }
        else
        {
            if (month < 6)
            {
                if (money < 1800)
                {
                    cout << "Need more!" << endl;
                }
                else if (money == 1800)
                {
                    cout << "Ok!" << endl;
                }
                else
                {
                    cout << "^_^" << endl;
                }
            }
            else if (month == 6 && day <= 20)
            {
                if (money < 1800)
                {
                    cout << "Need more!" << endl;
                }
                else if (money == 1800)
                {
                    cout << "Ok!" << endl;
                }
                else
                {
                    cout << "^_^" << endl;
                }
            }
            else
            {
                if (money < 2000)
                {
                    cout << "Need more!" << endl;
                }
                else if (money == 2000)
                {
                    cout << "Ok!" << endl;
                }
                else
                {
                    cout << "^_^" << endl;
                }
            }
        }
    }
    return 0;
}