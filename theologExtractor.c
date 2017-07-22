#include <string.h>
#include <stdio.h>
#include <stdlib.h>

struct pattern
{
    size_t currIndex;
    char *str;
    void (*func)(void);
};

void checkPattern(int ch, struct pattern *pattern);
void copyBoxContent(void);

struct pattern patterns[] =
{
    {0, "defbox", copyBoxContent},
    {0, "theobox", copyBoxContent}
};

char const separator[] = "\n\n\n";
FILE* input;
FILE *output;

int main(int argc, char *argv[])
{
    if (argc < 3)
    {
        puts("Usage: theologExtractor <path/to/lectureN.tex> <path/to/output.file>");
        exit(EXIT_FAILURE);
    }

    input = fopen(argv[1], "r");
    output = fopen(argv[2], "a");
    size_t len = sizeof(patterns) / sizeof(patterns[0]);
    int ch = 0;

    while ((ch = fgetc(input)) != EOF)
    {
        for (size_t i = 0; i < len; i++)
        {
            checkPattern(ch, &patterns[i]);
        }
    }

    fclose(input);
    fclose(output);

    return EXIT_SUCCESS;
}

void checkPattern(int ch, struct pattern *pattern)
{
    if (ch == pattern->str[pattern->currIndex])
    {
        if (pattern->currIndex == strlen(pattern->str) - 1)
        {
            fprintf(output, "\\%s", pattern->str);
            pattern->func();
            pattern->currIndex = 0;
        }
        else
        {
            pattern->currIndex++;
        }
    }
    else
    {
        pattern->currIndex = 0;
    }
}

void copyBoxContent(void)
{
    int depth = 0;
    int prevCh = 0;

    do
    {
        int ch = fgetc(input);
        fputc(ch, output);

        // Escaped curly brackets don't change depth
        if (prevCh != '\\')
        {
            switch (ch)
            {
                case '{':
                    depth++;
                    break;
                case '}':
                    depth--;
            }
        }

        prevCh = ch;
    }
    while(depth > 0);

    fprintf(output, "%s", separator);
}
