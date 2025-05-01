#include <bits/stdc++.h>
using namespace std;

bool checkValidation(int &symbols, int &states, int &initState, int &noOfcceptingState, int &acceptingState, vector<vector<int>> &matrix, string &inputStr)
{
  vector<int> str(inputStr.length());
  for (int i = 0; i < str.size(); i++)
  {
    str[i] = inputStr[i] - 'a';
  }
  int k = initState;
  int i = 0;
  while (i < str.size())
  {
    if (k <= matrix.size() && str[i] < matrix[k].size())
    {
      k = matrix[k - 1][str[i]];
    }
    else
    {
      break;
    }
    i++;
  }
  if (k == acceptingState && i == str.size())
  {
    return 1;
  }
  return 0;
}

int main()
{
  int symbols;
  cout << "Number of input symbols : ";
  cin >> symbols;
  vector<char> inpSymbol(symbols);
  cout << "Input Symbols : ";
  for (int i = 0; i < inpSymbol.size(); i++)
  {
    inpSymbol[i] = i + 'a';
    cout << inpSymbol[i] << " ";
  }
  cout << endl;
  int states;
  cout << "Enter number of states : ";
  cin >> states;

  int initState;
  cout << "Initial state : ";
  cin >> initState;

  int noOfcceptingState;
  cout << "number of accepting states : ";
  cin >> noOfcceptingState;

  int acceptingState;
  cout << "Accepting states : ";
  cin >> acceptingState;

  vector<vector<int>> matrix(states, vector<int>(symbols));
  cout << "Transition Table : " << endl;
  for (int i = 0; i < matrix.size(); i++)
  {
    for (int j = 0; j < matrix[0].size(); j++)
    {
      cout << i + 1 << " to " << j << " -> ";
      cin >> matrix[i][j];
    }
    cout << endl;
  }
  string inputStr;
  cout << "Enter String : ";
  cin >> inputStr;
  int ans = checkValidation(symbols, states, initState, noOfcceptingState, acceptingState, matrix, inputStr);
  if (ans == 1)
  {
    cout << "Valid String" << endl;
  }
  else
  {
    cout << "Invalid String" << endl;
  }
  return 0;
}