#include "Nodes.h"
#include <sstream>

// Implement your AST subclasses' member functions here.

// To format a double for output:
//   std::ostringstream stream;
//   stream << value;
//   return stream.str();

Number::Number(double value)
{
    num = value;
}

std::string Number::prefix() const
{
    std::ostringstream stream;
    stream << num;
    return stream.str();
}

std::string Number::postfix() const
{
    std::ostringstream stream;
    stream << num;
    return stream.str();
}

double Number::value() const
{
    return num;
}

Add::Add(AST *lhs, AST *rhs)
{
    left = lhs;
    right = rhs;
}

std::string Add::prefix() const
{
    std::string polish = "+";
    polish += " ";
    polish += left->prefix();
    polish += " ";
    polish += right->prefix();
    return polish;
}

std::string Add::postfix() const
{
    std::string reverse = "";
    reverse += left->postfix();
    reverse += " ";
    reverse += right->postfix();
    reverse += " ";
    reverse += "+";
    return reverse;
}

double Add::value() const
{
    return left->value() + right->value();
}

Subtract::Subtract(AST *lhs, AST *rhs)
{
    left = lhs;
    right = rhs;
}

std::string Subtract::prefix() const
{
    std::string polish = "-";
    polish += " ";
    polish += left->prefix();
    polish += " ";
    polish += right->prefix();
    return polish;
}
std::string Subtract::postfix() const
{
    std::string reverse = "";
    reverse += left->postfix();
    reverse += " ";
    reverse += right->postfix();
    reverse += " ";
    reverse += "-";
    return reverse;
}

double Subtract::value() const
{
    return left->value() - right->value();
}

Mutliply::Mutliply(AST *lhs, AST *rhs)
{
    left = lhs;
    right = rhs;
}
std::string Mutliply::prefix() const
{
    std::string polish = "*";
    polish += " ";
    polish += left->prefix();
    polish += " ";
    polish += right->prefix();
    return polish;
}

std::string Mutliply::postfix() const
{
    std::string reverse = "";
    reverse += left->postfix();
    reverse += " ";
    reverse += right->postfix();
    reverse += " ";
    reverse += "*";
    return reverse;
}

double Mutliply::value() const
{
    return left->value() * right->value();
}

Divide::Divide(AST *lhs, AST *rhs)
{
    left = lhs;
    right = rhs;
}

std::string Divide::prefix() const
{
    std::string polish = "/";
    polish += " ";
    polish += left->prefix();
    polish += " ";
    polish += right->prefix();
    return polish;
}
std::string Divide::postfix() const
{
    std::string reverse = "";
    reverse += left->postfix();
    reverse += " ";
    reverse += right->postfix();
    reverse += " ";
    reverse += "/";
    return reverse;
}

double Divide::value() const
{
    return left->value() / right->value();
}

Modulo::Modulo(AST *lhs, AST *rhs)
{
    left = lhs;
    right = rhs;
}

std::string Modulo::prefix() const
{
    std::string polish = "%";
    polish += " ";
    polish += left->prefix();
    polish += " ";
    polish += right->prefix();
    return polish;
}

std::string Modulo::postfix() const
{
    std::string reverse = "";
    reverse += left->postfix();
    reverse += " ";
    reverse += right->postfix();
    reverse += " ";
    reverse += "%";
    return reverse;
}
double Modulo::value() const
{
    return fmod(left->value(), right->value());
}

std::string Negtation::prefix() const
{
    std::string polish = "~";
    polish += left->prefix();
    polish += " ";
    polish += right->prefix();
    return polish;
}

std::string Negtation::postfix() const
{
    std::string reverse = "";
    reverse += left->postfix();
    reverse += " ";
    reverse += right->postfix();
    reverse += " ";
    reverse += "~";
    return reverse;
}

double Negtation::value() const
{
    if (left->value())
    {
        return left->value() * -1;
    }
    else
    {
        return right->value() * -1;
    }
}