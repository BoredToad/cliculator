#include "cliculator.h"
#include <algorithm>
#include <cctype>
#include <cmath>
#include <map>
#include <regex>
#include <stack>

bool valid_char(char c) {
  bool valid = false;
  for (char op : "()+-*/[^") {
    if (c == op) {
      valid = true;
    }
  }
  return valid;
}

std::stack<std::string> tokenize_expression(std::string expression) {
  std::reverse(expression.begin(), expression.end());
  std::stack<std::string> tokens;
  std::string number;
  int parantheses_count = 0;

  for (char c : expression) {
    if (isdigit(c) || c == '.') {
      number.insert(0, std::string(1, c));
      continue;
    }

    if (!valid_char(c)) {
      tokens.push("E-Fuckd char");
      return tokens;
    }

    // I have some cursed parentheses multiplication shidd here
    if (number != "") {
      if (!tokens.empty())
        if (tokens.top() == "(")
          tokens.push("*");

      tokens.push(number);
      number = "";

      if (c == ')')
        tokens.push("*");
    }

    if (c == ')')
      parantheses_count++;
    if (c == '(') {
      if (parantheses_count < 1) {
        tokens.push("E-Unclosed parentheses");
        return tokens;
      }

      parantheses_count--;
    }

    tokens.push(std::string(1, c));
  }
  // some depressing redundency
  if (number != "") {
    if (tokens.top() == "(")
      tokens.push("*");
    tokens.push(number);
  }

  if (parantheses_count > 0) {
    tokens.push("E-Unopened parantheses");
  }
  return tokens;
}

void popstack(std::stack<std::string> *operation_stack,
              std::stack<double> *number_stack) {
  char operation = operation_stack->top()[0];
  operation_stack->pop();

  if (operation == '_')
    return;

  double b = number_stack->top();
  number_stack->pop();
  double a = number_stack->top();
  number_stack->pop();

  switch (operation) {
  case '+':
    number_stack->push(a + b);
    break;
  case '-':
    number_stack->push(a - b);
    break;
  case '*':
    number_stack->push(a * b);
    break;
  case '/':
    number_stack->push(a / b);
    break;
  case '^':
    number_stack->push(pow(a, b));
    break;
  }
}

std::string evaluate(std::stack<std::string> tokens) {
  std::map<std::string, int> operation_precedence{
      {"+", 2}, {"-", 2}, {"/", 3}, {"*", 3}, {"^", 4}};
  std::stack<double> number_stack;
  std::stack<std::string> operation_stack;

  // I have no fucking idea what I'm doing
  while (!tokens.empty()) {
    std::string token = tokens.top();
    tokens.pop();

    if (std::regex_match(token, std::regex("-?[0-9]+([\.][0-9]+)?"))) {
      number_stack.push(std::stod(token));
      continue;
    }

    if (operation_stack.empty() || token == "(") {
      operation_stack.push(token);
      continue;
    }

    if (token == ")") {
      while (operation_stack.top() != "(") {
        popstack(&operation_stack, &number_stack);
      }
      operation_stack.pop();
      continue;
    }

    while (!operation_stack.empty() && operation_stack.top() != "(" &&
           ((operation_precedence[operation_stack.top()] >
                 operation_precedence[token] &&
             token != "^"))) {
      popstack(&operation_stack, &number_stack);
    }

    operation_stack.push(token);
  }

  while (!operation_stack.empty())
    popstack(&operation_stack, &number_stack);

  return std::to_string(number_stack.top());
}

void print_tokens(std::stack<std::string> tokens) {
  while (!tokens.empty()) {
    std::cout << tokens.top() << "|";
    tokens.pop();
  }
  std::cout << "  ->\n";
}

std::string cliculator::calculate(std::string expression) {
  expression.erase(remove_if(expression.begin(), expression.end(), isspace),
                   expression.end());
  std::cout << expression << " ->\n";

  std::stack<std::string> tokens = tokenize_expression(expression);

  if (tokens.top()[0] == 'E')
    return tokens.top().erase(0, 2);

  print_tokens(tokens);

  if (tokens.empty()) {
    return "nothing to evaluate";
  }

  return evaluate(tokens);
}
