// Copyright 2021 NNTU-CS
#include <string>
#include <map>
#include "tstack.h"

int getPrior(char op) {
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
  }
}

std::string infx2pstfx(std::string inf) {
  TStack <char, 100> st;
  std::string pstfx;
  bool isnum = false;
  for (int i = 0; i < inf.length(); i++) {
    if (isdigit(inf[i])) {
      if (!isnum) {
        pstfx.push_back(' ');
      }
      isnum = true;
      pstfx.push_back(inf[i]);
      continue;
    } else {
      isnum = false;
    }
    if (inf[i] == ')') {
      while (true) {
      if (st.get() != '(') {
        pstfx.push_back(' ');
        pstfx.push_back(st.get());
        st.pop();
      } else {
        st.pop();
        break;
      }
      }
      continue;
    }
    if (inf[i] == '+' || inf[i] == '-' || inf[i] == '*' || inf[i] == '/' || inf[i] == '(' ) {
      
      if (st.isEmpty()) {
         st.push(inf[i]);
         continue;
       }
      if (getPrior(inf[i]) > getPrior(st.get())) {
        st.push(inf[i]);
        continue;
      }
      if (getPrior(inf[i]) == 0) {
        st.push(inf[i]);
        continue;
      }
      if (getPrior(inf[i]) <= getPrior(st.get())) {
        while (true) {
          if (getPrior(inf[i]) <= getPrior(st.get())) {
            pstfx.push_back(' ');
            pstfx.push_back(st.get());
            st.pop();
          } else {
            st.push(inf[i]);
            break;
          }
        }
        continue;
      }
    }
  }
  while (true) {
    if (!(st.isEmpty())) {
      pstfx.push_back(' ');
      pstfx.push_back(st.get());
      st.pop();
    } else {
      break;
    }
  }
  return pstfx.substr(1);
}

bool is_digits(const std::string &str)
{
  return str.find_first_not_of("0123456789") == std::string::npos;
}

int eval(std::string pref) {
  TStack <int, 100> st;
  std::string apstr = "";
  std::string pere = pref;
  if (pref[pref.length()-1]!=' '){
    pere.push_back(' ');
  }
  int op1, op2;
  for (int i = 0; i < pere.length(); i++) {
    if (pere[i] != ' ') {
      apstr.push_back(pere[i]);
    } else {
      if (is_digits(apstr)){
        st.push(stoi(apstr));
      } else {
        op2 = st.get();
        st.pop();
        op1 = st.get();
        st.pop();
        switch (apstr[0]) {
        case '-':
          st.push(op1 - op2);
          break;
        case '+':
          st.push(op1 + op2);
          break;
        case '*':
          st.push(op1 * op2);
          break;
        case '/':
          st.push(op1 / op2);
          break;
        }
      }
      apstr = "";
    }
  }
  return st.get();
}
