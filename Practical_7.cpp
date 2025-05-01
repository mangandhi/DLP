// #include <iostream>
// #include <map>
// #include <set>
// #include <vector>

// using namespace std;

// map<char, vector<string>> grammar;
// map<char, set<char>> firstSets;
// map<char, set<char>> followSets;

// // Function to compute First Set
// void computeFirst(char nonTerminal)
// {
//   if (!firstSets[nonTerminal].empty())
//     return;

//   for (const string &production : grammar[nonTerminal])
//   {
//     bool epsilonPresent = true;

//     for (char c : production)
//     {
//       if (isupper(c))
//       {
//         computeFirst(c);
//         for (char first : firstSets[c])
//         {
//           if (first != 'ε')
//             firstSets[nonTerminal].insert(first);
//           else
//             epsilonPresent = true;
//         }
//       }
//       else
//       {
//         firstSets[nonTerminal].insert(c);
//         epsilonPresent = false;
//         break;
//       }

//       if (!epsilonPresent)
//         break;
//     }

//     if (epsilonPresent)
//       firstSets[nonTerminal].insert('ε');
//   }
// }

// // Function to compute Follow Set
// void computeFollow(char nonTerminal)
// {
//   if (!followSets[nonTerminal].empty())
//     return;

//   if (nonTerminal == 'S')
//     followSets[nonTerminal].insert('$'); // Start symbol gets $

//   for (const auto &pair : grammar) // Fix structured binding
//   {
//     char lhs = pair.first;
//     const vector<string> &productions = pair.second;

//     for (const string &production : productions)
//     {
//       for (size_t i = 0; i < production.length(); i++)
//       {
//         if (production[i] == nonTerminal)
//         {
//           bool epsilonFound = false;
//           if (i + 1 < production.length())
//           {
//             char nextSymbol = production[i + 1];
//             if (isupper(nextSymbol))
//             {
//               for (char first : firstSets[nextSymbol])
//               {
//                 if (first != 'ε')
//                   followSets[nonTerminal].insert(first);
//                 else
//                   epsilonFound = true;
//               }
//             }
//             else
//             {
//               followSets[nonTerminal].insert(nextSymbol);
//             }
//           }
//           else
//           {
//             epsilonFound = true;
//           }

//           if (epsilonFound)
//           {
//             computeFollow(lhs);
//             followSets[nonTerminal].insert(followSets[lhs].begin(), followSets[lhs].end());
//           }
//         }
//       }
//     }
//   }
// }

// int main()
// {
//   int n;
//   cout << "Enter number of productions: ";
//   cin >> n;
//   cin.ignore();

//   cout << "Enter grammar (e.g., S=AB|a):\n";
//   for (int i = 0; i < n; i++)
//   {
//     char lhs;
//     string rhs;
//     cin >> lhs;
//     cin.ignore();
//     getline(cin, rhs);

//     size_t pos = 0;
//     while ((pos = rhs.find('|')) != string::npos)
//     {
//       grammar[lhs].push_back(rhs.substr(0, pos));
//       rhs.erase(0, pos + 1);
//     }
//     grammar[lhs].push_back(rhs);
//   }

//   for (const auto &pair : grammar) // Fix structured binding
//     computeFirst(pair.first);
//   for (const auto &pair : grammar) // Fix structured binding
//     computeFollow(pair.first);

//   // Output First Sets
//   cout << "\nFirst Sets:\n";
//   for (const auto &pair : firstSets)
//   {
//     cout << "First(" << pair.first << ") = { ";
//     for (char first : pair.second)
//       cout << first << " ";
//     cout << "}\n";
//   }

//   // Output Follow Sets
//   cout << "\nFollow Sets:\n";
//   for (const auto &pair : followSets)
//   {
//     cout << "Follow(" << pair.first << ") = { ";
//     for (char follow : pair.second)
//       cout << follow << " ";
//     cout << "}\n";
//   }

//   return 0;
// }
#include <iostream>
#include <set>
#include <map>
#include <string>
#include <vector>
using namespace std;

map<char, set<char>> first, follow;
map<char, bool> visitedFirst, visitedFollow;

map<char, vector<string>> productions = {
    {'S', {"ABC", "D"}},
    {'A', {"a", "#"}},
    {'B', {"b", "#"}},
    {'C', {"(S)", "c"}},
    {'D', {"AC"}}};

// FIRST set computation
set<char> computeFirst(char symbol)
{
  if (first[symbol].size() > 0)
    return first[symbol];
  if (!isupper(symbol))
    return {symbol}; // terminal or ε

  vector<string> rules = productions[symbol];
  for (int j = 0; j < rules.size(); ++j)
  {
    string production = rules[j];
    for (int i = 0; i < production.size(); ++i)
    {
      char ch = production[i];
      set<char> temp = computeFirst(ch);
      for (char t : temp)
      {
        if (t != '#')
          first[symbol].insert(t);
      }
      if (temp.find('#') == temp.end())
        break;
      if (i == production.size() - 1)
        first[symbol].insert('#');
    }
  }
  return first[symbol];
}

// FOLLOW set computation
void computeFollow(char symbol)
{
  if (visitedFollow[symbol])
    return;
  visitedFollow[symbol] = true;

  for (map<char, vector<string>>::iterator it = productions.begin(); it != productions.end(); ++it)
  {
    char lhs = it->first;
    vector<string> rules = it->second;

    for (int r = 0; r < rules.size(); ++r)
    {
      string rhs = rules[r];
      for (int i = 0; i < rhs.size(); ++i)
      {
        if (rhs[i] == symbol)
        {
          // Case: symbol is not last
          if (i + 1 < rhs.size())
          {
            char next = rhs[i + 1];
            set<char> firstNext = computeFirst(next);
            for (char ch : firstNext)
            {
              if (ch != '#')
                follow[symbol].insert(ch);
            }
            if (firstNext.find('#') != firstNext.end())
            {
              computeFollow(lhs);
              follow[symbol].insert(follow[lhs].begin(), follow[lhs].end());
            }
          }
          else
          {
            // symbol at end
            computeFollow(lhs);
            follow[symbol].insert(follow[lhs].begin(), follow[lhs].end());
          }
        }
      }
    }
  }
}

void displaySet(string name, char var, set<char> s)
{
  cout << name << "(" << var << ") = { ";
  for (set<char>::iterator it = s.begin(); it != s.end(); ++it)
  {
    if (*it == '#')
      cout << "ε, ";
    else if (*it == '$')
      cout << "$, ";
    else
      cout << *it << ", ";
  }
  cout << "\b\b }" << endl;
}

int main()
{
  // Compute FIRST sets
  for (map<char, vector<string>>::iterator it = productions.begin(); it != productions.end(); ++it)
  {
    computeFirst(it->first);
  }

  // Set initial Follow(S) = {$}
  follow['S'].insert('$');

  // Compute FOLLOW sets
  for (map<char, vector<string>>::iterator it = productions.begin(); it != productions.end(); ++it)
  {
    computeFollow(it->first);
  }

  // Display results
  cout << "== FIRST Sets ==" << endl;
  for (map<char, set<char>>::iterator it = first.begin(); it != first.end(); ++it)
  {
    displaySet("First", it->first, it->second);
  }

  cout << "\n== FOLLOW Sets ==" << endl;
  for (map<char, set<char>>::iterator it = follow.begin(); it != follow.end(); ++it)
  {
    displaySet("Follow", it->first, it->second);
  }

  return 0;
}
