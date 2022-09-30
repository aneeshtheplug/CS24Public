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

void reverse()
{
    string input;
    string word = "";
    int index = 0;

    getline(cin, input);

    int length = input.length();
    for (int i = index; i < length; i++)
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
            index = index + 1;
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