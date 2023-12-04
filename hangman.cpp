#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <cctype>
#include <bits/stdc++.h>
using namespace std;

void readDictionary(vector<pair<string, int>> &v)
{
    ifstream file("dictionary.txt");

    if (!file.is_open())
    {
        cerr << "Error opening file." << endl;
    }

    string line;
    while (getline(file, line))
    {
        string formattedLine = "";
        for (int i = 0; i < line.size(); i++)
        {
            if (isalpha(line[i]))
            {
                formattedLine += line[i];
            }
        }
        v.push_back({formattedLine, formattedLine.size()});
    }

    file.close();
}

void generateRandomNumber(int &arrSize, int &randNum)
{
    srand(static_cast<unsigned int>(std::time(nullptr)));
    randNum = rand() % arrSize;
}

void playGame(string word, int len)
{
    string coveredWord = "";
    int coveredLen = len;
    for (int i = 0; i < len; i++)
    {
        coveredWord += "_";
    }
    vector<char> enterredLetters;
    string remainingChances = "hangman";
    int remainingChancesLen = remainingChances.length();
    char letter;
    while (remainingChancesLen > 0 && coveredLen > 0)
    {
        cout << "Chances Remaining: " << remainingChances << " (" << remainingChancesLen << ")" << endl;
        cout << endl;
        cout << "Word: ";
        for (int i = 0; i < len; i++)
        {
            cout << coveredWord[i] << " ";
        }
        cout << endl;
        cout << endl;
        cout << "Enter letter: ";
        cin >> letter;
        auto it = find(enterredLetters.begin(), enterredLetters.end(), letter);
        while (it != enterredLetters.end())
        {
            cout << "Already enterred this letter. Enter again: ";
            cin >> letter;
            it = find(enterredLetters.begin(), enterredLetters.end(), letter);
        }
        enterredLetters.push_back(letter);
        bool flag = false;
        for (int i = 0; i < len; i++)
        {
            if (word[i] == letter)
            {
                coveredWord[i] = letter;
                coveredLen--;
                flag = true;
            }
        }
        if (!flag)
        {
            remainingChancesLen--;
            remainingChances = remainingChances.substr(0, remainingChancesLen);
        }
        cout << endl;
    }
    if (remainingChancesLen == 0)
    {
        cout << "Oops! You ran out of chances." << endl
             << "Word: " << word << endl
             << endl;
    }
    if (coveredLen == 0)
    {
        cout << "Congratulation! you guessed it correct!" << endl
             << "Word: " << coveredWord << endl
             << endl;
    }
}

int main()
{
    vector<pair<string, int>> words;
    readDictionary(words);
    int randomNumber, wordSize = words.size();
    int choice;
    bool flag = true;
    while (flag)
    {
        cout << "-----------------" << endl;
        cout << "---- HANGMAN ----" << endl;
        cout << "-----------------" << endl;
        cout << "1. Play" << endl
             << "2. Exit" << endl;
        cout << "Enter choice: ";
        cin >> choice;
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        switch (choice)
        {
        case 1:
            cout << endl;
            generateRandomNumber(wordSize, randomNumber);
            playGame(words[randomNumber].first, words[randomNumber].second);
            break;
        case 2:
            flag = false;
            break;
        default:
            flag = false;
            break;
        }
    }
    cout << "Goodbye!";
    return 0;
}