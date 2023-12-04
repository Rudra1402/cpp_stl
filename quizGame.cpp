#include <iostream>
#include <bits/stdc++.h>
using namespace std;

void setGameQuestions(map<string, vector<pair<string, pair<string, bool>>>> &questions)
{
    questions.insert({"Q1. What is the full form of ILS?", {{"A", {"Immediate Landing System", false}}, {"B", {"Instrument Landing System", true}}, {"C", {"Integrate Landing System", false}}, {"D", {"Isolate Landing System", false}}}});
    questions.insert({"Q2. How many black box(es) are there in an airplane?", {{"A", {"2", true}}, {"B", {"3", false}}, {"C", {"1", false}}, {"D", {"4", false}}}});
    questions.insert({"Q3. What is the color of black boxes?", {{"A", {"Green", false}}, {"B", {"Black", false}}, {"C", {"Blue", false}}, {"D", {"Orange", true}}}});
    questions.insert({"Q4. What is the full form of FAA?", {{"A", {"Federal Avionics Administration", false}}, {"B", {"Fedex Aviation Administration", false}}, {"C", {"Federal Aviation Administration", true}}, {"D", {"Flying Aviation Administration", false}}}});
    questions.insert({"Q5. What is the full form of RAT?", {{"A", {"Radial Air Transmission", false}}, {"B", {"Ram Air Turbine", true}}, {"C", {"Rotational Air Transmission", false}}, {"D", {"Rotational Air Turbine", false}}}});
}

void showQuestions(map<string, vector<pair<string, pair<string, bool>>>> &q, map<string, pair<string, string>> &wa, int &userScore)
{
    cout << endl;
    for (auto ques : q)
    {
        char option;
        cout << ques.first << endl;
        string correctOption;
        for (int i = 0; i < ques.second.size(); i++)
        {
            cout << ques.second[i].first << ". " << ques.second[i].second.first << endl;
            if (ques.second[i].second.second == true)
            {
                correctOption = ques.second[i].first + ". " + ques.second[i].second.first;
            }
        }
        cout << "----------" << endl;
        cout << "Select your option (A, B, C, or D): ";
        cin >> option;
        bool isInvalidOption = false;
        switch (option)
        {
        case 'A':
            cout << "You selected A." << endl;
            break;
        case 'B':
            cout << "You selected B." << endl;
            break;
        case 'C':
            cout << "You selected C." << endl;
            break;
        case 'D':
            cout << "You selected D." << endl;
            break;
        default:
            cout << "Invalid option." << endl;
            isInvalidOption = true;
            break;
        }
        cout << endl;
        if (!isInvalidOption)
        {
            if (ques.second[option - 'A'].second.second == true)
            {
                userScore++;
            }
            else
            {
                wa.insert({ques.first, {correctOption, ques.second[option - 'A'].first + ". " + ques.second[option - 'A'].second.first}});
            }
        }
        else
        {
            wa.insert({ques.first, {correctOption, "Invalid option selected!"}});
        }
    }
}

void showWrongAnswers(map<string, pair<string, string>> &wrongAnswers)
{
    for (auto wa : wrongAnswers)
    {
        cout << wa.first << endl;
        cout << "Correct: " << wa.second.first << endl;
        cout << "Your choice: " << wa.second.second << endl;
        cout << "----------" << endl;
    }
}

void playGame()
{
    map<string, vector<pair<string, pair<string, bool>>>> q;
    int userScore = 0;
    map<string, pair<string, string>> wrongAnswers;
    setGameQuestions(q);
    cout << "-----------------------------------" << endl;
    cout << "LET'S BEGIN THE GAME..." << endl;
    cout << "-----------------------------------" << endl;
    showQuestions(q, wrongAnswers, userScore);
    cout << "--- Your Score: " << userScore << "/" << q.size() << " ---" << endl;
    cout << endl;
    if (!wrongAnswers.empty())
    {
        cout << "---Incorrect Questions---" << endl
             << endl;
        showWrongAnswers(wrongAnswers);
        cout << endl;
    }
}

int main()
{
    int choice;
    bool playAgain = true;
    while (playAgain)
    {
        cout << "-----------------------" << endl;
        cout << "---- AVIATION QUIZ ----" << endl;
        cout << "-----------------------" << endl;
        cout << "1. Play" << endl
             << "2. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;
        switch (choice)
        {
        case 1:
            playGame();
            break;
        case 2:
            playAgain = false;
            break;
        default:
            playAgain = false;
            break;
        }
    }
    cout << "Goodbye!";
    return 0;
}