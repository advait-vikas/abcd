#include <bits/stdc++.h>
using namespace std;
void computeLPSArray(string& pat, int M, vector<int>& lps)
{
    int len = 0;
    lps[0] = 0;
    int i = 1;
    while (i < M) {
        if (pat[i] == pat[len]) {
            len++;
            lps[i] = len;
            i++;
        }
        else 
        {
            if (len != 0) {
                len = lps[len - 1];
            }
            else 
            {
                lps[i] = 0;
                i++;
            }
        }
    }
}
vector<int> KMPSearch(string& pat, string& txt)
{
    int M = pat.length();
    int N = txt.length();
    vector<int> lps(M);
    vector<int> result;
    computeLPSArray(pat, M, lps);
    int i = 0; 
    int j = 0; 
    while ((N - i) >= (M - j)) {
        if (pat[j] == txt[i]) {
            j++;
            i++;
        }
        if (j == M) {
            result.push_back(i - j + 1);
            j = lps[j - 1];
        }
        else if (i < N && pat[j] != txt[i]) {
            if (j != 0)
                j = lps[j - 1];
            else
                i = i + 1;
        }
    }
    return result;
}
int main()
{
    string txt = "geeksforgeeks";
    string pat = "geeks";
    auto start = chrono::high_resolution_clock::now();
    vector<int> result = KMPSearch(pat, txt);
    auto end = chrono::high_resolution_clock::now();
    for (int i = 0; i < result.size(); i++) {
        cout << result[i] << " ";
    }
    cout << endl;
    chrono::duration<double, milli> duration = end - start;
    cout << "Time taken: " << duration.count() << " ms" << endl;
    return 0;
}

