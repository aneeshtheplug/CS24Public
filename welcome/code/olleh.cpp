#include <iostream>
#include <string>

using namespace std;

string reverseWord(string word)
{
    string rev = "";
    for (int i = word.length() - 1; i >= 0; i--)
    {
        rev = rev + word[i];
    }
    return rev;
}

void reverse()
{
    string input;
    string word = "";

    getline(cin, input);

    int length = input.length();
    if (length == 0)
    {
        cout << endl;
    }
    for (int i = 0; i < length; i++)
    {
        if (i == length - 1)
        {
            if (isspace(input[i]) || ispunct(input[i]))
            {
                cout << reverseWord(word) << input[i];
            }
            else
            {
                word = word + input[i];
                cout << reverseWord(word);
            }
            cout << endl;
        }
        else if (isspace(input[i]) || ispunct(input[i]))
        {
            cout << reverseWord(word) << input[i];
            word = "";
        }
        else
        {
            word = word + input[i];
        }
    }
}

int main()
{
    reverse();

    return 0;
}