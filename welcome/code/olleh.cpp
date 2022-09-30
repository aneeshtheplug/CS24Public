#include <iostream>
#include <string>

using namespace std;

string reverseWord(string word)
{
    string rev = "";
    for (int i = word.length(); i >= 0; i--)
    {
        rev = rev + word[i];
    }
    return rev;
}

int main()
{
    string input;
    string word = "";

    getline(cin, input);

    for (int i = 0; i < input.length(); i++)
    {
        if (i == input.length() - 1)
        {
            if (isspace(input[i]) || ispunct(input[i]))
            {
                cout << reverseWord(word) << input[i] << endl;
                word = "";
            }
            else
            {
                word = word + input[i];
                cout << reverseWord(word) << endl;
            }
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