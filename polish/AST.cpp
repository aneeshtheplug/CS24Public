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
            Add *addition = new Add(second, first);
            s.push(addition);
        }
        else if (token == "-")
        {
            AST *first = s.pop();
            AST *second = s.pop();
            Subtract *minus = new Subtract(second, first);
            s.push(minus);
        }
        else if (token == "*")
        {
            AST *first = s.pop();
            AST *second = s.pop();
            Mutliply *mult = new Mutliply(second, first);
            s.push(mult);
        }
        else if (token == "/")
        {
            AST *first = s.pop();
            AST *second = s.pop();
            Divide *div = new Divide(second, first);
            s.push(div);
        }
        else if (token == "%")
        {
            AST *first = s.pop();
            AST *second = s.pop();
            Modulo *mod = new Modulo(second, first);
            s.push(mod);
        }
        else if (token == "~")
        {
            AST *little = s.pop();
            Negation *negate = new Negation(little);
            s.push(negate);
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
    if (s.topNode() == nullptr)
    {
        throw runtime_error("No input");
    }
    else if (s.count() > 1)
    {
        throw runtime_error("Too many operands");
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