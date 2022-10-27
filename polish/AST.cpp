#include "AST.h"
#include "Nodes.h"
#include "Stack.h"
#include <sstream>
#include <iostream>
#include <string>
#include <stdexcept>

using namespace std;

bool isNumber(string str);

AST *AST::parse(const std::string &expression)
{
    Stack s;
    string token;
    istringstream myExp(expression);
    while (myExp >> token)
    {
        if (token == "+")
        {
            AST *first = s.pop();
            AST *second = s.pop();
            Add *addition = new Add(first, second);
            s.push(addition);
        }
        else if (token == "-")
        {
            AST *first = s.pop();
            AST *second = s.pop();
            Subtract *minus = new Subtract(first, second);
            s.push(minus);
        }
        else if (token == "*")
        {
            AST *first = s.pop();
            AST *second = s.pop();
            Mutliply *mult = new Mutliply(first, second);
            s.push(mult);
        }
        else if (token == "/")
        {
            AST *first = s.pop();
            AST *second = s.pop();
            Divide *div = new Divide(first, second);
            s.push(div);
        }
        else if (token == "%")
        {
            AST *first = s.pop();
            AST *second = s.pop();
            Modulo *mod = new Modulo(first, second);
            s.push(mod);
        }
        else
        {
            if (isNumber(token) == false)
            {
                throw runtime_error("Invalid token:: " + token);
            }
            else
            {
                double value = stod(token);
                Number *num = new Number(value);
                s.push(num);
            }
        }
    }
    AST *final = s.pop();
    return final;
}

bool isNumber(string str)
{
    int period = 0;
    int len = str.length();
    for (int i = 0; i < len; i++)
    {
        if (isdigit(str[i]))
        {
        }
        else if (str[i] == '.')
        {
            if (period == 0)
            {
                period++;
            }
            else
            {
                return false;
            }
        }
        else if (str[i] == '+' || str[i] == '-')
        {
            if (i == 0)
            {
                continue;
            }
            else
            {
                return false;
            }
        }
        else
        {
            return false;
        }
    }
    return true;
}