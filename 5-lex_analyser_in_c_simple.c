
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char keywords[][10] = {
    "char", "int", "if", "else",
    "while", "for", "do"
};

#define KEYWORD_COUNT (sizeof(keywords) / sizeof(keywords[0]))

int isKeyword(char word[])
{
    for (int i = 0; i < KEYWORD_COUNT; i++)
    {
        if (strcmp(keywords[i], word) == 0)
            return 1;
    }

    return 0;
}

int main()
{
    FILE *fp = fopen("5-input.c", "r");

    if (fp == NULL)
    {
        printf("File cannot be opened\n");
        return EXIT_FAILURE;
    }

    int ch;
    char word[100];

    while ((ch = fgetc(fp)) != EOF)
    {
        if (isspace((unsigned char)ch))
            continue;

        // Handle comments and division operator
        else if (ch == '/')
        {
            int next = fgetc(fp);

            // Single-line comment
            if (next == '/')
            {
                while ((ch = fgetc(fp)) != EOF && ch != '\n')
                    ;

                continue;
            }

            // Multi-line comment
            else if (next == '*')
            {
                int prev = '\0';
                int closed = 0;

                while ((ch = fgetc(fp)) != EOF)
                {
                    if (prev == '*' && ch == '/')
                    {
                        closed = 1;
                        break;
                    }

                    prev = ch;
                }

                if (!closed)
                    printf("Unterminated block comment\n");

                continue;
            }

            // Division operator
            else
            {
                if (next != EOF)
                    ungetc(next, fp);

                printf("/ : Operator\n");
                continue;
            }
        }

        // Handle keywords and identifiers
        else if (isalpha((unsigned char)ch) || ch == '_')
        {
            int i = 0;

            word[i++] = ch;

            while ((ch = fgetc(fp)) != EOF &&
                   (isalnum((unsigned char)ch) || ch == '_'))
            {
                if (i < sizeof(word) - 1)
                    word[i++] = ch;
            }

            word[i] = '\0';

            if (ch != EOF)
                ungetc(ch, fp);

            if (isKeyword(word))
                printf("%s : Keyword\n", word);
            else
                printf("%s : Identifier\n", word);
        }

        // Handle numbers
        else if (isdigit((unsigned char)ch))
        {
            int i = 0;

            word[i++] = ch;

            while ((ch = fgetc(fp)) != EOF &&
                   isdigit((unsigned char)ch))
            {
                if (i < sizeof(word) - 1)
                    word[i++] = ch;
            }

            word[i] = '\0';

            if (ch != EOF)
                ungetc(ch, fp);

            printf("%s : Number\n", word);
        }

        // Handle arithmetic operators
        else if (ch == '+' || ch == '-' || ch == '*')
        {
            printf("%c : Operator\n", ch);
        }

        // Handle special symbols
        else if (ch == ';' || ch == ',' ||
                 ch == '(' || ch == ')' ||
                 ch == '{' || ch == '}' ||
                 ch == '[' || ch == ']')
        {
            printf("%c : SpecialSymbol\n", ch);
        }
    }

    fclose(fp);

    return 0;
}
