
#include <bits/stdc++.h>
using namespace std;

int temp = 1;

int precedence(char op) {
    if (op == '*' || op == '/')
        return 2;
    if (op == '+' || op == '-')
        return 1;
    return 0;
}

int main() {
    string expr;
    stack<string> operand;
    stack<char> op;

    cout << "Enter the expression: ";
    cin >> expr;

    string result = "";

    if (expr.find('=') != string::npos) {
        int pos = expr.find('=');
        result = expr.substr(0, pos);
        expr = expr.substr(pos + 1);
    }

    cout << "\nThree Address Code:\n";

    for (int i = 0; i < expr.length(); i++) {
        char ch = expr[i];

        if (isalnum(ch)) {
            string s = "";

            while (i < expr.length() && isalnum(expr[i]))
                s += expr[i++];

            operand.push(s);
            i--;
        }

        else if (ch == '(') {
            op.push(ch);
        }

        else if (ch == ')') {
            while (!op.empty() && op.top() != '(') {
                if (operand.size() < 2) {
                    cout << "Invalid expression";
                    return 0;
                }

                string b = operand.top();
                operand.pop();

                string a = operand.top();
                operand.pop();

                char oper = op.top();
                op.pop();

                string t = "t" + to_string(temp++);

                cout << t << " = " << a << " " << oper << " " << b << endl;
                operand.push(t);
            }

            if (op.empty()) {
                cout << "Invalid expression";
                return 0;
            }

            op.pop();
        }

        else if (ch == '+' || ch == '-' || ch == '*' || ch == '/') {
            while (!op.empty() && op.top() != '(' &&
                   precedence(op.top()) >= precedence(ch)) {

                if (operand.size() < 2) {
                    cout << "Invalid expression";
                    return 0;
                }

                string b = operand.top();
                operand.pop();

                string a = operand.top();
                operand.pop();

                char oper = op.top();
                op.pop();

                string t = "t" + to_string(temp++);

                cout << t << " = " << a << " " << oper << " " << b << endl;
                operand.push(t);
            }

            op.push(ch);
        }

        else {
            cout << "Invalid character";
            return 0;
        }
    }

    while (!op.empty()) {
        if (operand.size() < 2 || op.top() == '(') {
            cout << "Invalid expression";
            return 0;
        }

        string b = operand.top();
        operand.pop();

        string a = operand.top();
        operand.pop();

        char oper = op.top();
        op.pop();

        string t = "t" + to_string(temp++);

        cout << t << " = " << a << " " << oper << " " << b << endl;
        operand.push(t);
    }

    if (operand.size() != 1) {
        cout << "Invalid expression";
        return 0;
    }

    if (result != "")
        cout << result << " = " << operand.top() << endl;
    else
        cout << "Result = " << operand.top() << endl;

    return 0;
}


