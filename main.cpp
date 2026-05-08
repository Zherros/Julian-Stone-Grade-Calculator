#include <iostream>
#include <vector>
#include <iomanip>
#include <memory>
#include <string>
#include <stack>
#include <limits>
#include "GradedItem.h"
#include "Homework.h"
#include "Quiz.h"
#include "Exam.h"

using namespace std;

// Input validation function
template <typename T>
void getInput(T& variable, const string& prompt) {
    while (true) {
        cout << prompt;
        cin >> variable;

        if (cin.fail()) {
            cin.clear(); // Clear error flags
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
            cout << "Invalid input. Please enter a number.\n";
        } else {
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard any leftover input
            break;
        }
    }
}

struct GradingScheme {
    float homeworkWeight = 0.20f;
    float quizWeight = 0.30f;
    float examWeight = 0.50f;
    float cutoffA = 90.0f;
    float cutoffB = 80.0f;
    float cutoffC = 70.0f;
    float cutoffD = 60.0f;
};

struct Action {
    enum ActionType { ADD, REMOVE } type;
    shared_ptr<GradedItem> item;
    size_t index;
};

void displayHeader(const string& title) {
    cout << "\n";
    cout << string(50, '=') << '\n';
    cout << "  " << title << '\n';
    cout << string(50, '=') << '\n';
}

void displaySeparator() {
    cout << string(50, '-') << '\n';
}

void displayMenu() {
    displayHeader("GRADE CALCULATOR - MAIN MENU");
    cout << "1. Set Grading Scheme\n";
    cout << "2. Add Graded Item\n";
    cout << "3. View All Items\n";
    cout << "4. Remove Item\n";
    cout << "5. Calculate Grade (Points-Based)\n";
    cout << "6. Calculate Grade (Weighted)\n";
    cout << "7. Undo Last Action\n";
    cout << "0. Exit\n";
    displaySeparator();
}

char getColoredLetterGrade(float percentage, const GradingScheme& scheme) {
    string colorCode;
    char grade;
    if (percentage >= scheme.cutoffA) {
        grade = 'A';
        colorCode = "\033[32m"; // Green
    } else if (percentage >= scheme.cutoffB) {
        grade = 'B';
        colorCode = "\033[34m"; // Blue
    } else if (percentage >= scheme.cutoffC) {
        grade = 'C';
        colorCode = "\033[33m"; // Yellow
    } else if (percentage >= scheme.cutoffD) {
        grade = 'D';
        colorCode = "\033[35m"; // Magenta
    } else {
        grade = 'F';
        colorCode = "\033[31m"; // Red
    }
    cout << colorCode << "Letter Grade: " << grade << "\033[0m\n"; // Reset
    return grade;
}

void setGradingScheme(GradingScheme& scheme) {
    displayHeader("SET GRADING SCHEME");
    cout << "-- Category Weights --\n";
    float hw, qz, ex;
    getInput(hw, "Enter weight for Homework (%): ");
    getInput(qz, "Enter weight for Quizzes (%): ");
    getInput(ex, "Enter weight for Exams (%): ");

    float total = hw + qz + ex;
    if (total != 100.0f) {
        cout << "Weights must sum to 100%. Got " << total << "%. Try again.\n";
        return;
    }

    scheme.homeworkWeight = hw / 100.0f;
    scheme.quizWeight = qz / 100.0f;
    scheme.examWeight = ex / 100.0f;
    cout << "Weights saved!\n";

    cout << "\n-- Letter Grade Cutoffs --\n";
    getInput(scheme.cutoffA, "Enter minimum % for A: ");
    getInput(scheme.cutoffB, "Enter minimum % for B: ");
    getInput(scheme.cutoffC, "Enter minimum % for C: ");
    getInput(scheme.cutoffD, "Enter minimum % for D: ");
    cout << "Cutoffs saved!\n";
}

void addGradedItem(vector<shared_ptr<GradedItem>>& items, stack<Action>& actions) {
    displayHeader("ADD GRADED ITEM");
    cout << "Select category:\n";
    cout << "1. Homework\n";
    cout << "2. Quiz\n";
    cout << "3. Exam\n";
    cout << "Choice: ";

    int category;
    getInput(category, "Choice: ");

    cout << "Name: ";
    string name;
    getline(cin, name);

    float possible, earned;
    getInput(possible, "Points possible: ");
    getInput(earned, "Points earned: ");

    shared_ptr<GradedItem> item;
    switch (category) {
        case 1:
            item = make_shared<Homework>(name, earned, possible);
            break;
        case 2:
            item = make_shared<Quiz>(name, earned, possible);
            break;
        case 3:
            item = make_shared<Exam>(name, earned, possible);
            break;
        default:
            cout << "Invalid category.\n";
            return;
    }
    items.push_back(item);
    actions.push({Action::ADD, item, items.size() - 1});
    cout << "Item added!\n";
}

