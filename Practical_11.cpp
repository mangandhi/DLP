// #include <iostream>
// #include <string>
// #include <vector>
// #include <sstream>
// #include <stack>
// #include <algorithm>

// using namespace std;

// // Structure to represent a quadruple
// struct Quadruple
// {
//   string op;
//   string arg1;
//   string arg2;
//   string result;
// };

// // Function to get the precedence of an operator
// int getPrecedence(const string &op)
// {
//   if (op == "*" || op == "/")
//     return 2;
//   if (op == "+" || op == "-")
//     return 1;
//   return 0;
// }

// // Function to convert infix expression to postfix using Shunting Yard Algorithm
// vector<string> infixToPostfix(const string &expression)
// {
//   vector<string> postfix;
//   stack<string> operators;
//   stringstream ss(expression);
//   string token;

//   while (ss >> token)
//   {
//     if (isdigit(token[0]))
//     {
//       postfix.push_back(token);
//     }
//     else if (token == "(")
//     {
//       operators.push(token);
//     }
//     else if (token == ")")
//     {
//       while (!operators.empty() && operators.top() != "(")
//       {
//         postfix.push_back(operators.top());
//         operators.pop();
//       }
//       operators.pop(); // Pop the "("
//     }
//     else if (token == "+" || token == "-" || token == "*" || token == "/")
//     {
//       while (!operators.empty() && getPrecedence(token) <= getPrecedence(operators.top()))
//       {
//         postfix.push_back(operators.top());
//         operators.pop();
//       }
//       operators.push(token);
//     }
//   }

//   while (!operators.empty())
//   {
//     postfix.push_back(operators.top());
//     operators.pop();
//   }

//   return postfix;
// }

// // Function to generate quadruples from a postfix expression
// vector<Quadruple> generateQuadruples(const vector<string> &postfix)
// {
//   vector<Quadruple> quadruples;
//   stack<string> operands;
//   int tempVarCount = 1;

//   for (const string &token : postfix)
//   {
//     if (isdigit(token[0]))
//     {
//       operands.push(token);
//     }
//     else if (token == "+" || token == "-" || token == "*" || token == "/")
//     {
//       string operand2 = operands.top();
//       operands.pop();
//       string operand1 = operands.top();
//       operands.pop();

//       Quadruple quad;
//       quad.op = token;
//       quad.arg1 = operand1;
//       quad.arg2 = operand2;
//       quad.result = "t" + to_string(tempVarCount++);
//       quadruples.push_back(quad);

//       operands.push(quad.result);
//     }
//   }

//   return quadruples;
// }

// int main()
// {
//   string expression;
//   cout << "Enter an arithmetic expression: ";
//   getline(cin, expression);

//   // Convert infix to postfix
//   vector<string> postfix = infixToPostfix(expression);

//   // Generate quadruples from postfix
//   vector<Quadruple> quadruples = generateQuadruples(postfix);

//   // Print the quadruple table
//   cout << "Operator\tOperand 1\tOperand 2\tResult\n";
//   for (const auto &quad : quadruples)
//   {
//     cout << quad.op << "\t\t" << quad.arg1 << "\t\t" << quad.arg2 << "\t\t" << quad.result << endl;
//   }

//   return 0;
// }

#include <iostream>
#include <sstream>
#include <cctype>
#include <stack>
#include <vector>

using namespace std;

enum Token
{
  NUM,
  PLUS,
  MINUS,
  MUL,
  DIV,
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
  int temp_count;
  vector<vector<string>> quadruples; // To store the quadruples

  Parser(Lexer lexer) : lexer(lexer), temp_count(0)
  {
    current_token = lexer.getNextToken();
  }

  void parse()
  {
    expression();
    if (current_token != END)
    {
      cout << "Invalid expression" << endl;
    }
    else
    {
      printQuadruples();
    }
  }

private:
  void expression()
  {
    term();
    while (current_token == PLUS || current_token == MINUS)
    {
      Token op = current_token;
      current_token = lexer.getNextToken();
      term();
      string temp_var = generateTempVar();
      string op_str = (op == PLUS) ? "+" : "-";
      string left_operand = popOperand();
      string right_operand = popOperand();
      generateQuadruple(op_str, left_operand, right_operand, temp_var);
      pushOperand(temp_var);
    }
  }

  void term()
  {
    factor();
    while (current_token == MUL || current_token == DIV)
    {
      Token op = current_token;
      current_token = lexer.getNextToken();
      factor();
      string temp_var = generateTempVar();
      string op_str = (op == MUL) ? "*" : "/";
      string left_operand = popOperand();
      string right_operand = popOperand();
      generateQuadruple(op_str, left_operand, right_operand, temp_var);
      pushOperand(temp_var);
    }
  }

  void factor()
  {
    if (current_token == NUM)
    {
      string num = to_string(lexer.getNumValue());
      current_token = lexer.getNextToken();
      pushOperand(num);
    }
    else if (current_token == LPAREN)
    {
      current_token = lexer.getNextToken();
      expression();
      if (current_token == RPAREN)
      {
        current_token = lexer.getNextToken();
      }
      else
      {
        cout << "Invalid expression" << endl;
        exit(0);
      }
    }
    else
    {
      cout << "Invalid expression" << endl;
      exit(0);
    }
  }

  string generateTempVar()
  {
    return "t" + to_string(temp_count++);
  }

  void pushOperand(string operand)
  {
    operand_stack.push(operand);
  }

  string popOperand()
  {
    if (!operand_stack.empty())
    {
      string operand = operand_stack.top();
      operand_stack.pop();
      return operand;
    }
    return "";
  }

  void generateQuadruple(string op, string operand1, string operand2, string result)
  {
    quadruples.push_back({op, operand1, operand2, result});
  }

  void printQuadruples()
  {
    cout << "Operator   Operand1   Operand2   Result\n";
    for (auto &quadruple : quadruples)
    {
      cout << quadruple[0] << "         " << quadruple[1] << "         " << quadruple[2] << "         " << quadruple[3] << "\n";
    }
  }

  stack<string> operand_stack; // Stack to store operands
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
