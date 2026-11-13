
#include <iostream>
#include <string>
#include <cctype>
using namespace std;

string s;
int i = 0;

void E();
void E1();
void T();
void T1();
void F();

void E()
{
    T();
    E1();
}

void E1()
{
    if (i < s.length() && s[i] == '+')
    {
        i++;
        T();
        E1();
    }
}

void T()
{
    F();
    T1();
}

void T1()
{
    if (i < s.length() && s[i] == '*')
    {
        i++;
        F();
        T1();
    }
}

void F()
{
    if (i < s.length() && isalnum(s[i]))
    {
        while (i < s.length() && isalnum(s[i]))
            i++;
    }
    else if (i < s.length() && s[i] == '(')
    {
        i++;
        E();

        if (i < s.length() && s[i] == ')')
            i++;
        else
            throw 1;
    }
    else
        throw 1;
}

int main()
{
    cout << "Enter expression: ";
    cin >> s;

    try
    {
        E();

        if (i == s.length())
            cout << "Valid Expression";
        else
            cout << "Invalid Expression";
    }
    catch (...)
    {
        cout << "Invalid Expression";
    }

    return 0;
}