void viewItems(const vector<shared_ptr<GradedItem>>& items) {
    displayHeader("ALL GRADED ITEMS");
    if (items.empty()) {
        cout << "No items entered yet.\n";
        return;
    }

    cout << left << setw(5) << "#"
         << setw(20) << "Name"
         << setw(12) << "Category"
         << right << setw(10) << "Earned"
         << setw(10) << "Possible"
         << setw(10) << "Percent" << '\n';
    displaySeparator();
    cout << fixed << setprecision(1);
    for (size_t i = 0; i < items.size(); ++i) {
        cout << left << setw(5) << (i + 1)
             << setw(20) << items[i]->getName()
             << setw(12) << items[i]->getCategory()
             << right << setw(10) << items[i]->getPointsEarned()
             << setw(10) << items[i]->getPointsPossible()
             << setw(9) << items[i]->getPercentage() << "%\n";
    }
}

void removeItem(vector<shared_ptr<GradedItem>>& items, stack<Action>& actions) {
    displayHeader("REMOVE ITEM");
    if (items.empty()) {
        cout << "No items to remove.\n";
        return;
    }
    size_t i;
    for (i = 0; i < items.size(); ++i) {
        cout << (i + 1) << ". " << items[i]->getCategory()
             << " - " << items[i]->getName() << '\n';
    }
    int index;
    getInput(index, "Enter item number to remove (0 to cancel): ");

    if (index < 1 || index > static_cast<int>(items.size())) {
        cout << "Cancelled.\n";
        return;
    }

    actions.push({Action::REMOVE, items[index - 1], static_cast<size_t>(index - 1)});
    cout << "Removed: " << items[index - 1]->getName() << '\n';
    items.erase(items.begin() + (index - 1));
}

void undoLastAction(vector<shared_ptr<GradedItem>>& items, stack<Action>& actions) {
    if (actions.empty()) {
        cout << "No actions to undo.\n";
        return;
    }

    Action lastAction = actions.top();
    actions.pop();

    if (lastAction.type == Action::ADD) {
        items.pop_back();
        cout << "Last added item removed.\n";
    } else if (lastAction.type == Action::REMOVE) {
        items.insert(items.begin() + lastAction.index, lastAction.item);
        cout << "Last removed item restored.\n";
    }
}

void calculatePointsBased(const vector<shared_ptr<GradedItem>>& items, const GradingScheme& scheme) {
    displayHeader("POINTS-BASED GRADE");
    if (items.empty()) {
        cout << "No items to calculate.\n";
        return;
    }

    float totalEarned = 0, totalPossible = 0;
    for (const auto& item : items) {
        totalEarned += item->getPointsEarned();
        totalPossible += item->getPointsPossible();
    }

    float percentage = (totalPossible > 0) ? (totalEarned / totalPossible) * 100 : 0;

    cout << fixed << setprecision(1);
    cout << "Total Earned: " << totalEarned << " / " << totalPossible << '\n';
    cout << "Overall: " << percentage << "%\n";

    getColoredLetterGrade(percentage, scheme);
}

void calculateWeighted(const vector<shared_ptr<GradedItem>>& items, const GradingScheme& scheme) {
    displayHeader("WEIGHTED GRADE CALCULATION");
    if (items.empty()) {
        cout << "No items to calculate.\n";
        return;
    }

    float hwTotal = 0, hwCount = 0;
    float quizTotal = 0, quizCount = 0;
    float examTotal = 0, examCount = 0;

    for (const auto& item : items) {
        if (item->getCategory() == "Homework") {
            hwTotal += item->getPercentage();
            hwCount++;
        } else if (item->getCategory() == "Quiz") {
            quizTotal += item->getPercentage();
            quizCount++;
        } else if (item->getCategory() == "Exam") {
            examTotal += item->getPercentage();
            examCount++;
        }
    }

    float hwAvg = hwCount > 0 ? hwTotal / hwCount : 0;
    float quizAvg = quizCount > 0 ? quizTotal / quizCount : 0;
    float examAvg = examCount > 0 ? examTotal / examCount : 0;

    float finalGrade = (hwAvg * scheme.homeworkWeight)
                     + (quizAvg * scheme.quizWeight)
                     + (examAvg * scheme.examWeight);

    cout << fixed << setprecision(1);
    cout << "Homework Average:  " << hwAvg << "% ("
         << (scheme.homeworkWeight * 100) << "% weight)\n";
    cout << "Quiz Average:      " << quizAvg << "% ("
         << (scheme.quizWeight * 100) << "% weight)\n";
    cout << "Exam Average:      " << examAvg << "% ("
         << (scheme.examWeight * 100) << "% weight)\n";
    cout << "\nFinal Weighted Grade: " << finalGrade << "%\n";
    cout << "Letter Grade: " << getColoredLetterGrade(finalGrade, scheme) << '\n';
}

int main() {
    GradingScheme scheme;
    vector<shared_ptr<GradedItem>> items;
    stack<Action> actions;

    int choice = 0;
    do {
        displayMenu();
        getInput(choice, "Enter choice: ");

        switch (choice) {
            case 1: setGradingScheme(scheme); break;
            case 2: addGradedItem(items, actions); break;
            case 3: viewItems(items); break;
            case 4: removeItem(items, actions); break;
            case 5: calculatePointsBased(items, scheme); break;
            case 6: calculateWeighted(items, scheme); break;
            case 7: undoLastAction(items, actions); break;
            case 0:
                displayHeader("GOODBYE");
                cout << "Thank you for using Grade Calculator!\n";
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 0);

    return 0;
}
