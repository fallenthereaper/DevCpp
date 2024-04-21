#include "practice.h";
#include "main.h";

using namespace std;

namespace Practice {
    const int numQuestions = 10;
    const int numOptions = 4;


    void displayQuestions(const string questions[], int questionsSize, const string options[][4], int optionsSize) {
        for (int i = 0; i < questionsSize; i++) {
            cout << questions[i] << endl;
            for (int j = 0; j < 4; j++) {
                cout << options[i][j] << endl;
            }
            cout << endl;
        }
    }



    void startUp() {

       

        string questions[numQuestions] = {
        "What is the capital of France?",
        "Which planet is known as the Red Planet?",
        "Who wrote 'Romeo and Juliet'?",
        "What is the largest mammal in the world?",
        "Which country is famous for the Taj Mahal?",
        "What is the powerhouse of the cell?",
        "Which programming language is often used for game development?",
        "What year did the Titanic sink?",
        "Which ocean is the largest?",
        "Who painted the Mona Lisa?"
        };

        string options[numQuestions][numOptions] = {
        {"A) London", "B) Paris", "C) Berlin", "D) Madrid"},
        {"A) Venus", "B) Mars", "C) Jupiter", "D) Saturn"},
        {"A) William Shakespeare", "B) Jane Austen", "C) Charles Dickens", "D) Mark Twain"},
        {"A) Elephant", "B) Blue Whale", "C) Giraffe", "D) Hippopotamus"},
        {"A) India", "B) Egypt", "C) China", "D) Italy"},
        {"A) Nucleus", "B) Mitochondrion", "C) Ribosome", "D) Chloroplast"},
        {"A) Java", "B) C++", "C) Python", "D) Ruby"},
        {"A) 1912", "B) 1923", "C) 1901", "D) 1945"},
        {"A) Atlantic Ocean", "B) Indian Ocean", "C) Pacific Ocean", "D) Arctic Ocean"},
        {"A) Vincent van Gogh", "B) Leonardo da Vinci", "C) Pablo Picasso", "D) Michelangelo"}
        };


        char correctAnswers[numQuestions] = { 'B', 'B', 'A', 'B', 'A', 'B', 'B', 'A', 'C', 'B' };


        int score = 0;




}

}
