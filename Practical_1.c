#include <stdio.h>
#include <stdbool.h>

bool checkValidation(const char *str)
{
  int i = 0;

  if (str == NULL)
    return false;

  while (str[i] == 'a')
  {
    i++;
  }

  if (str[i] == 'b' && str[i + 1] == 'b' && str[i + 2] == '\0')
  {
    return true;
  }

  return false;
}

int main()
{
  char str[100];

  printf("Enter a string: ");
  scanf("%99s", str);

  bool ans = checkValidation(str);

  printf("Validation result: %s\n", ans ? "Valid" : "Invalid");

  return 0;
}

// #include <stdio.h>
// #include <string.h>

// int isValid(const char *str)
// {
//   int i = 0;

//   // Match zero or more 'a's
//   while (str[i] == 'a')
//   {
//     i++;
//   }

//   // After 'a's, there must be exactly two 'b's and nothing else
//   if (str[i] == 'b' && str[i + 1] == 'b' && str[i + 2] == '\0')
//   {
//     return 1; // Valid
//   }

//   return 0; // Invalid
// }

// int main()
// {
//   char input[100];

//   printf("Enter a string: ");
//   fgets(input, sizeof(input), stdin);

//   // Remove newline character if present
//   size_t len = strlen(input);
//   if (len > 0 && input[len - 1] == '\n')
//   {
//     input[len - 1] = '\0';
//   }

//   if (isValid(input))
//   {
//     printf("Valid string\n");
//   }
//   else
//   {
//     printf("Invalid string\n");
//   }

//   return 0;
// }
