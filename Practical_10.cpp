// #include <iostream>
// #include <string>
// #include <stack>
// #include <cmath>
// #include <cctype>
// #include <stdexcept>

// using namespace std;

// // Function to check if a character is a digit
// bool isDigit(char c)
// {
//   return c >= '0' && c <= '9';
// }

// // Function to check if a character is an operator
// bool isOperator(char c)
// {
//   return c == '+' || c == '-' || c == '*' || c == '/' || c == '^';
// }

// // Function to get the precedence of an operator
// int getPrecedence(char op)
// {
//   if (op == '^')
//     return 3;
//   else if (op == '*' || op == '/')
//     return 2;
//   else if (op == '+' || op == '-')
//     return 1;
//   else
//     return 0;
// }

// // Function to convert infix expression to postfix expression
// string infixToPostfix(const string &infix)
// {
//   string postfix = "";
//   stack<char> operators;

//   for (char c : infix)
//   {
//     if (isspace(c))
//       continue; // Skip whitespace
//     if (isdigit(c))
//     {
//       postfix += c;
//     }
//     else if (c == '(')
//     {
//       operators.push(c);
//     }
//     else if (c == ')')
//     {
//       while (!operators.empty() && operators.top() != '(')
//       {
//         postfix += operators.top();
//         operators.pop();
//       }
//       if (!operators.empty() && operators.top() == '(')
//       {
//         operators.pop(); // Pop the '('
//       }
//       else
//       {
//         throw invalid_argument("Invalid expression: Unmatched parenthesis");
//       }
//     }
//     else if (isOperator(c))
//     {
//       while (!operators.empty() && getPrecedence(c) <= getPrecedence(operators.top()))
//       {
//         postfix += operators.top();
//         operators.pop();
//       }
//       operators.push(c);
//     }
//     else
//     {
//       throw invalid_argument("Invalid character in expression");
//     }
//   }

//   while (!operators.empty())
//   {
//     if (operators.top() == '(')
//     {
//       throw invalid_argument("Invalid expression: Unmatched parenthesis");
//     }
//     postfix += operators.top();
//     operators.pop();
//   }

//   return postfix;
// }

// // Function to evaluate a postfix expression
// double evaluatePostfix(const string &postfix)
// {
//   stack<double> operands;

//   for (char c : postfix)
//   {
//     if (isdigit(c))
//     {
//       operands.push(c - '0'); // Convert char to double
//     }
//     else if (isOperator(c))
//     {
//       if (operands.size() < 2)
//       {
//         throw invalid_argument("Invalid expression: Insufficient operands for operator");
//       }
//       double operand2 = operands.top();
//       operands.pop();
//       double operand1 = operands.top();
//       operands.pop();

//       switch (c)
//       {
//       case '+':
//         operands.push(operand1 + operand2);
//         break;
//       case '-':
//         operands.push(operand1 - operand2);
//         break;
//       case '*':
//         operands.push(operand1 * operand2);
//         break;
//       case '/':
//         if (operand2 == 0)
//         {
//           throw invalid_argument("Division by zero");
//         }
//         operands.push(operand1 / operand2);
//         break;
//       case '^':
//         operands.push(pow(operand1, operand2));
//         break;
//       }
//     }
//   }

//   if (operands.size() == 1)
//   {
//     return operands.top();
//   }
//   else
//   {
//     throw invalid_argument("Invalid expression: Too many operands");
//   }
// }

// int main()
// {
//   string expression;
//   cout << "Enter an arithmetic expression: ";
//   getline(cin, expression);

//   try
//   {
//     string postfix = infixToPostfix(expression);
//     double result = evaluatePostfix(postfix);
//     cout << "Result: " << result << endl;
//   }
//   catch (const invalid_argument &e)
//   {
//     cout << "Invalid expression: " << e.what() << endl;
//   }

//   return 0;
// }

#include <iostream>
#include <sstream>
#include <cctype>
#include <stack>
#include <cmath>

using namespace std;

enum Token
{
  NUM,
  PLUS,
  MINUS,
  MUL,
  DIV,
  EXP,
  LPAREN,
  RPAREN,
  END,
  INVALID
};

struct Lexer
{
  string input;
  size_t pos;
  char current_char;

  Lexer(const string &input) : input(input), pos(0), current_char(input[0]) {}

  void advance()
  {
    pos++;
    if (pos < input.length())
    {
      current_char = input[pos];
    }
    else
    {
      current_char = '\0'; // End of input
    }
  }

  Token getNextToken()
  {
    while (current_char != '\0' && isspace(current_char))
    {
      advance();
    }
    if (isdigit(current_char))
    {
      return NUM;
    }
    if (current_char == '+')
    {
      advance();
      return PLUS;
    }
    if (current_char == '-')
    {
      advance();
      return MINUS;
    }
    if (current_char == '*')
    {
      advance();
      return MUL;
    }
    if (current_char == '/')
    {
      advance();
      return DIV;
    }
    if (current_char == '^')
    {
      advance();
      return EXP;
    }
    if (current_char == '(')
    {
      advance();
      return LPAREN;
    }
    if (current_char == ')')
    {
      advance();
      return RPAREN;
    }
    if (current_char == '\0')
    {
      return END;
    }
    return INVALID;
  }

  double getNumValue()
  {
    double result = 0;
    while (isdigit(current_char))
    {
      result = result * 10 + (current_char - '0');
      advance();
    }
    return result;
  }
};

class Parser
{
public:
  Lexer lexer;
  Token current_token;
  double result;

  Parser(Lexer lexer) : lexer(lexer)
  {
    current_token = lexer.getNextToken();
  }

  void parse()
  {
    result = expression();
    if (current_token != END)
    {
      cout << "Invalid expression" << endl;
    }
    else
    {
      cout << result << endl;
    }
  }

private:
  double expression()
  {
    double left = term();
    while (current_token == PLUS || current_token == MINUS)
    {
      Token op = current_token;
      current_token = lexer.getNextToken();
      double right = term();
      if (op == PLUS)
      {
        left += right;
      }
      else if (op == MINUS)
      {
        left -= right;
      }
    }
    return left;
  }

  double term()
  {
    double left = factor();
    while (current_token == MUL || current_token == DIV)
    {
      Token op = current_token;
      current_token = lexer.getNextToken();
      double right = factor();
      if (op == MUL)
      {
        left *= right;
      }
      else if (op == DIV)
      {
        if (right != 0)
        {
          left /= right;
        }
        else
        {
          cout << "Invalid expression" << endl;
          exit(0); // Division by zero error
        }
      }
    }
    return left;
  }

  double factor()
  {
    double left = exponentiation();
    return left;
  }

  double exponentiation()
  {
    double left = primary();
    while (current_token == EXP)
    {
      current_token = lexer.getNextToken();
      double right = primary();
      left = pow(left, right); // Exponentiation
    }
    return left;
  }

  double primary()
  {
    double result;
    if (current_token == NUM)
    {
      result = lexer.getNumValue();
      current_token = lexer.getNextToken();
    }
    else if (current_token == LPAREN)
    {
      current_token = lexer.getNextToken();
      result = expression();
      if (current_token == RPAREN)
      {
        current_token = lexer.getNextToken();
      }
      else
      {
        cout << "Invalid expression" << endl;
        exit(0); // Mismatched parentheses
      }
    }
    else
    {
      cout << "Invalid expression" << endl;
      exit(0); // Unexpected token
    }
    return result;
  }
};

int main()
{
  string input;
  cout << "Enter arithmetic expression: ";
  getline(cin, input);

  Lexer lexer(input);
  Parser parser(lexer);
  parser.parse();

  return 0;
}
