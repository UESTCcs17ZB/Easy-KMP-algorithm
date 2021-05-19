// ----------
// Author: Zhang Bin. Majored in computer science @UESTC, China.
// ----------
// I found almost all the codes of KMP algorithm on the Internet were really awful, especially in CSDN, a disgusting website belongs to "Ctrl C+V programmers" in China.
// So I decided to rewrite it for a beautiful one. The easy KMP algorithm, which is really easy to understand and program.
// No one knows more about how to write a faster KMP algorithm than I do! (just a joke)
// ----------
#include <stdio.h>

#include <algorithm>
#include <string>
#include <vector>
using namespace std;
// The following function will calculate the next array of pattern.
// next[i] is the length of substring(from 0 to i)'s longest common prefix and suffix.
// For example, the next array of pattern "abcabc" will be {0, 0, 0, 1, 2, 3}.
// PS: The whole pattern is not a prefix or suffix of itself, thus the next array of "a" is {0}, not {1}!
void buildNext(const char *pattern, size_t patternLen, size_t *next) {
    next[0] = 0;  // next[0] is always 0, maybe we could optimize this memory unit in the future.
    size_t len = 0;
    size_t j = 1;
    while (j < patternLen) {
        if (pattern[j] == pattern[len]) {
            // This code block will do the same thing as "next[j] = len+1; len++; j++", 
            // but a little bit faster.(The speed might be in the same if you add "-O2" to compile the code, I'm not sure GCC would discover that or not)
            len++;
            next[j] = len;
            j++;
        } else {
            if (len == 0) {
                next[j] = 0;
                j++;
            } else {
                len = next[len - 1];
            }
        }
    }
}
// All of the begin position of pattern appeared in text will be pushed back to vector results.
void KMP(const char *text, size_t textLen, const char *pattern, size_t patternLen, size_t *next, vector<size_t> &results) {
    size_t i = 0, j = 0;
    while (i < textLen) {
    // You can ignore the lable "skipWhileCompare" druing the first time you read this code, it's just a trick.
    skipWhileCompare:
        if (text[i] == pattern[j]) {
            i++;
            j++;
            if (j == patternLen) {
                results.push_back(i - j);
                j = next[j - 1];
            }
        } else {
            if (j != 0) {
                j = next[j - 1];
                // We could skip the compare: "i < textLen?" in the while sentence.
                // because now i is less than textLen, and we haven't changed it yet. (textLen is a const value.)
                goto skipWhileCompare;
            } else {
                i++;
            }
        }
    }
}
//  Test
int main(int argc, const char *argv[]) {
    string text = "abcababcabc";
    string pattern = "abcabc";
    auto next = new size_t[pattern.size()];
    buildNext(pattern.c_str(), pattern.size(), next);
    vector<size_t> results;
    KMP(text.c_str(), text.size(), pattern.c_str(), pattern.size(), next, results);
    // Output will be like:
    // pattern: a b c a b c
    // next:    0 0 0 1 2 3
    // text:    a b c a b a b c a b c
    // results: 0 0 0 0 0 1 0 0 0 0 0
    printf("pattern: ");
    for (auto v : pattern) {
        printf("%c ", v);
    }
    printf("\n");
    printf("next:    ");
    for (size_t i = 0; i < pattern.size(); i++) {
        printf("%d ", next[i]);
    }
    printf("\n");
    printf("text:    ");
    for (auto v : text) {
        printf("%c ", v);
    }
    printf("\n");
    printf("results: ");
    for (size_t i = 0; i < text.size(); i++) {
        if (binary_search(results.begin(), results.end(), i)) {
            printf("1 ");
        } else {
            printf("0 ");
        }
    }
    printf("\n");
    delete[] next;
    return 0;
}
