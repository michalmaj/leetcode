/*
Problem: Strobogrammatic Number
Link: https://leetcode.com/problems/strobogrammatic-number/

Statement:
Given a string num representing an integer, determine whether it is a strobogrammatic number. 
Return TRUE if the number is strobogrammatic or FALSE if it is not.
A strobogrammatic number appears the same when rotated 180 degrees (viewed upside down).

Constraints:
- 1 <= num.length <= 50
- num contains only digits
- num has no leading zeros except when the number itself is zero

Pattern: Two Pointers / Hash Map

Valid digit pairs for 180° rotation:
- '0' <-> '0'
- '1' <-> '1'
- '8' <-> '8'
- '6' <-> '9'
- '9' <-> '6'

Examples:
- "69"  -> true
- "88"  -> true
- "818" -> true
- "962" -> false

Edge cases to think about:
- Single digit: '0','1','8' vs others
- Middle character for odd length must be {0,1,8}
- Non-rotatable digits: 2,3,4,5,7
- Strings like "10" -> rotate => "01" (not equal) -> false

Plan (your notes):
1) ...
2) ...
Complexity target: O(n) time / O(1) extra space
*/

#include <bits/stdc++.h>
using namespace std;

// Function that checks is given digit is not strobogrammatic
bool invalidValues(int num) {
    if (num == 2 || num == 3 || num == 4 || num == 5 || num == 7) {
        return true;
    }

    return false;
}

// Function that checks if mapping is wrong
bool incorrectMapping(int v1, int v2) {
    if (v1 == 6 && v2 != 9 || v1 == 9 && v2 != 6) {
        return true;
    }

    if (v1 == 0 && v2 != 0) {
        return true;
    }

    if (v1 == 1 && v2 != 1) {
        return true;
    }

    if (v1 == 8 && v2 != 8) {
        return true;
    }

    return false;
}

bool IsStrobogrammatic(const string& num) {
    // Checking if there is only a single digit
    if (num.size() == 1 && (invalidValues(num[0] - '0') || num[0] - '0' == 6 || num[0] - '0' == 9)) {
        return false;
    }

    // Set two pointers left and right, left points to the begin of give num.
    // Right points to the end.
    int l = 0;
    int r = num.size() - 1;

    // Main loop works until left pointer is less than right
    while (l < r) {
        // Convert chars to numbers
        int v1 = num[l] - '0';
        int v2 = num[r] - '0';

        // If number contais single digit that is not strobogrammatic return false
        if (invalidValues(v1) || invalidValues(v2)) {
            return false;
        }

        // Check if mapping is correct, it should map:
        // 6 -> 9, 9 -> 6, 0 -> 0, 1 -> 1, 8 -> 8
        if (incorrectMapping(v1, v2)) {
            return false;
        }

        // Update pointers
        ++l;
        --r;
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
    bool got = IsStrobogrammatic(s);
    assert_eq(got, expected, name);
}
// ----------------------------------------


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    try {
        // ---- Basic tests from description / typical cases ----
        run_case("69",   true,  "pair-69");
        run_case("88",   true,  "pair-88");
        run_case("818",  true,  "odd-center-8");
        run_case("962",  false, "example-false");

        // ---- More sanity/edge cases for your debugging ----
        run_case("1",    true,  "single-1");
        run_case("0",    true,  "single-0");
        run_case("8",    true,  "single-8");
        run_case("2",    false, "single-2-not-rotatable");
        run_case("10",   false, "leading-zero-after-rotate");
        run_case("906",  true,  "mirror-906");   // 906 -> rotate -> 906
        run_case("619",  true,  "mirror-619");   // 619 -> rotate -> 619


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