
#include <iostream>
#include <map>
#include <set>
#include <string>
using namespace std;

map<char, string> grammar;
map<char, set<char>> first, follow;

void findFirst(char ch)
{
    for (char p : grammar[ch])
    {
        if (!isupper(p))
            first[ch].insert(p);
        else
        {
            findFirst(p);

            for (char x : first[p])
                if (x != '#')
                    first[ch].insert(x);

            if (first[p].count('#'))
                first[ch].insert('#');
        }
    }
}

void findFollow()
{
    follow['E'].insert('$');

    for (int k = 0; k < 5; k++)
    {
        for (auto g : grammar)
        {
            char nt = g.first;
            string prod = g.second;

            for (int i = 0; i < prod.length(); i++)
            {
                char ch = prod[i];

                if (isupper(ch))
                {
                    if (i + 1 < prod.length())
                    {
                        char next = prod[i + 1];

                        if (!isupper(next))
                            follow[ch].insert(next);
                        else
                        {
                            for (char x : first[next])
                                if (x != '#')
                                    follow[ch].insert(x);

                            if (first[next].count('#'))
                                for (char x : follow[nt])
                                    follow[ch].insert(x);
                        }
                    }
                    else
                    {
                        for (char x : follow[nt])
                            follow[ch].insert(x);
                    }
                }
            }
        }
    }
}

int main()
{
    grammar['E'] = "TR";
    grammar['R'] = "+TR#";
    grammar['T'] = "FY";
    grammar['Y'] = "*FY#";
    grammar['F'] = "(E)i";

    for (auto g : grammar)
        findFirst(g.first);

    findFollow();

    cout << "FIRST:\n";
    for (auto g : grammar)
    {
        cout << "FIRST(" << g.first << ") = { ";
        for (char x : first[g.first])
            cout << x << " ";
        cout << "}\n";
    }

    cout << "\nFOLLOW:\n";
    for (auto g : grammar)
    {
        cout << "FOLLOW(" << g.first << ") = { ";
        for (char x : follow[g.first])
            cout << x << " ";
        cout << "}\n";
    }

    return 0;
}
