// Copyright 2025 NNTU-CS
#include <string>
#include <map>
#include <cctype>
#include "tstack.h"

int getPriority(char op) {
  switch (op) {
    case '+': return 1;
    case '-': return 1;
    case '*': return 2;
    case '/': return 2;
    default: return 0;
  }
}

bool isOperator(char c) {
  return c == '+' || c == '-' || c == '*' || c == '/';
}

std::string infx2pstfx(const std::string& inf) {
  TStack<char, 100> stack;
  std::string result;
  std::string number;

  for (size_t i = 0; i < inf.length(); ++i) {
    char c = inf[i];

    if (std::isdigit(c)) {
      number += c;
    } else {
      if (!number.empty()) {
        if (!result.empty()) result += ' ';
        result += number;
        number.clear();
      }

      if (c == ' ') {
        continue;
      } else if (c == '(') {
        stack.push(c);
      } else if (c == ')') {
        while (!stack.is_empty() && stack.top() != '(') {
          result += ' ';
          result += stack.pop();
        }
        if (!stack.is_empty() && stack.top() == '(') {
          stack.pop();
        }
      } else if (isOperator(c)) {
        while (!stack.is_empty() && stack.top() != '(' &&
               getPriority(stack.top()) >= getPriority(c)) {
          result += ' ';
          result += stack.pop();
        }
        stack.push(c);
      }
    }
  }

  if (!number.empty()) {
    if (!result.empty()) result += ' ';
    result += number;
  }

  while (!stack.is_empty()) {
    result += ' ';
    result += stack.pop();
  }

  return result;
}

int applyOp(int a, int b, char op) {
  switch (op) {
    case '+': return a + b;
    case '-': return a - b;
    case '*': return a * b;
    case '/': return a / b;
    default: return 0;
  }
}

int eval(const std::string& post) {
  TStack<int, 100> stack;
  std::string number;

  for (size_t i = 0; i < post.length(); ++i) {
    char c = post[i];

    if (std::isdigit(c)) {
      number += c;
    } else if (c == ' ') {
      if (!number.empty()) {
        stack.push(std::stoi(number));
        number.clear();
      }
    } else if (isOperator(c)) {
      if (stack.get_size() >= 2) {
        int b = stack.pop();
        int a = stack.pop();
        stack.push(applyOp(a, b, c));
      }
    }
  }

  if (!number.empty()) {
    stack.push(std::stoi(number));
  }

  return stack.top();
}
