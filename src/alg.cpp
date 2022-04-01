// Copyright 2021 NNTU-CS
#include <string>
#include <map>
#include "tstack.h"

int prior(char op) {
    switch (op) {
    case '(': return 0;
    case ')': return 1;
    case '-': return 2;
    case '+': return 2;
    case '*': return 3;
    case '/': return 3;
    case ' ': return -1;
    default: return -2;
    }
}

int calc(int x, int y, char ch) {
    switch (ch) {
    case '+':
        return y + x;
    case '-':
        return y - x;
    case '*':
        return y * x;
    case '/':
        return y / x;
    default:
        ;
    }
}

string infx2pstfx(string inf) {
    TStack<char, 100> st1;
    string post = "";
    for (int iter = 0; iter < inf.size(); iter++) {
        if (prior(inf[iter]) == -2) {
            if (iter < inf.size() && prior(inf[iter + 1]) == -2) {
                while (iter < inf.size() && prior(inf[iter]) == -2) {
                    post += inf[iter++];
                }
                post += ' ';
            }
            else {
                post += inf[iter];
                post += ' ';
            }
            continue;
        }
        if (inf[iter] == '(' || prior(inf[iter]) > prior(st1.get()) || st1.isEmpty()) {
            st1.push(inf[iter]);
        }
        else if (prior(inf[iter]) <= prior(st1.get())) {
            while (prior(st1.get()) > 1) {
                post += st1.get();
                post += ' ';
                st1.pop();
            }
            st1.push(inf[iter]);
        }
        if (inf[iter] == ')') {
            while ((st1.get() != '(')) {
                post += st1.get();
                post += ' ';
                st1.pop();
            }
            st1.pop();
        }
    }
    while (!st1.isEmpty()) {
        if (prior(st1.get()) > 1) {
            post += st1.get();
            post += ' ';
        }
        st1.pop();
    }
    post.erase(post.size() - 1);
    return post;
}

int eval(string post) {
    TStack<int, 100> st2;
    int iter = 0;
    for (int i = 0; i < post.size(); i++) {
        iter = i;
        string temp = "";
        while (prior(post[iter]) == -2) {
            temp += post[iter];
            iter++;
        }
        i = iter;
        if (prior(post[i]) > 1) {
            int x = st2.get();
            st2.pop();
            int y = st2.get();
            st2.pop();
            st2.push(calc(x, y, post[i]));
        }
        if (temp != "") {
            st2.push(stoi(temp));
        }
    }
    return st2.get();
}
