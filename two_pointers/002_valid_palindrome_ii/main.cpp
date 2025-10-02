/*
Problem: Valid Palindrome II
Link: https://leetcode.com/problems/valid-palindrome-ii/

Statement:
Write a function that takes a string as input and checks whether it can be a valid palindrome 
by removing at most one character from it.

Constraints:
- 1 <= string.length <= 10^5
- String only consists of English letters (a–z, A–Z)

Pattern: Two Pointers

Input / Output:
- Input: string s
- Output: bool (true if valid palindrome with <=1 deletion)

Examples (from statement + typical cases):
- "aba"        -> true   (already palindrome)
- "abca"       -> true   (remove 'b' or 'c')
- "abc"        -> false  (need to remove >1)
- "deeee"      -> true   (remove 'd')
- "a"          -> true   (single char)

Edge cases to test:
- string of length 1 or 2
- string already palindrome
- removal needed at beginning/end
- case sensitivity? (problem statement doesn't force lowercase only, so watch out if uppercase may appear)

Plan (your notes):
1) ...
2) ...
Complexity: 
- Time: O(n)
- Space: O(1)
*/

#include <bits/stdc++.h>
using namespace std;

// Function that checks if a given string is a palindrome in given range from left to right
bool helper(const string& s, size_t l, size_t r) {
    // Main loop chcecking if it is a palindrome
    while (l < r) {
        // Checking if letters at index left and index right are different
        if (s[l] != s[r]) {
            // If so, it means given string is not a palindome, so return false
            return false;
        }

        // Update both pointers
        ++l;
        --r;
    }

    return true;
}

bool IsPalindrome(const string& s) {
    // Set left pointer to the beginning of the string s
    size_t left{0};
    // Set right pointer to the end of the string s
    size_t right{s.size() - 1};

    // Main loop until left pointer is less than right pointer
    while (left < right) {
        // Case when char at left and char at right are different
        if (s[left] != s[right]) {
            // Check both cases from left + 1 till right, and from left till right - 1
            return helper(s, left + 1, right) || helper(s, left, right - 1);
        }

        // Update both pointers, increment left by one and decrement right by one
        ++left;
        --right;
    }

    return true;
}
// ===================================================


// ---------- Tiny test framework ----------
struct TestFail : public std::exception {
    string msg; explicit TestFail(string m):msg(std::move(m)){}
    const char* what() const noexcept override { return msg.c_str(); }
};
template<typename T, typename U>
void assert_eq(const T& got, const U& exp, const string& name) {
    if (!(got == exp)) {
        ostringstream oss;
        oss << "[FAIL] " << name << "  got=" << boolalpha << got
            << "  exp=" << boolalpha << exp;
        throw TestFail(oss.str());
    }
}
void run_case(const string& s, bool expected, const string& name) {
    bool got = IsPalindrome(s);
    assert_eq(got, expected, name);
}
// ----------------------------------------


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    try {
        // ---- Basic tests ----
        run_case("aba", true,  "already-palindrome");
        run_case("abca", true, "remove-one-char");
        run_case("abc", false, "need-more-than-one");
        run_case("deeee", true, "remove-first-char");
        run_case("a", true, "single-char");
        
        cout << "OK\n";
    } catch (const TestFail& e) {
        cerr << e.what() << "\n";
        return 1;
    } catch (const std::exception& e) {
        cerr << "[ERROR] " << e.what() << "\n";
        return 2;
    }
    return 0;
}