// #include <iostream>
// #include <string>
// #include <vector>
// #include <map>
// #include <set>
// #include <stack>

// using namespace std;

// // Structure to represent a production rule
// struct Production
// {
//   char lhs;
//   string rhs;
// };

// // Function to check if a grammar is LL(1) based on the parsing table
// bool isLL1(const map<pair<char, char>, int> &parsingTable)
// {
//   for (auto const &entry : parsingTable)
//   {
//     auto const &key = entry.first;
//     auto const &val = entry.second;
//     // If there are multiple production rules for the same non-terminal and terminal, it's not LL(1)
//     if (val > 1)
//     {
//       return false;
//     }
//   }
//   return true;
// }

// // Function to validate a string using the predictive parsing table
// bool validateString(const string &input, const map<pair<char, char>, int> &parsingTable,
//                     const map<char, vector<Production>> &grammar, char startSymbol)
// {
//   stack<char> parseStack;
//   parseStack.push('$');         // End marker
//   parseStack.push(startSymbol); // Start symbol

//   int inputIndex = 0;
//   char currentInputSymbol = inputIndex < input.length() ? input[inputIndex] : '$';

//   while (!parseStack.empty())
//   {
//     char topStack = parseStack.top();

//     if (isupper(topStack))
//     { // Non-terminal
//       auto it = parsingTable.find({topStack, currentInputSymbol});
//       if (it != parsingTable.end())
//       {
//         parseStack.pop();
//         int productionIndex = it->second;

//         // Get the production rule from the grammar
//         auto &productions = grammar.at(topStack);
//         string rhs = productions[productionIndex].rhs;

//         // Push the production rule onto the stack in reverse order
//         for (int i = rhs.length() - 1; i >= 0; i--)
//         {
//           if (rhs[i] != 'ε')
//           {
//             parseStack.push(rhs[i]);
//           }
//         }
//       }
//       else
//       {
//         return false; // No entry in parsing table, invalid string
//       }
//     }
//     else if (topStack == currentInputSymbol)
//     { // Terminal
//       if (topStack == '$')
//       {
//         return true; // End of input and stack, valid string
//       }
//       parseStack.pop();
//       inputIndex++;
//       currentInputSymbol = inputIndex < input.length() ? input[inputIndex] : '$';
//     }
//     else
//     {
//       return false; // Mismatch between stack top and input symbol, invalid string
//     }
//   }

//   return false; // Stack is empty before end of input, invalid string
// }

// int main()
// {
//   // Define the grammar (example grammar)
//   map<char, vector<Production>> grammar = {
//       {'S', {{'S', "iEtS"}, {'S', "iEtSeS"}, {'S', "a"}}},
//       {'E', {{'E', "b"}}}};

//   // Define First and Follow sets (example sets)
//   map<char, set<char>> firstSets = {
//       {'S', {'i', 'a'}},
//       {'E', {'b'}}};

//   map<char, set<char>> followSets = {
//       {'S', {'$', 'e'}},
//       {'E', {'t'}}};

//   // Construct the predictive parsing table
//   map<pair<char, char>, int> parsingTable;
//   for (auto const &entry : grammar)
//   {
//     char nonTerminal = entry.first;
//     auto const &productions = entry.second;
//     for (size_t i = 0; i < productions.size(); ++i)
//     {
//       Production production = productions[i];
//       string rhs = production.rhs;

//       // Iterate through the first set of the RHS
//       bool canDeriveEpsilon = false;
//       for (char terminal : firstSets[nonTerminal])
//       {
//         if (terminal != 'ε')
//         {
//           parsingTable[{nonTerminal, terminal}] = (int)i;
//         }
//         else
//         {
//           canDeriveEpsilon = true;
//         }
//       }

//       // If the RHS can derive epsilon, add the follow set of the LHS to the parsing table
//       if (canDeriveEpsilon)
//       {
//         for (char terminal : followSets[nonTerminal])
//         {
//           parsingTable[{nonTerminal, terminal}] = (int)i;
//         }
//       }
//     }
//   }

//   // Print the parsing table
//   cout << "Predictive Parsing Table:\n";
//   for (auto const &entry : parsingTable)
//   {
//     cout << "M[" << entry.first.first << ", " << entry.first.second << "] = " << entry.second << endl;
//   }

//   // Check if the grammar is LL(1)
//   if (isLL1(parsingTable))
//   {
//     cout << "\nThe grammar is LL(1).\n";
//   }
//   else
//   {
//     cout << "\nThe grammar is not LL(1).\n";
//   }

//   // Validate an input string
//   string inputString;
//   cout << "\nEnter a string to validate: ";
//   cin >> inputString;

//   if (validateString(inputString, parsingTable, grammar, 'S'))
//   {
//     cout << "Valid string\n";
//   }
//   else
//   {
//     cout << "Invalid string\n";
//   }

//   return 0;
// }

#include <iostream>
#include <set>
#include <map>
#include <string>
#include <vector>
#include <stack>
using namespace std;

map<char, set<char>> first, follow;
map<char, vector<string>> productions;
map<char, map<char, string>> parsingTable;

// Helper function to compute First set
set<char> computeFirst(char symbol)
{
  set<char> result;
  if (isupper(symbol))
  {
    for (const string &prod : productions[symbol])
    {
      if (prod[0] == symbol)
        continue;
      if (prod[0] != '#')
      { // non-epsilon
        result.insert(prod[0]);
      }
    }
  }
  return result;
}

// Helper function to compute Follow set
void computeFollow(char symbol)
{
  // Your existing logic for Follow computation goes here.
}

// Construct parsing table
void constructParsingTable()
{
  // Use First and Follow sets to build the parsing table
  for (const auto &prod : productions)
  {
    char nonTerminal = prod.first;
    for (const string &rhs : prod.second)
    {
      set<char> firstSet = computeFirst(rhs[0]);
      for (char terminal : firstSet)
      {
        parsingTable[nonTerminal][terminal] = rhs;
      }
    }
  }
}

// LL(1) grammar validation
bool isLL1()
{
  for (const auto &row : parsingTable)
  {
    for (const auto &entry : row.second)
    {
      if (entry.second != "")
      {
        cout << "Grammar is not LL(1)\n";
        return false;
      }
    }
  }
  cout << "Grammar is LL(1)\n";
  return true;
}

// String validation
bool validateString(const string &input)
{
  stack<char> parseStack;
  parseStack.push('S'); // Start symbol of the grammar
  int idx = 0;

  while (!parseStack.empty() && idx < input.length())
  {
    char top = parseStack.top();
    parseStack.pop();

    if (isupper(top))
    {
      // Non-terminal, use the parsing table
      char terminal = input[idx];
      if (parsingTable[top].count(terminal))
      {
        string production = parsingTable[top][terminal];
        for (int i = production.size() - 1; i >= 0; i--)
        {
          parseStack.push(production[i]);
        }
      }
      else
      {
        return false;
      }
    }
    else if (top == input[idx])
    {
      idx++;
    }
    else
    {
      return false;
    }
  }

  return (idx == input.length());
}

int main()
{
  // Fill productions (example grammar)
  productions['S'] = {"aB", "(S)"};
  productions['B'] = {"b", "c"};

  // Fill First and Follow sets
  first['S'] = computeFirst('S');
  first['B'] = computeFirst('B');

  // Construct parsing table
  constructParsingTable();

  // Validate if grammar is LL(1)
  if (isLL1())
  {
    string input;
    cout << "Enter string to validate: ";
    cin >> input;

    if (validateString(input))
    {
      cout << "Valid string\n";
    }
    else
    {
      cout << "Invalid string\n";
    }
  }

  return 0;
}
