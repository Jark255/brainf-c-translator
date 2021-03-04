#include <stdio.h>
#include <stdlib.h>

const char BPROG_BEGGINING[] =
    "#include <stdio.h>\n\nint main() {\nchar array[30000] = {0};\nchar *ptr = "
    "&array[0];\n\n";
const char BPROG_END[] = "\nreturn 0;\n}";

int main(int argc, char **argv) {
    if (argc != 3) {
        return 1;
    }

    FILE *input = fopen(argv[1], "r");
    FILE *output = fopen(argv[2], "w");

    fwrite(BPROG_BEGGINING, sizeof(char), sizeof(BPROG_BEGGINING)-1, output);

    char buffer = '\0';
    short commentFlag = 0;
    while ((buffer = fgetc(input))) {
        // putchar(buffer);

        if (buffer == -1)
            break;

        if (commentFlag) {
            fputc(buffer, output);
            if (buffer == '\n')
                commentFlag = 0;
            continue;
        }

        switch (buffer) {
        case '+':
            fwrite("++*ptr;\n\0", sizeof(char), 8, output);
            break;

        case '-':
            fwrite("--*ptr;\n\0", sizeof(char), 8, output);
            break;

        case '>':
            fwrite("++ptr;\n\0", sizeof(char), 7, output);
            break;

        case '<':
            fwrite("--ptr;\n\0", sizeof(char), 7, output);
            break;

        case '.':
            fwrite("putchar(*ptr);\n\0", sizeof(char), 15, output);
            break;

        case ',':
            fwrite("*ptr=getchar();\n\0", sizeof(char), 16, output);
            break;
        
        case '[':
            fwrite("while (*ptr) {\n\0", sizeof(char), 15, output);
            break;
        
        case ']':
            fwrite("}", sizeof(char), 1, output);
            break;
        
        case '*':
            commentFlag = 1;
            fwrite("//\0", sizeof(char), 2, output);
            break;
        
        case ' ':
            break;
        
        case '\n':
            break;
        
        default:
            return 2;
            break;
        }
    }

    fwrite(BPROG_END, sizeof(char), sizeof(BPROG_END)-1, output);

    fclose(input);
    fclose(output);

    return 0;
}