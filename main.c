#include <stdio.h>
#include <stdlib.h>

struct elem
{
    double value;
    char op;
    char if_op;
};

int prio(char a, char b)
{
    //switch can be used
    char q, w;
    if(a == '+' || a == '-') {
        q = 1;
    } else if (a == '*' || a=='/') {
        q = 2;
    } else {
        q = 3;
    }
    if(b == '+' || b == '-') {
        w = 1;
    } else if (b == '*' || b=='/') {
        w = 2;
    } else {
        w = 3;
    }
    return q - w;
}

int create_rpn(struct elem *arr)
{
    const int stack_size = 200;
    int stack_pointer = 0, len = 0;
    char a = 10;
    char stack[stack_size];
    while(a != '\n') {
        a = getchar();
        if(a == '(') {
            stack[stack_pointer++] = a;
        } else {
            ungetc(a, stdin);
        }
        arr[len].if_op = 0;
        scanf("%lf", &(arr[len++].value));

        while(1) {
            //need to check if it's '\n'
            a = getchar();
            if(a != ' ') break;
        }
        if(a == '\n') break;
        if (a == ')') {
            while(stack[--stack_pointer] != '(') {
                arr[len].if_op = 1;
                arr[len++].op = stack[stack_pointer];
            }
        }else if(stack_pointer == 0 || prio(a, stack[stack_pointer - 1] > 0)) {
            stack[stack_pointer++] = a;
        } else {
            arr[len].if_op = 1;
            arr[len++].op = stack[stack_pointer - 1];
            stack[stack_pointer - 1] = a;
        }
        //dealing with spaces before next non-space character
        //no need to check if it's '\n' because it was already checked in line "if(a == '\n') break;"
        //honestly no need to check '\n' in major cycle, because after this cycle a will never be \n. I reckon :3
        while(1) {
            a = getchar();
            if(a != ' ') {
                ungetc(a, stdin);
                break;
            }
        }
    }
    while(stack_pointer) {
        arr[len].if_op = 1;
        arr[len++].op = stack[stack_pointer];
        --stack_pointer;
    }

    return len;
}

double act(double a, double b, char op)
{
    if(op == '+') return a + b;
    if(op == '-') return a - b;
    if(op == '*') return a * b;
    if(op == '/') return a / b;
    if(op == '^') {
        while(b--) a *= a;
        return a;
    }

}

int count_rpn(struct elem *rpn, int len)
{
    //only one num stack is needed
    const int stack_size = 200;
    int pointer = 0;
    double stack[stack_size];
    for(int i = 0; i < len; ++i) {
        while(rpn[i].if_op != 1) {
            stack[pointer++] = rpn[i].value;
            ++i;
        }
        stack[pointer - 2] = act(stack[pointer - 2], stack[pointer - 1], rpn[i].op);
        --pointer;
    }
    return 0;
}

int main(void)
{
    const int size_of_exp = 200;
    struct elem arr[size_of_exp];
    int len;

    len = create_rpn(arr);

    printf("%d", count_rpn(arr, len));

    return 0;
}
