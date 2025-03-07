#include "eval.h"

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

static double parse_expr(char** expr);
static double parse_term(char** expr);

static void skip_spaces_str(char** str){
    while(**str && isspace(**str)){
        (*str)++;
    }
}

double parse_fact(char** expr){
    skip_spaces_str(expr);

    char* endptr;
    double result = strtod(*expr, &endptr);

    if(*expr == endptr){
        printf("Expected a number.\n");
        return 0.0f;
    }
    *expr = endptr;

    return result;
}

double parse_term(char** expr){
    double result = parse_fact(expr);
    skip_spaces_str(expr);

    while(**expr == '*' || **expr == '/'){
        char op = **expr;
        (*expr)++;
        double next_factor = parse_fact(expr);
        if(op == '*'){
            result *= next_factor;
        }
        else if(op != 0.0f){
            result /= next_factor;
        }
        else{
            printf("Division by zero.\n");
            return result;
        }
        skip_spaces_str(expr);
    }
    return result;
}

double parse_expr(char** expr){

    double result = parse_term(expr);
    skip_spaces_str(expr);

    while(**expr == '+' || **expr == '-'){
        char op = **expr;
        (*expr)++;
        double next_term = parse_term(expr);
        if(op == '+'){
            result += next_term;
        }
        else{
            result -= next_term;
        }
        skip_spaces_str(expr);
    }
    return result;
}

double eval_expr(char* expr){
    return parse_expr(&expr);
}
