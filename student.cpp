#include<iostream>
using namespace std;

class student
{
int rollNo;
string name;
float marks;

public:
    student(int rollNo, string namee, float marks)
    {
        this->rollNo= rollNo;
        this->name=name;
        this->marks=marks;
    }
    void display(){
    cout<<"Roll No:"<<rollNo<<endl;
    cout<<"Name:"<<name<<endl;
    cout<<"Marks :"<<marks<<endl;
    }
};
int main()
{
    student s(12,"priya",100.8);
    s.display();
    return 0;
}
