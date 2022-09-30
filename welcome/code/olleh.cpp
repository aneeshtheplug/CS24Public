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

    int length = input.length();
    for (int i = 0; i < length; i++)
    {
        if (i == length - 1)
        {
            if (isspace(input[i]) || ispunct(input[i]))
            {
                cout << reverseWord(word) << input[i];
                word = "";
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
    return 0;
}