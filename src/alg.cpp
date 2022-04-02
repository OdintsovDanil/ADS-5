// Copyright 2021 NNTU-CS
#include <string>
#include <map>
#include "tstack.h"

int prior(char op) {
    switch (op) {
    case '(':
        return 0;
    case ')':
        return 1;
    case '+':
        return 2;
    case '-':
        return 2;
    case '*':
        return 3;
    case '/':
        return 3;
    case ' ':
        return -2;
    default:
        return -1;
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
        if (x != 0)
            return y / x;
    default:
        return 0;
    }
}

std::string infx2pstfx(std::string inf) {
    TStack<char, 100> st1;
    std::string post = "";
    for (int iter = 0; iter < inf.size(); iter++) {
        if (prior(inf[iter]) == -1) {
            if (iter < inf.size() && prior(inf[iter + 1]) == -1) {
                while (iter < inf.size() && prior(inf[iter]) == -1) {
                    post += inf[iter++];
                }
                post += ' ';
            } else {
                post += inf[iter];
                post += ' ';
            }
            continue;
        }
        int pri = prior(inf[iter]);
        if (pri == 0 || pri > prior(st1.get()) || st1.isEmpty()) {
            st1.push(inf[iter]);
        } else {
            if (prior(inf[iter]) <= prior(st1.get())) {
                while (prior(st1.get()) > 1) {
                    post += st1.get();
                    post += ' ';
                    st1.pop();
                }
                st1.push(inf[iter]);
            } else if (prior(inf[iter]) == 1) {
                while (prior(st1.get()) != 0) {
                    post += st1.get();
                    post += ' ';
                    st1.pop();
                }
                st1.pop();
            }
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

int eval(std::string pref) {
    TStack<int, 100> st2;
    int iter = 0;
    for (int i = 0; i < pref.size(); i++) {
        iter = i;
        std::string temp = "";
        while (prior(pref[iter]) == -1) {
            temp += pref[iter];
            iter++;
        }
        i = iter;
        if (prior(pref[iter]) > 1) {
            int x = st2.get();
            st2.pop();
            int y = st2.get();
            st2.pop();
            st2.push(calc(x, y, pref[i]));
        }
        if (temp != "") {
            st2.push(std::stoi(temp));
        }
    }
    return st2.get();
}
