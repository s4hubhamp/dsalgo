// String Compression: Implement a method to perform basic string compression using the counts
// of repeated characters. For example, the string aabcccccaaa would become a2blc5a3. If the
// "compressed" string would not become smaller than the original string, your method should return
// the original string. You can assume the string has only uppercase and lowercase letters (a - z).

#include <iostream>
#include <string>

using namespace std;

string compress(string s)
{
    if (s.length() < 2)
    {
        return s;
    }

    string compressed_str = "";
    int i = 1, j = 0;
    char last_char = s[0];
    int last_char_occurrences = 1;
    while (i < s.length())
    {
        if (last_char == s[i])
        {
            last_char_occurrences++;
        }
        else
        {
            compressed_str += last_char;
            compressed_str += to_string(last_char_occurrences);
            last_char = s[i];
            last_char_occurrences = 1;
        }
        i++;
    }

    compressed_str += last_char;
    compressed_str += to_string(last_char_occurrences);

    return compressed_str;
}

int main()
{
    string s = "abc";
    cout << "original string " << s << endl;
    cout << "compressed string " << compress(s) << endl;
}