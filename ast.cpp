
#include <bits/stdc++.h>
using namespace std;

struct Node {
    string val;
    Node *left, *right;

    Node(string v) {
        val = v;
        left = right = NULL;
    }
};

string s;
int pos = 0, reg = 0;

Node* expression();
Node* term();
Node* factor();

Node* factor() {
    if (s[pos] == '(') {
        pos++;
        Node* n = expression();
        pos++;
        return n;
    }

    string x;

    while (pos < s.size() && isalnum(s[pos]))
        x += s[pos++];

    return new Node(x);
}

Node* term() {
    Node* n = factor();

    while (pos < s.size() &&
          (s[pos] == '*' || s[pos] == '/')) {
        string op(1, s[pos++]);
        Node* r = factor();

        Node* t = new Node(op);
        t->left = n;
        t->right = r;
        n = t;
    }

    return n;
}

Node* expression() {
    Node* n = term();

    while (pos < s.size() &&
          (s[pos] == '+' || s[pos] == '-')) {
        string op(1, s[pos++]);
        Node* r = term();

        Node* t = new Node(op);
        t->left = n;
        t->right = r;
        n = t;
    }

    return n;
}

string generate(Node* n) {
    if (!n->left && !n->right) {
        string r = "R" + to_string(reg++);
        cout << "MOV " << r << ", " << n->val << endl;
        return r;
    }

    string a = generate(n->left);
    string b = generate(n->right);

    string r = "R" + to_string(reg++);

    if (n->val == "+")
        cout << "ADD ";
    else if (n->val == "-")
        cout << "SUB ";
    else if (n->val == "*")
        cout << "MUL ";
    else
        cout << "DIV ";

    cout << r << ", " << a << ", " << b << endl;

    return r;
}

int main() {
    string expr, target = "";

    cout << "Enter expression: ";
    cin >> expr;

    int p = expr.find('=');

    if (p != string::npos) {
        target = expr.substr(0, p);
        s = expr.substr(p + 1);
    }
    else
        s = expr;

    Node* root = expression();

    cout << "\nMachine Code:\n";

    string r = generate(root);

    if (target != "")
        cout << "MOV " << target << ", " << r << endl;

    return 0;
}
