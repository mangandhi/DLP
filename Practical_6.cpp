// #include <iostream>
// #include <string>

// using namespace std;

// class RecursiveDescentParser
// {
// private:
//   string input;
//   int index; // Keeps track of parsing position

// public:
//   RecursiveDescentParser(string str) : input(str), index(0) {}

//   bool parse()
//   {
//     return S() && index == input.length();
//   }

// private:
//   bool S()
//   {
//     // S → ( L ) | a
//     if (match('a'))
//     {
//       return true;
//     }
//     else if (match('('))
//     {
//       if (L() && match(')'))
//       {
//         return true;
//       }
//     }
//     return false;
//   }

//   bool L()
//   {
//     // L → S L’
//     if (S())
//     {
//       return L_prime();
//     }
//     return false;
//   }

//   bool L_prime()
//   {
//     // L’ → , S L’ | ϵ
//     if (match(','))
//     {
//       if (S())
//       {
//         return L_prime();
//       }
//       return false;
//     }
//     return true; // ϵ (epsilon) case
//   }

//   bool match(char expected)
//   {
//     // Check if the current character matches `expected` and move forward
//     if (index < input.length() && input[index] == expected)
//     {
//       index++;
//       return true;
//     }
//     return false;
//   }
// };

// // Main function to take input from CLI
// int main()
// {
//   string userInput;
//   cout << "Enter a string to validate: ";
//   cin >> userInput;

//   RecursiveDescentParser parser(userInput);

//   if (parser.parse())
//   {
//     cout << "Valid string\n";
//   }
//   else
//   {
//     cout << "Invalid string\n";
//   }

//   return 0;
// }

#include <bits/stdc++.h>
using namespace std;

string input;
int pos = 0;

// Function declarations
bool S();
bool L();
bool LPrime();

bool match(char expected)
{
  if (pos < input.length() && input[pos] == expected)
  {
    pos++;
    return true;
  }
  return false;
}

// S → ( L ) | a
bool S()
{
  if (match('a'))
  {
    return true;
  }
  else if (match('('))
  {
    if (L() && match(')'))
    {
      return true;
    }
  }
  return false;
}

// L → S L'
bool L()
{
  if (S())
  {
    return LPrime();
  }
  return false;
}

// L' → , S L' | ε
bool LPrime()
{
  if (match(','))
  {
    if (S())
    {
      return LPrime();
    }
    return false;
  }
  return true; // ε (empty) case
}

int main()
{
  cout << "Enter input string: ";
  getline(cin, input);

  // Remove spaces from input
  input.erase(remove(input.begin(), input.end(), ' '), input.end());

  pos = 0;
  if (S() && pos == input.length())
  {
    cout << "Valid string" << endl;
  }
  else
  {
    cout << "Invalid string" << endl;
  }

  return 0;
}
