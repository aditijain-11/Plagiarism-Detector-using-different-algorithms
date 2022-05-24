#include <bits/stdc++.h>
#include <fstream>
#include <string>
using namespace std;
#define HASH_BASE 0
#define NO_OF_CHARS 256
#define d 256

// function declaration
void convertingToLowerCase(char *input, int n);
void removeSpecialCharacters();
void chose();
void direct(int n);
int min2(int a, int b);
int min3(int a, int b, int c);
int levenFun(string str1, string str2);
void levenMain();
void badCharHeuristic(string str, int size,int badchar[NO_OF_CHARS]);
int search(string txt, string pat);
void boyerMain();
void rabinKarp(char pat[], char txt[], int q);
void rabinKarpMain();
double jaro_distance(string s1, string s2);
void jaroMain();
void computeLPSArray(string pat, int M, int* lps);
int  KMPSearch(string pat, string txt);
void KMPmain();
void direct(int n);
void chose();
// code implemented
// CONVERTING INPUT FILE TEXT TO LOWER CASE
void convertingToLowerCase(char *input, int n)
{
    FILE *fp1, *fp2;
    char ch;
    fp1 = fopen(input, "r");
    if (n == 1)
    {
        fp2 = fopen("assignment1.txt", "w");
    }
    else
    {
        fp2 = fopen("assignment2.txt", "w");
    }
    while ((ch = fgetc(fp1)) != EOF)
    {
        ch = tolower(ch);
        fputc(ch, fp2);
    }
    fclose(fp1);
    fclose(fp2);
    remove(input);
}
// REMOVE SPECIAL CHARACTERS FROM THE FILE
void removeSpecialCharacters()
{
    FILE *fp1, *fp2;
    char ch;
    fp1 = fopen("assignment1.txt", "r");
    fp2 = fopen("assignment1a.txt", "w");
    while ((ch = fgetc(fp1)) != EOF)
    {
        if ((ch >= 'A' && ch <= 'Z') || (ch >= 'a' && ch <= 'z'))
        {
            fputc(ch, fp2);
        }
    }
    fclose(fp1);
    fclose(fp2);
    remove("assignment1.txt");

    FILE *fp1_, *fp2_;
    char ch2;
    fp1_ = fopen("assignment2.txt", "r");
    fp2_ = fopen("assignment2a.txt", "w");
    while ((ch2 = fgetc(fp1)) != EOF)
    {
        if ((ch2 >= 'A' && ch2 <= 'Z') || (ch2 >= 'a' && ch2 <= 'z'))
        {
            fputc(ch2, fp2_);
        }
    }
    fclose(fp1_);
    fclose(fp2_);
    remove("assignment2.txt");
}
// FINDING MINIMUM ELEMENT BETWEEN TWO ELEMENTS
int min2(int a, int b)
{
    return a < b ? a : b;
}
// FINDING MINIMUM ELEMENTS BETWEEN THREE ELEMENTS
int min3(int a, int b, int c)
{
    return min2(a, min2(b, c));
}
char *strlwr(char *str)
{
    char *p = (char *)str;
    while (*p)
    {
        *p = tolower((char)*p);
        p++;
    }
    return str;
}

