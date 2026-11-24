#include <iostream>
protected:
    int rollNo;
    string name;
public:
    void getStudent() 
    {
        cout << "Enter roll number: ";
        cin >> rollNo;
        cout << "Enter name: ";
        cin >> name;
    }
};
class Marks : public Student {
protected:
    float m1, m2, m3;
public:
    void getMarks() {
        cout << "Enter marks in 3 subjects: ";
        cin >> m1 >> m2 >> m3;
    }
};
class Result : public Marks {
public:
    void display() {
        float total = m1 + m2 + m3;
        float percentage = total / 3;
        cout << "\nRoll No: " << rollNo;
        cout << "\nName: " << name;
        cout << "\nTotal: " << total;
        cout << "\nPercentage: " << percentage << "%";
        if (percentage >= 90)
            cout << "\nGrade: A";
        else if (percentage >= 75)
            cout << "\nGrade: B";
        else if (percentage >= 60)
            cout << "\nGrade: C";
        else if (percentage >= 40)
            cout << "\nGrade: D";
        else
            cout << "\nGrade: F";
    }
};
int main() {
    Result r;
    r.getStudent();
    r.getMarks();
    r.display();
    return 0;
}