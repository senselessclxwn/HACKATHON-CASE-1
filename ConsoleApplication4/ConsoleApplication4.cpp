#include <iostream>
#include <vector>
#include <string>
#include <ctime>
#include <iomanip>
#include <sstream>
#include <fstream>

using namespace std;

struct Expense
{
    std::string date;
    std::string type;
    float amount;
    std::string desc;
};

static std::vector<Expense> expenses;

const std::string filename = "expenses.txt";

void saveExpenses() {
    ofstream outFile(filename);
    if (outFile.is_open()) {
        for (const auto& expense : expenses) {
            outFile << expense.date << "," << expense.type << "," << expense.amount << "," << expense.desc << endl;
        }
        outFile.close();
    }
    else {
        cout << "Error opening file for saving." << endl;
    }
}

void loadExpenses() {
    ifstream inFile(filename);
    if (inFile.is_open()) {
        string line;
        while (getline(inFile, line)) {
            stringstream ss(line);
            string date, type, desc;
            float amount;
            getline(ss, date, ',');
            getline(ss, type, ',');
            ss >> amount;
            ss.ignore();
            getline(ss, desc);
            expenses.push_back({ date, type, amount, desc });
        }
        inFile.close();
    }
    else {
        cout << "No previous expenses found. Starting fresh." << endl;
    }
}

void addExpense(const string& type, float amount, const string& desc) {
    auto t = std::time(nullptr);
    auto tm = *std::localtime(&t);
    std::stringstream date;
    date << std::put_time(&tm, "%d-%m-%Y %H:%M:%S");

    expenses.push_back({ date.str(), type, amount, desc });
}

void viewExpenses() {
    float totalAmount = 0.0f;
    for (auto i : expenses) {
        std::stringstream ss;
        ss << i.date << "    " << i.amount << "    (" << i.type << ")" << "    " << i.desc;
        cout << ss.str() << endl;
        totalAmount += i.amount;
    }
    cout << "Total expenses: " << totalAmount << endl;
}

void searchByType(const string& searchType) {
    float totalAmount = 0.0f;
    for (auto i : expenses) {
        std::stringstream ss;
        ss << i.date << "    " << i.amount << "    (" << i.type << ")" << "    " << i.desc;
        if (i.type == searchType) {
            cout << ss.str() << endl;
            totalAmount += i.amount;
        }
    }
    cout << "Total expenses: " << totalAmount << endl;
}

int main() {
    loadExpenses();

    string userInput;

    vector <string> allHelp = {
            "[add] Adds new expense. Usage : add <type> <amount> <description>\n",
            "[look] Shows all expenses.\n",
            "[search] Search expenses by type. Usage: search <type>\n",
            "[exit] Exit program.\n"
    };

    while (true) {

        cout << "Enter command: ";
        getline(cin, userInput);

        stringstream ss(userInput);
        string command;
        ss >> command;

        if (command == "exit") {
            system("cls");
            break;
        }
        else if (command == "add") {
            system("cls");
            string type, desc;
            float amount;


            ss >> type >> amount;
            getline(ss, desc);
            if (type.empty() || desc.empty() || amount <= 0) {
                cout << "Invalid input format. Please use: add <type> <amount> <description>" << endl;
            }
            else {
                addExpense(type, amount, desc);
                cout << "Successfully added!" << endl;
            }
        }
        else if (command == "look") {
            system("cls");
            viewExpenses();
        }
        else if (command == "search") {
            system("cls");
            string searchType;
            ss >> searchType;
            if (!searchType.empty()) {
                searchByType(searchType);
            }
            else {
                cout << "Please provide a type to search for." << endl;
            }
        }
        else if (command == "help") {
            system("cls");
            string commandHelp;
            ss >> commandHelp;
            if (!commandHelp.empty()) {
                if (commandHelp == "add") {
                    cout << allHelp[0];
                }
                else if (commandHelp == "look") {
                    cout << allHelp[1];
                }
                else if (commandHelp == "search") {
                    cout << allHelp[2];
                }
                else if (commandHelp == "exit") {
                    cout << allHelp[3];
                }
                else {
                    cout << "Unknown command!\n";
                }
            }
            else {
                for (const auto& helpText : allHelp) {
                    cout << helpText;
                }
            }
        }
        else {
            cout << "Unknown command!" << endl;
        }
    }

    saveExpenses();
    return 0;
}
