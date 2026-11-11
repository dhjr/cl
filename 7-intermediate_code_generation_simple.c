
#include <stdio.h>
#include <string.h>
#include <ctype.h>

char stack[100];
int top = -1;
int temp = 1;
char postfix[100];

int precedence(char c)
{
    if (c == '*' || c == '/')
        return 2;

    if (c == '+' || c == '-')
        return 1;

    return 0;
}

void infixtopostfix(char infix[])
{
    int n = strlen(infix);
    int j = 0;

    for (int i = 0; i < n; i++)
    {
        char c = infix[i];

        if (isalnum(c))
        {
            postfix[j++] = c;
        }


        else if (c == '(')
        {
            stack[++top] = c;
        }


        else if (c == ')')
        {
            while (top != -1 && stack[top] != '(')
            {
                postfix[j++] = stack[top--];
            }

            top--;  // Remove opening parenthesis
        }
        else
        {
            while (top != -1 &&
                   stack[top] != '(' &&
                   precedence(stack[top]) >= precedence(c))
            {
                postfix[j++] = stack[top--];
            }

            stack[++top] = c;
        }
    }

    while (top != -1)
        postfix[j++] = stack[top--];

    postfix[j] = '\0';
}

void generatecode(char post[])
{
    int n = strlen(post);
    char op[100][10];
    int t = -1;

    char right[10];
    char left[10];
    char result[10];

    for (int i = 0; i < n; i++)
    {
        char c = post[i];

        if (isalnum(c))
        {
            op[++t][0] = c;
            op[t][1] = '\0';
        }
        else
        {
            strcpy(right, op[t--]);
            strcpy(left, op[t--]);

            sprintf(result, "t%d", temp++);

            printf("%s = %s %c %s\n",
                   result, left, c, right);

            strcpy(op[++t], result);
        }
    }
}

int main()
{
    char infix[100];

    printf("Enter an expression: ");
    scanf("%s", infix);

    infixtopostfix(infix);

    generatecode(postfix);

    return 0;
}
