#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <unordered_set>

using namespace std;

class  PrefixandSuffix{
public:
    int countPrefixSuffixPairs(vector<string>& words) {
        unordered_map<string, int> spCount;
        int count = 0;
        for (auto rit = words.crbegin(); rit != words.crend(); rit++) {
            if (spCount.count(*rit) == 1)
                count += spCount[*rit];

            const int n = rit->size();
            for (int i = 1; i <= n; i++) {
                string prefix = rit->substr(0, i);
                string suffix = rit->substr(n - i, i);
                if (prefix == suffix)
                    spCount[prefix]++;
            }
        }
        return count;
    }
};

class MyHashSet {
public:
    vector<bool>vec;
    MyHashSet() {
        vec.resize(1000001,false);
    }

    void add(int key) {
        vec[key] = true;
    }

    void remove(int key) {
        vec[key] = false;
    }

    bool contains(int key) {
        return vec[key] == true;
    }
};

class DNAsequences {
public:
    vector<string> findRepeatedDnaSequences(string s) {
        vector<string> result;
        unordered_map<string, int> substrings;

        for (int i = 0; i <= (int)s.size() - 10; ++i) {
            string substr = s.substr(i, 10);
            substrings[substr]++;
        }

        for (const auto& entry : substrings) {
            if (entry.second > 1) {
                result.push_back(entry.first);
            }
        }

        return result;
    }
};

class BinaryCodes {
public:
    bool hasAllCodes(string s, int k) {
        int n = s.size();

        unordered_set<string> codes;
        for (int i = 0; i <= n - k; ++i) {
            codes.insert(s.substr(i, k));
        }

        return codes.size() == (1 << k);
    }
};

int main() {
    PrefixandSuffix solution;
    vector<string> words = {"aba", "ababa", "abcd"};
    cout << solution.countPrefixSuffixPairs(words) << endl;

    MyHashSet* obj = new MyHashSet();

    obj->add(1);
    obj->add(2);
    cout << "Contains 1: " << (obj->contains(1) ? "true" : "false") << endl; // Output: true
    cout << "Contains 3: " << (obj->contains(3) ? "true" : "false") << endl; // Output: false
    obj->add(2);
    cout << "Contains 2: " << (obj->contains(2) ? "true" : "false") << endl; // Output: true
    obj->remove(2);
    cout << "Contains 2: " << (obj->contains(2) ? "true" : "false") << endl; // Output: false

    DNAsequences solution1;

    string input1 = "AAAAACCCCCAAAAACCCCCCAAAAAGGGTTT";
    vector<string> result1 = solution1.findRepeatedDnaSequences(input1);
    cout << "Output for input \"" << input1 << "\":" << endl;
    for (const auto& sequence : result1) {
        cout << sequence << endl;
    }

    string input2 = "AAAAAAAAAAAAA";
    vector<string> result2 = solution1.findRepeatedDnaSequences(input2);
    cout << "\nOutput for input \"" << input2 << "\":" << endl;
    for (const auto& sequence : result2) {
        cout << sequence << endl;
    }

    delete obj;
    BinaryCodes solution2;

    string s1 = "00110110";
    int k1 = 2;
    cout << "Output for input s = \"" << s1 << "\" and k = " << k1 << ": ";
    cout << (solution2.hasAllCodes(s1, k1) ? "true" : "false") << endl;

    string s2 = "0110";
    int k2 = 1;
    cout << "Output for input s = \"" << s2 << "\" and k = " << k2 << ": ";
    cout << (solution2.hasAllCodes(s2, k2) ? "true" : "false") << endl;

    string s3 = "0110";
    int k3 = 2;
    cout << "Output for input s = \"" << s3 << "\" and k = " << k3 << ": ";
    cout << (solution2.hasAllCodes(s3, k3) ? "true" : "false") << endl;

    return 0;
}

