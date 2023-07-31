#include <iostream>
#include <vector>
#include <list>
#include <string>
#include <ctime>
#include <fstream>
#include <conio.h>
using namespace std;
#include "header.h"
#include "menu.h"

int main()
{
    Quiz myQuiz("Sample Quiz");

    Question* question1 = new Question(
        "What is the capital of France?",
        { "Paris", true },
        { "Berlin", false },
        { "Madrid", false },
        { "London", false }
    );

    Question* question2 = new Question(
        "What is the largest planet in our solar system?",
        { "Jupiter", true },
        { "Mars", false },
        { "Venus", false },
        { "Saturn", false }
    );

    myQuiz._questions.push_back(question1);
    myQuiz._questions.push_back(question2);

    myQuiz.save();
}