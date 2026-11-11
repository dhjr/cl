
#include <stdio.h>

int main()
{
    char line[100];
    char line1[100];
    char result[10], op1[10], op2[10];
    char opr;
    int n;

    printf("Enter the 3 address code:\n");
    printf("Press e for exit\n");

    while (1)
    {
        fgets(line, sizeof(line), stdin);
        int j=0;

        for (int i=0;line[i]!='\0';i++)
        {
            if (line[i] != ' ' && line[i] != '\t' && line[i] != '\n')
                line1[j++] = line[i];
        }
        line1[j] = '\0';


        printf("%s",line1);

        if (line[0] == '\n')
            continue;

        if (line[0] == 'e')
            break;

        n = sscanf(line1, "%s=%s%c%s", result, op1, &opr, op2);

        if (n == 4)
        {
            switch (opr)
            {
                case '+':
                    printf("MOV AX,%s\n", op1);
                    printf("ADD AX,%s\n", op2);
                    printf("MOV %s,AX\n", result);
                    break;

                case '-':
                    printf("MOV AX,%s\n", op1);
                    printf("SUB AX,%s\n", op2);
                    printf("MOV %s,AX\n", result);
                    break;

                case '*':
                    printf("MOV AX,%s\n", op1);
                    printf("MOV BX,%s\n", op2);
                    printf("MUL BX\n");
                    printf("MOV %s,AX\n", result);
                    break;

                case '/':
                    printf("MOV AX,%s\n", op1);
                    printf("MOV BX,%s\n", op2);
                    printf("MOV DX,0\n");
                    printf("DIV BX\n");
                    printf("MOV %s,AX\n", result);
                    break;
            }
        }
        else if (n == 2)
        {
            printf("MOV AX,%s\n", op1);
            printf("MOV %s,AX\n", result);
        }
        else
        {
            printf("Invalid 3 address code\n");
        }

        printf("\n");
    }

    return 0;
}