// // BUILDING LEVENSHTIEN CODE
int MIN(int x, int y)
{
    return ((x) < (y) ? (x) : (y));
}
int max2(int a, int b)
{
    return a > b ? a : b;
}
int levenFun(string str1, string str2)
{
    int i, j, l1, l2, t, track, len1, len2;
    int dist[50][50];
    //taking length of input strings
    len1 = str1.size();
    len2 = str2.size();
    //take the strings as input
    char s1[len1 + 1];
    char s2[len2 + 1];
    //string to char
    strcpy(s1, str1.c_str());
    strcpy(s2, str2.c_str());
    // stores the lenght of strings s1 and s2
    l1 = strlen(s1);
    l2 = strlen(s2);
    for (i = 0; i <= l1; i++)
    {
        dist[0][i] = i;
    }
    for (j = 0; j <= l2; j++)
    {
        dist[j][0] = j;
    }
    for (j = 1; j <= l1; j++)
    {
        for (i = 1; i <= l2; i++)
        {
            if (s1[i - 1] == s2[j - 1])
            {
                track = 0;
            }
            else
            {
                track = 1;
            }
            t = MIN((dist[i - 1][j] + 1), (dist[i][j - 1] + 1));
            dist[i][j] = MIN(t, (dist[i - 1][j - 1] + track));
        }
    }
    // cout<<dist[l2][l1];
    return dist[l2][l1];
}
void levenMain()
{
    string str1, str2, buffer;
    ifstream input1("assignment1a.txt");
    while (getline(input1, buffer))
        str1 += (buffer + '\n');
    ifstream input2("assignment2a.txt");
    while (getline(input2, buffer))
        str2 += (buffer + '\n');
    int maximum = max2(str1.size(), str2.size())-1;
    // cout<<maximum;
    int leven = levenFun(str1, str2);
    float per = ((float)leven / (float)maximum) * 100;
    if (per >= 75 && per <= 100)
    {
        cout <<"non-plagiarism rate: "<<per<<"%"<< " Voila! Original submission.\nacceptable submission good job!" << endl;
    }
    else if (per < 75 && per >= 45)
    {
        cout << "non-plagiarism rate: "<<per<< "%"<<" likely to be not plagiarised!\nacceptable submission good job!"  << endl;
    }
    else if (per >= 10 && per < 45)
    {
        cout <<"non-plagiarism rate: "<<per<<"%"<< " Fairly Plagiarised!\nacceptable submission but research marks should be deducted." << endl;
    }
    else
    {
        cout << "non-plagiarism rate: "<<per<< "%"<<" Highly plagiarised!\nunacceptable submission." << endl;
    }
}
// LEVENSHTEIN CODE ENDED

// RABIN KARP CODE STARTING
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

            if (j == M){
                cout << "Plagiarism detected! " << endl;
            }
            else{
                cout<<"non plagiarised file!"<<endl;
            }
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
// RABIN KARP CODE ENDED
// BOYER MOORE HORSPOOL

void badCharHeuristic(string str, int size,
                      int badchar[NO_OF_CHARS])
{
    int i;
    for (i = 0; i < NO_OF_CHARS; i++)
        badchar[i] = -1;
    for (i = 0; i < size; i++)
        badchar[(int)str[i]] = i;
}

int search(string txt, string pat)
{
    int res(0);
    int m = pat.size();
    int n = txt.size();

    int badchar[NO_OF_CHARS];
    badCharHeuristic(pat, m, badchar);

    int s = 0;
    while (s <= (n - m))
    {
        int j = m - 1;
        while (j >= 0 && pat[j] == txt[s + j])
            j--;
        if (j < 0)
        {
            res = 1;
            s += (s + m < n) ? m - badchar[txt[s + m]] : 1;
        }

        else
            s += max(1, j - badchar[txt[s + j]]);
    }
    return res;
}
void boyerMain()
{
    string str1, str2, buffer;
    ifstream input1("assignment1a.txt");
    while (getline(input1, buffer))
        str1 += (buffer + '\n');
    ifstream input2("assignment2a.txt");
    while (getline(input2, buffer))
        str2 += (buffer + '\n');
    int x = search(str1, str2);
    if (x == 1)
    {
        cout << "assignment is plagiarised!";
    }
    else
    {
        cout << "assignment not plagiarised!";
    }
}
// BOYER MOORE HORSEPOOL ENDED

