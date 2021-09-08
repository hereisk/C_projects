#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <assert.h>
#include <stdbool.h>

#define STACK_TOP (-1)
#define modifier (-1)

int _isdigit(char lexeme)
{
    if('0' <= lexeme && lexeme <= '9') return 1;
    return 0;
}

typedef struct expression_s {
    int* values;
    int top_val;
    char* operator;
    int top_op;
} expression_t;

// allocate struct and initilize members 
expression_t* create_expression(int expression_len) {
    expression_t* expression = malloc(sizeof(expression_t));
    expression->values = malloc(sizeof(int) * expression_len+2);
    memset(expression->values, 0, expression_len);
    expression->top_val = STACK_TOP;
    expression->operator = malloc(sizeof(char) * expression_len);
    memset(expression->operator, 0, expression_len);
    expression->top_op = STACK_TOP;
    return expression;
}

// destroy pointers to avoid memory leaks
void destroy_expression(expression_t* expression) {
    free(expression->values);
    free(expression->operator);
    free(expression);
}

int operation(int num1, int num2, char op) {
    switch (op) {
        case '+': return num1 + num2;
        case '-': return num1 - num2;
        case '*': return num1 * num2;
        case '/': return num1 / num2;
        case '%': return num1 % num2;
        default: assert(false);
    }
}

void push_value(expression_t* expression, int value) {
    expression->top_val++;
    expression->values[expression->top_val] = value;
}

void push_op(expression_t* expression, char op) {
    expression->top_op++;
    expression->operator[expression->top_op] = op;
}

int pop_value(expression_t* expression) {
    // expression->top_val++;
    // expression->values[expression->top_val] = value;
    int value2 = expression->values[expression->top_val];
    expression->top_val--;
    return value2;
}

char pop_op(expression_t* expression) {
    // expression->top_op++;
    // expression->operator[expression->top_op] = op;
    char op = expression->operator[expression->top_op];
    expression->top_op--;
    return op;
}

int evaluate(expression_t* expression) {
    int value2 = pop_value(expression);
    int value1 = pop_value(expression); 
    char op = pop_op(expression);

    return operation(value1, value2, op);
}

int order_of_precedence(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/' || op == '%') return 2;
    return 0;
}

int parse_string(const char* string, expression_t* expression, int expression_len)
{
    int index = 0;
    while (index < expression_len) {
        // skip over whitespace
        if (string[index] == ' ' || string[index] == '\t') {
            index++;
            continue;
        }
        // treat as unary minus
        //bool is_val_stack_empty = expression->top_val == STACK_TOP;
        bool is_negative = string[index] == '-' && ((expression->top_val == STACK_TOP) || 
            // (expression->operator[expression->top_op] == '('));
            (expression->top_op != STACK_TOP));
        // look for negative, remember (similar to article), skip over, 
        // capture entire digit and push to value stack
        if (is_negative) {
          push_op(expression, '+');
          index++;
        }
        if (_isdigit(string[index])) {
            int val = 0;

            while (index < expression_len && _isdigit(string[index])) {
                val = ((val * 10) + (string[index]) - '0');
                index++;
            }   
            val *= is_negative ? -1 : 1;      
            push_value(expression, val);
            index--;
        }
        else if (string[index] == '(') {
            if(string[index+1] == ')')
            {
                destroy_expression(expression);
                printf("syntax error\n");
                return 1;
            }
            if (is_negative) {
              push_value(expression, -1);
              push_op(expression, '*');
            }
            push_op(expression, string[index]);
        }
        // perform all operations within both parens
        else if (string[index] == ')') {            
            while (expression->top_op != STACK_TOP && expression->operator[expression->top_op] != '(') {
                int result = evaluate(expression);
                result *= is_negative ? -1 : 1;   
                push_value(expression, result);
                assert(expression->top_op != STACK_TOP);
            }
            // pop left paren from operator stack
            pop_op(expression);
        }
        else if (string[index] == '+' || string[index] == '*' || string[index] == '/' || string[index] == '%' || string[index] == '-') {
            while (expression->top_op != -1 && (order_of_precedence(expression->operator[expression->top_op]) >= order_of_precedence(string[index]))) {
                int result = evaluate(expression);
                push_value(expression, result);
            }
            push_op(expression, string[index]);
        }
        index++;
    }
    return 0;
}

int check_error(const char* string, int expression_len)
{
    for(int i = 0; i < expression_len; i++)
    {
        if(
            (string[i] < '0' || 
            string[i] > '9') &&
            string[i] != '+' && 
            string[i] != '*' && 
            string[i] != '/' && 
            string[i] != '%' && 
            string[i] != '-' &&
            string[i] != '(' &&
            string[i] != ')' && string[i] != ' ') 
        {
            printf("Unknown lexeme\n");
            return 1;
        }

        if(
            (
                string[i] == '+' || 
                string[i] == '*' || 
                string[i] == '/' || 
                string[i] == '%' || 
                string[i] == '-'
            )
                &&
            (
                string[i+1] == '+' || 
                string[i+1] == '*' || 
                string[i+1] == '/' || 
                string[i+1] == '%'
            )
        )
        {
            printf("Syntax error\n");
            return 1;
        }

        if(string[i] == '(' && string[i+1] == ')' )
        {
            printf("Syntax error\n");
            return 1;
        }

        if(string[i] == '/' && string[i+1] == '0')
        {
            printf("The result is undefined\n");
            return 1;
        }
    }
    return 0;
}

int evaluate_string(const char* string) {
    // get length of string passed
    int expression_len = strlen(string);

    if(check_error(string, expression_len)) return 1;

    // allocate memory for struct and memebers
    expression_t* expression = create_expression(expression_len);
    assert(expression != NULL);
    parse_string(string, expression, expression_len);

    while (expression->top_op != -1) {
        int result = evaluate(expression);
        push_value(expression, result);
    }

    int final_result = pop_value(expression);
    destroy_expression(expression);
    printf("%d\n", final_result);
    return 0;
}

struct s {
  char* expr;
  int result;
};

int main(int argc, char* argv[]) {
    int i = 1;
    /*struct s exps[] = {
      {"1-4", -3},
      {"-(-((-4)+-6))", -10},
      {"1-(-((-4)+-6))", -9},
      {"-(2)", -2},
      { "1+ 2 + 3", 6 },
      { "3 + (4 + 8)", 15 },
      { "(1 + 1)", 2},
      {"-(2)", -2},
      {"1 + (3 + 4)", 8},
      { "1 -(4 + 8)", -11},
      { "1 + 2 *-3", -5},
      { "1+2*(3-42)%5", 1},
      {"(1-1)", 0}
    };
    for (long unsigned int i = 0; i < sizeof(exps)/sizeof(exps[0]); i++) {
      int result = evaluate_string(exps[i].expr);
      printf("%s = %d\n", exps[i].expr, result);
      assert( result == exps[i].result);
    };
    */
     if(argc == 1) {
          return 0;
    } else {
        while (i < argc) {
            if(evaluate_string(argv[i])) break;
            i++; 
        }
    }
    return 0;
}  