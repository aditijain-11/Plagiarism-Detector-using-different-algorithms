#include <cstring>
#include <iostream>
#include <string>
#include <fstream>
using namespace std;
#define HASH_BASE 0
#define d 256
void rabinKarp(char pat[], char txt[], int q)
{
    int M = strlen(pat);
    int N = strlen(txt);
    int i, j;
    int p = 0; // hash value for pattern
    int t = 0; // hash value for txt
    int h = 1;

    for (i = 0; i < M - 1; i++)
        h = (h * d) % q;

    for (i = 0; i < M; i++)
    {
        p = (d * p + pat[i]) % q;
        t = (d * t + txt[i]) % q;
    }
    for (i = 0; i <= N - M; i++)
    {

        if (p == t)
        {
            bool flag = true;
            /* Check for characters one by one */
            for (j = 0; j < M; j++)
            {
                if (txt[i + j] != pat[j])
                {
                    flag = false;
                    break;
                }
                if (flag){}
                //   cout<<i<<" ";
            }

            // if p == t and pat[0...M-1] = txt[i, i+1, ...i+M-1]

            if (j == M)
                cout << "Pattern found at index " << i << endl;
        }
        if (i < N - M)
        {
            t = (d * (t - txt[i] * h) + txt[i + M]) % q;
            if (t < 0)
                t = (t + q);
        }
    }
}
void rabinKarpMain()
{
    FILE *fp1, *fp2;
    char ch;
    fp1 = fopen("assignment1a.txt", "r");
    fp2 = fopen("assignment2a.txt", "r");
    string str1 = "", str2 = "";
    while ((ch = fgetc(fp1)) != EOF)
    {
        str1 += ch;
    }
    while ((ch = fgetc(fp2)) != EOF)
    {
        str2 += ch;
    }
    fclose(fp1);
    fclose(fp2);

    char str1_arr[100];
    char str2_arr[100];
    strcpy(str1_arr, str1.c_str());
    strcpy(str2_arr, str2.c_str());
    int q = 13, res;
    if (str1.length() > str2.length() || str1.length() == str2.length())
    {
        rabinKarp(str2_arr, str1_arr, q);
    }
    else
    {
        rabinKarp(str1_arr, str2_arr, q);
    }
}
int main()
{

    rabinKarpMain();
}