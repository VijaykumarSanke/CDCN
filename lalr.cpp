
#include <iostream>
#include <vector>
#include <string>
using namespace std;

int action(int s, char ch)
{
    if (s == 0 || s == 2 || s == 3)
    {
        if (ch == 'c') return 3;
        if (ch == 'd') return 4;
    }

    if (s == 1 && ch == '$') return 100;

    if ((s == 4 || s == 6) &&
        (ch == 'c' || ch == 'd' || ch == '$'))
        return (s == 4) ? -3 : -2;

    if (s == 5 && ch == '$') return -1;

    return 0;
}

int goTo(int s, char ch)
{
    if (s == 0 && ch == 'S') return 1;
    if (s == 0 && ch == 'C') return 2;
    if (s == 2 && ch == 'C') return 5;
    if (s == 3 && ch == 'C') return 6;

    return -1;
}

void parse(string input)
{
    input += '$';

    vector<int> st = {0};
    int i = 0;

    cout << "\nParsing Steps:\n";

    while (true)
    {
        int s = st.back();
        char ch = input[i];
        int act = action(s, ch);

        cout << "State: " << s
             << " Input: " << input.substr(i);

        if (act == 100)
        {
            cout << " Action: ACCEPT\n";
            cout << "\nString Accepted!\n";
            return;
        }

        if (act == 0)
        {
            cout << " Action: ERROR\n";
            cout << "\nString Rejected!\n";
            return;
        }

        // Shift
        if (act > 0)
        {
            cout << " Action: s" << act << "\n";
            st.push_back(act);
            i++;
        }

        // Reduce
        else
        {
            if (act == -1)       // R1: S -> CC
            {
                cout << " Action: r1 (S -> CC)\n";
                st.pop_back();
                st.pop_back();
                st.push_back(goTo(st.back(), 'S'));
            }
            else if (act == -2)  // R2: C -> cC
            {
                cout << " Action: r2 (C -> cC)\n";
                st.pop_back();
                st.pop_back();
                st.push_back(goTo(st.back(), 'C'));
            }
            else if (act == -3)  // R3: C -> d
            {
                cout << " Action: r3 (C -> d)\n";
                st.pop_back();
                st.push_back(goTo(st.back(), 'C'));
            }
        }
    }
}

int main()
{
    string input;

    cout << "Grammar:\n";
    cout << "S -> CC\n";
    cout << "C -> cC\n";
    cout << "C -> d\n";

    cout << "\nEnter input string: ";
    cin >> input;

    parse(input);

    return 0;
}
