// #include <iostream>
// #include <sstream>
// #include <stack>
// #include <vector>
// #include <unordered_map>
// #include <cctype>
// #include <cmath>
// using namespace std;

// bool isOperator(const string &op)
// {
//   return op == "+" || op == "-" || op == "*" || op == "/";
// }

// // Function to check if a token is a number
// bool isNumber(const string &s)
// {
//   for (char c : s)
//   {
//     if (!isdigit(c) && c != '.')
//       return false;
//   }
//   return true;
// }

// // Function to perform arithmetic operations
// double applyOperator(double a, double b, const string &op)
// {
//   if (op == "+")
//     return a + b;
//   if (op == "-")
//     return a - b;
//   if (op == "*")
//     return a * b;
//   if (op == "/")
//     return b != 0 ? a / b : 0; // Avoid division by zero
//   return 0;
// }

// // Function to convert infix expression to postfix
// vector<string> infixToPostfix(const vector<string> &tokens)
// {
//   vector<string> output;
//   stack<string> operators;
//   unordered_map<string, int> precedence = {{"+", 1}, {"-", 1}, {"*", 2}, {"/", 2}};

//   for (const string &token : tokens)
//   {
//     if (isNumber(token) || isalpha(token[0]))
//     {
//       output.push_back(token);
//     }
//     else if (isOperator(token))
//     {
//       while (!operators.empty() && precedence[operators.top()] >= precedence[token])
//       {
//         output.push_back(operators.top());
//         operators.pop();
//       }
//       operators.push(token);
//     }
//   }

//   while (!operators.empty())
//   {
//     output.push_back(operators.top());
//     operators.pop();
//   }

//   return output;
// }

// // Function to evaluate constant expressions in postfix notation
// vector<string> evaluatePostfix(const vector<string> &postfix)
// {
//   stack<double> evalStack;
//   stack<string> exprStack;

//   for (const string &token : postfix)
//   {
//     if (isNumber(token))
//     {
//       evalStack.push(stod(token));
//       exprStack.push(token);
//     }
//     else if (isOperator(token))
//     {
//       string b = exprStack.top();
//       exprStack.pop();
//       string a = exprStack.top();
//       exprStack.pop();

//       if (isNumber(a) && isNumber(b))
//       {
//         double result = applyOperator(stod(a), stod(b), token);
//         evalStack.push(result);
//         exprStack.push(to_string(result));
//       }
//       else
//       {
//         exprStack.push(a + " " + token + " " + b);
//       }
//     }
//     else
//     {
//       exprStack.push(token);
//     }
//   }

//   vector<string> optimizedExpression;
//   stringstream ss(exprStack.top());
//   string temp;
//   while (ss >> temp)
//     optimizedExpression.push_back(temp);
//   return optimizedExpression;
// }

// // Function to parse input expression into tokens
// vector<string> tokenize(const string &expr)
// {
//   vector<string> tokens;
//   stringstream ss(expr);
//   string token;
//   while (ss >> token)
//     tokens.push_back(token);
//   return tokens;
// }

// int main()
// {
//   string input;
//   cout << "Enter an arithmetic expression: ";
//   getline(cin, input);

//   vector<string> tokens = tokenize(input);
//   vector<string> postfix = infixToPostfix(tokens);
//   vector<string> optimizedTokens = evaluatePostfix(postfix);

//   for (const string &token : optimizedTokens)
//   {
//     cout << token << " ";
//   }
//   cout << endl;

//   return 0;
// }

#include <iostream>
#include <vector>
#include <sstream>
#include <string>
#include <cctype>
#include <map>

// Function to check if a string is a number (integer or floating point)
bool isNumber(const std::string &s)
{
  try
  {
    std::stod(s); // Attempt to convert to double
    return true;
  }
  catch (const std::invalid_argument &e)
  {
    return false;
  }
}

// Function to perform constant folding
std::vector<std::string> constantFold(std::vector<std::string> &tokens)
{
  for (size_t i = 0; i + 2 < tokens.size(); ++i)
  {
    // Check if the current token and the next one are numbers and the middle token is an operator
    if (isNumber(tokens[i]) && isNumber(tokens[i + 2]))
    {
      double operand1 = std::stod(tokens[i]);
      double operand2 = std::stod(tokens[i + 2]);
      std::string operator_ = tokens[i + 1];
      double result = 0;

      // Perform the operation based on the operator
      if (operator_ == "+")
      {
        result = operand1 + operand2;
      }
      else if (operator_ == "-")
      {
        result = operand1 - operand2;
      }
      else if (operator_ == "*")
      {
        result = operand1 * operand2;
      }
      else if (operator_ == "/")
      {
        if (operand2 != 0)
        {
          result = operand1 / operand2;
        }
        else
        {
          std::cerr << "Error: Division by zero!" << std::endl;
          return {};
        }
      }

      // Replace the three tokens with the result
      tokens[i] = std::to_string(result);
      tokens.erase(tokens.begin() + i + 1, tokens.begin() + i + 3); // Remove operator and second operand

      // Restart scanning the expression after a successful folding
      i = 0;
    }
  }
  return tokens;
}

// Function to tokenize the input expression into a vector of strings
std::vector<std::string> tokenize(const std::string &expr)
{
  std::vector<std::string> tokens;
  std::string token;
  std::istringstream stream(expr);

  while (stream >> token)
  {
    tokens.push_back(token);
  }

  return tokens;
}

// Function to optimize the expression using constant folding
std::string optimizeExpression(const std::string &expr)
{
  // Tokenize the expression
  std::vector<std::string> tokens = tokenize(expr);

  // Apply constant folding optimization
  tokens = constantFold(tokens);

  // Rebuild the optimized expression
  std::string optimizedExpr = "";
  for (const auto &token : tokens)
  {
    optimizedExpr += token + " ";
  }

  // Remove the trailing space
  optimizedExpr.pop_back();

  return optimizedExpr;
}

int main()
{
  // Test expressions
  std::vector<std::string> expressions = {
      "5 + x - 3 * 2",
      "2 + 3 * 4 - 1",
      "x + (3 * 5) - 2",
      "(22 / 7) * r * r"};

  for (const std::string &expr : expressions)
  {
    std::cout << "Original: " << expr << std::endl;
    std::string optimizedExpr = optimizeExpression(expr);
    std::cout << "Optimized: " << optimizedExpr << std::endl
              << std::endl;
  }

  return 0;
}