// JARO-WRINKLER CODE STARTING
double jaro_distance(string s1, string s2)
{
    if (s1 == s2)
        return 1.0;
    int len1 = s1.length(),
        len2 = s2.length();
    int max_dist = floor(max(len1, len2) / 2) - 1;
    int match = 0;
    int hash_s1[s1.length()] = {0},
        hash_s2[s2.length()] = {0};
    for (int i = 0; i < len1; i++)
    {
        for (int j = max(0, i - max_dist);
             j < min(len2, i + max_dist + 1); j++)
            if (s1[i] == s2[j] && hash_s2[j] == 0)
            {
                hash_s1[i] = 1;
                hash_s2[j] = 1;
                match++;
                break;
            }
    }
    if (match == 0)
        return 0.0;
    double t = 0;
    int point = 0;
    for (int i = 0; i < len1; i++)
        if (hash_s1[i])
        {

            while (hash_s2[point] == 0)
                point++;

            if (s1[i] != s2[point++])
                t++;
        }
    t /= 2;
    return (((double)match) / ((double)len1) + ((double)match) / ((double)len2) + ((double)match - t) / ((double)match)) / 3.0;
}
void jaroMain()
{
    string str1;
    string str2;
    string buffer;
    ifstream input1("assignment1a.txt");
    while (getline(input1, buffer))
        str1 += (buffer + '\n');
    ifstream input2("assignment2a.txt");
    while (getline(input2, buffer))
        str2 += (buffer + '\n');
    double res = jaro_distance(str1, str2);
    if (res == 1)
    {
        cout << "plagiarised";
    }
    else
    {
        cout << "not plagiarised";
    }
}
// JARO WRINKLE ENDED
// KNUTH MORRIS PRATT STARTING
void computeLPSArray(string pat, int M, int* lps)
{
	// length of the previous longest prefix suffix
	int len = 0;

	lps[0] = 0; // lps[0] is always 0

	// the loop calculates lps[i] for i = 1 to M-1
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
int  KMPSearch(string pat, string txt)
{   int res = 0;
	int M = pat.length();
	int N = txt.length();
	// create lps[] that will hold the longest prefix suffix
	// values for pattern
	int lps[M];
	// Preprocess the pattern (calculate lps[] array)
	computeLPSArray(pat, M, lps);
	int i = 0; 
	int j = 0;  
	while (i < N) {
		if (pat[j] == txt[i]) {
			j++;
			i++;
		}

		if (j == M) {
			int res = 1;
			//printf("Found pattern at index %d ", i - j);
			j = lps[j - 1];
		}
		else if (i < N && pat[j] != txt[i]) {
			 
			if (j != 0)
				j = lps[j - 1];
			else
				i = i + 1;
		}
	}
	return 0;
}
void KMPmain(){
    string str1;
        string str2;
        string buffer;
        ifstream input1("assignment1a.txt");
        while (getline(input1, buffer))
            str1 += (buffer + '\n');
        ifstream input2("assignment2a.txt");
        while (getline(input2, buffer))
            str2 += (buffer + '\n');
        int res = KMPSearch(str1, str2);
        if(res==0){
            cout<<"not Plagiarised!"<<endl;
        }
        else{
            cout<<"plagiarised document!"<<endl;
        }
}
// KNUTH MORISS PRATT ENDED
void direct(int n)
{
    if (n == 1)
    {
        levenMain();
    }
    else if (n == 2)
    {
        rabinKarpMain();
    }
    else if (n == 3)
    {
        boyerMain();
    }
    else if (n == 4)
    {
        jaroMain();
    }
    else if(n == 5){
        KMPmain();
    }
    else
    {
        cout<<"NULL";
    }
}
void chose()
{
    int n;
    cout << "\nFollowing are the list of algorithm you want to use for detecting plagiarism in the assignments";
    cout << "\n1:Levenshtein Algorithm";
    cout << "\n2:Boyer Moore Horspool Algorithm";
    cout << "\n3:Rabin-Karp Algorithm";
    cout << "\n4:Jaro-Winkler Algorithm";
    cout << "\n5:Knuth Morris Pratt Algorithm";
    cout << "\nEnter the index of algorithm you want to select: ";
    cin >> n;
    direct(n);
}

int main()
{
    char input1[10000], input2[10000];
    cout << "Enter the name of first document: ";
    cin >> input1;
    cout << "Enter the name of second document: ";
    cin >> input2;
    convertingToLowerCase(input1, 1);
    convertingToLowerCase(input2, 2);
    removeSpecialCharacters();
    chose();
}
