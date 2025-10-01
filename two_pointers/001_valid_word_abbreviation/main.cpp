/*
Problem: Valid Word Abbreviation
Link: https://leetcode.com/problems/valid-word-abbreviation/

Statement:
Given a string, word, and abbreviation, abbr, return TRUE if the abbreviation matches the given string...

Pattern: Two Pointers / Parsing

Input / Output:
- word: lowercase letters, 1 <= |word| <= 20
- abbr: lowercase letters + digits, 1 <= |abbr| <= 10
- Return: bool

Rules recap:
- A number in abbr skips that many characters in word.
- No leading zeros in numbers.
- Cannot replace empty substring (i.e., "0" is invalid, and concatenating numbers to be adjacent replacements is still one skip count).
- Skips must not be adjacent replacements counted separately (see statement examples).
- All integers fit 32-bit.

Examples from statement:
- "calendar", "cal3ar"  -> true
- "calendar", "c6r"     -> true
- "calendar", "c06r"    -> false (leading zero)
- "calendar", "cale0ndar" -> false (empty replacement)
- "calendar", "c24r"    -> false (adjacent replacements)

Edge cases to think about (fill with your thoughts):
- abbr starts/ends with digits?
- very long number close to |word|?
- skipping exactly to the end?
- single-letter word, single-digit abbr?
- non-matching letters mid-way?

Plan (your notes, not solution code):
1) ...
2) ...
Complexity target:
- Time: O(|word| + |abbr|)
- Space: O(1)
*/

#include <bits/stdc++.h>
using namespace std;

bool ValidWordAbbreviation(const std::string& word, const std::string& abbr) {
    // Set i as a pointer to the first character in word
    int i{0};
    // Set j as a pointer to the first character in abbr
    int j{0};

    // Main loop until both i and j are in bound
    while (i < word.size() && j < abbr.size()) {
        // Check if both characters are the same
        if (word[i] == abbr[j]) {
            // If so, move both pointers by one to the right
            ++i;
            ++j;
        } 
        // If abbr is a character but is not equal to the corresponding character from word
        // or it is a value 0 (trailing 0) just return false
        else if (std::isalpha(abbr[j]) || abbr[j] == '0') {
            return false;
        }
        // Last case, when there is a number in abbr 
        else {
            // Convert characters to integer
            int num{0};
            // As long as there j points to the number collect those values
            while (std::isdigit(abbr[j])) {
                num = num * 10 + (abbr[j] - '0');
                ++j;
            }
            // Move i by number from abbr
            i += num;
        }
    }

    // Return true only if both of pointers are at one item afetr the last one
    return i == word.size() && j == abbr.size();
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
void run_case(const string& word, const string& abbr, bool expected, const string& name) {
    bool got = ValidWordAbbreviation(word, abbr);
    assert_eq(got, expected, name);
}
// ----------------------------------------


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    try {
        // ---- Sanity tests from the statement (these reveal only the examples) ----
        run_case("calendar", "cal3ar", true,  "ex-cal3ar");
        run_case("calendar", "c6r",    true,  "ex-c6r");
        run_case("calendar", "c06r",   false, "ex-c06r-leading-zero");
        run_case("calendar", "cale0ndar", false, "ex-cale0ndar-empty");
        run_case("calendar", "c24r",   false, "ex-c24r-adjacent");

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