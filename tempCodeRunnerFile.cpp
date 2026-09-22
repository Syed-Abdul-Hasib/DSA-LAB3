#include <iostream>
#include <string>
#include <cctype>
using namespace std;
 
// Returns true if 's' reads the same forward and backward
// (spaces, punctuation, and letter case are ignored).
bool isPalindrome(string s) {
    int left = 0;
    int right = s.length() - 1;
 
    while (left < right) {
        // Move left pointer forward until it points to a letter/digit
        if (!isalnum(s[left])) {
            left++;
            continue;
        }
        // Move right pointer backward until it points to a letter/digit
        if (!isalnum(s[right])) {
            right--;
            continue;
        }
        // Compare the two characters (case-insensitive)
        if (tolower(s[left]) != tolower(s[right])) {
            return false;
        }
        left++;
        right--;
    }
    return true;
}
 
int main() {
    string input;
 
    cout << "Enter a string: ";
    getline(cin, input);
 
    if (isPalindrome(input)) {
        cout << "\"" << input << "\" IS a palindrome." << endl;
    } else {
        cout << "\"" << input << "\" is NOT a palindrome." << endl;
    }
 
    return 0;
}
 