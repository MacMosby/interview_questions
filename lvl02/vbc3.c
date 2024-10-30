/* TASK:
Write a program that will print the result of a math expression given as argument.
You must handle the operations + and * and the parentheses.
Values will be between 0 and 9.

For example this should work:
$> ./vbc '1' | cat -e
1$

$> ./vbc '2+3' | cat -e
5$

$> ./vbc '3*4+5' | cat -e
17$

$> ./vbc '3+4*5' | cat -e
23$

$> ./vbc '(3+4)*5' | cat -e
35$

$> ./vbc '(((((2+2)*2+2)*2+2)*2+2)*2+2)*2' | cat -e
188$

$> ./vbc '1+' | cat -e
Unexpected end of input$

$> ./vbc '1+2)' | cat -e
Unexpected token ')'$
*/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int evaluate_expression(const char **expr);

int parse_number(const char **expr) {
    int num = 0;
    if (**expr > 47 && **expr < 58) {
        num = **expr - 48;
        (*expr)++;
    }
    return num;
}

int parse_factor(const char **expr) {
    int result;
    if (**expr == '(') {
        (*expr)++; // Skip '('
        result = evaluate_expression(expr);
        (*expr)++; // Skip ')'
    } else {
        result = parse_number(expr);
    }
    return result;
}

int parse_term(const char **expr) {
    int result = parse_factor(expr);
    while (**expr == '*') {
        (*expr)++;
        result *= parse_factor(expr);
    }
    return result;
}

int evaluate_expression(const char **expr) {
    int result = parse_term(expr);
    while (**expr == '+') {
        (*expr)++;
        result += parse_term(expr);
    }
    return result;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s 'expression'\n", argv[0]);
        return 1;
    }

    const char *expr = argv[1];
    int result = evaluate_expression(&expr);

    printf("%d$\n", result);
    return 0;
}
