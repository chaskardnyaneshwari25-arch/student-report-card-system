#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <limits>
#include <stdexcept>
#include <iomanip>
using namespace std;

class Student
{
private:
    int rollNo;
    string name;
    int marks[5];

public:

    // Accept and validate student details.
    void inputDetails()
    {

        cout << "\nEnter Roll Number: ";
        cin >> rollNo;
        if (cin.fail() || rollNo <= 0)
            throw invalid_argument("Invalid roll number!");

        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Enter Student Name: ";
        getline(cin, name);
        if (name.empty() || name.find('|') != string::npos)
            throw invalid_argument("Invalid student name!");


        cout << "\nEnter marks for 5 subjects (0-100):\n";
        for (int i = 0; i < 5; i++)
        {
            cout << "Subject " << i + 1 << ": ";
            cin >> marks[i];
            if (cin.fail() || marks[i] < 0 || marks[i] > 100)
                throw invalid_argument("Invalid marks! Enter marks between 0 and 100.");
        }
    }


    // Calculate the sum of all five subjects.
    int calculateTotal()
    {
        int total = 0;
        for (int i = 0; i < 5; i++)
            total += marks[i];
        return total;
    }


    // Calculate percentage using the maximum possible marks.
    double calculatePercentage(int maxMarks)
    {
        if (maxMarks == 0)
            throw runtime_error("Division by zero is not allowed!");
        return calculateTotal() * 100.0 / maxMarks;
    }


    // Assign a grade according to the percentage.
    string calculateGrade()
    {
        double percentage = calculatePercentage(500);
        if (percentage >= 90) return "A+";
        else if (percentage >= 80) return "A";
        else if (percentage >= 70) return "B";
        else if (percentage >= 60) return "C";
        else if (percentage >= 40) return "D";
        else return "F";
    }


    // Display the complete report card.
    void display()
    {
        cout << "\n----------------------------------\n";
        cout << "       STUDENT REPORT CARD\n";
        cout << "----------------------------------\n";
        cout << "Roll Number : " << rollNo << endl;
        cout << "Name        : " << name << endl;

        for (int i = 0; i < 5; i++)
            cout << "Subject " << i + 1 << " : "
                 << marks[i] << "/100" << endl;


        cout << "Total Marks : " << calculateTotal() << "/500" << endl;
        cout << fixed << setprecision(2);
        cout << "Percentage  : " << calculatePercentage(500) << "%" << endl;
        cout << "Grade       : " << calculateGrade() << endl;
        cout << "----------------------------------\n";
    }


    // Append the student's record to the text file.
    void saveToFile()
    {
        ofstream file("students.txt", ios::app);
        if (!file)
            throw runtime_error("Unable to open file for writing!");


        file << rollNo << "|" << name;
        for (int i = 0; i < 5; i++)
            file << "|" << marks[i];
        file << endl;

        cout << "\nStudent record saved successfully!\n";
    }


    // Convert one line from the file into a Student object.
    static bool readRecord(string line, Student &s)
    {
        stringstream ss(line);
        string value;

        try
        {
            if (!getline(ss, value, '|')) return false;
            s.rollNo = stoi(value);
            if (s.rollNo <= 0 || !getline(ss, s.name, '|')) return false;


            for (int i = 0; i < 5; i++)
            {
                if (!getline(ss, value, '|')) return false;
                s.marks[i] = stoi(value);
                if (s.marks[i] < 0 || s.marks[i] > 100) return false;
            }
        }
        catch (...)
        {
            return false;
        }
        return true;
    }


    // Read and display every valid student record.
    static void displayAll()
    {
        ifstream file("students.txt");
        if (!file)
            throw runtime_error("File not found! Add a student first.");

        string line;
        bool found = false;

        while (getline(file, line))
        {
            Student s;
            if (readRecord(line, s))
            {
                s.display();
                found = true;
            }
        }
        if (!found)
            cout << "\nNo student records available.\n";
    }


    // Find and display a student using the roll number.
    static void searchStudent(int searchRoll)
    {
        ifstream file("students.txt");
        if (!file)
            throw runtime_error("File not found!");

        string line;
        bool found = false;
        while (getline(file, line))
        {
            Student s;
            if (readRecord(line, s) && s.rollNo == searchRoll)
            {
                s.display();
                found = true;
                break;
            }
        }
        if (!found)
            cout << "\nStudent record not found!\n";
    }
};


// Main menu of the Student Report Card System.
int main()
{
    int choice = 0;
    do
    {
        cout << "\n================================\n";
        cout << "   STUDENT REPORT CARD SYSTEM\n";
        cout << "================================\n";
        cout << "1. Add Student Record\n";
        cout << "2. Display All Records\n";
        cout << "3. Search Student Record\n";
        cout << "4. Exit\n";
        cout << "\nEnter your choice: ";


        if (!(cin >> choice))
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "\nInvalid input! Enter a number.\n";
            continue;
        }

        try
        {
            switch (choice)
            {
                case 1:
                {
                    Student s;
                    s.inputDetails();
                    s.display();
                    s.saveToFile();
                    break;
                }
                case 2:
                    Student::displayAll();
                    break;
                case 3:
                {
                    int roll;
                    cout << "Enter Roll Number to Search: ";
                    if (!(cin >> roll) || roll <= 0)
                        throw invalid_argument("Invalid roll number!");
                    Student::searchStudent(roll);
                    break;
                }
                case 4:
                    cout << "\nThank you for using the system!\n";
                    break;
                default:
                    cout << "\nInvalid choice! Try again.\n";
            }
        }

        catch (const exception &e)
        {
            cout << "\nError: " << e.what() << endl;
            if (cin.fail())
            {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
        }
    } while (choice != 4);

    return 0;
}
