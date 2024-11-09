#include <iostream>
#include <sstream>
#include <string>
#include <cstdlib>

using namespace std;

class Student;

#ifndef _COURSE_H_
#define _COURSE_H_

class Course
{
    private:
        
        string name;
        string code;
        Student* student_references;

    public:

        Course(string course_name, string course_code);
        Course();

        string get_name() { return name; }
        string get_code() { return code; }
        Student* get_course_references();

        ~Course();
};

#endif

#ifndef _STUDENT_H_
#define _STUDENT_H_

class Student
{
    private:
        
        string name;
        string ID;
        Course* course_references;

    public:

        Student(string student_name, string student_ID);
        Student();

        string get_name() { return name; }
        string get_ID() { return ID; }
        Course* get_course_references();

        friend ostream& operator<<(ostream& os, const Student toBePrintedStudent);

        ~Student();
};

#endif

#ifndef _SCHOOLMANAGEMENTSYSTEM_H_
#define _SCHOOLMANAGEMENTSYSTEM_H_

class SchoolManagementSystem
{
    private:
        
        Course* course_references;
        Student* student_references;
        int student_counter;
        int student_rfr_size; //number of elements of student_references
        int course_rfr_size; //number of elements of course_references

    public:

        SchoolManagementSystem();
        Course* get_course_references(void);
        Student* get_student_references(void);

        void menu(void);
            void student_menu(void);
                void add_student_to_database(void); //creates a Student object and adds it to student_references of SchoolManagementSystem
                void student_submenu(void); //for the selection 2 in the student menu
                    void delete_student_from_database(string toBeDeletedID); //frees selected Student object and its course_references in SchoolManagementSystem's student_references
                    void add_student_to_course(void); //adds selected Course object to course_references of selected Student object and adds selected Student object to student_references of selected Course object 
                    void drop_student_from_course(void); //frees the Course object in the course_references of student

        
            void course_menu(void); 
                void add_course_to_database(void); //creates a Course object and adds it to course_references
                void course_submenu(void); //for the selection 2 in the course menu
                    void delete_course_from_database(void); //frees selected course object and its student_references
                    void list_registered_students(void); //prints the student_references of the selected course
            
            void list_all_students(void); //prints the student_references of SchoolManagementSystem

            void list_all_courses(void); //prints the course_references of SchoolManagementSystem

        ~SchoolManagementSystem();

};

#endif

Course::Course(string course_name, string course_code) : name(course_name), code(course_code) 
{ 
    student_references = nullptr; 
}

Course::Course()
{
    student_references = nullptr; 
}

Course::~Course() 
{ 
    delete[] student_references; 
}

Student* Course::get_course_references() 
{ 
    return student_references; 
}

//###############################################

Student::Student(string student_name, string student_ID) : name(student_name), ID(student_ID) 
{ 
    course_references = nullptr; 
}

Student::Student()
{
    course_references = nullptr; 
}

Course* Student::get_course_references() 
{ 
    return course_references; 
}

ostream& operator<<(ostream& os, const Student toBePrintedStudent)
{
    os << toBePrintedStudent.name << ", " << toBePrintedStudent.ID << endl;
    return os;
}

Student::~Student() 
{ 
    delete[] course_references; 
}

//###############################################

SchoolManagementSystem::SchoolManagementSystem() 
{ 
    student_counter = 0; 
    student_rfr_size = 0;
    course_rfr_size = 0;

    student_references = nullptr;
    course_references = nullptr;
}

Course* SchoolManagementSystem::get_course_references(void)
{
    return course_references;
}

Student* SchoolManagementSystem::get_student_references(void)
{
    return student_references;
}

void SchoolManagementSystem::menu(void)
{
    string input;

    do {
        
        cout << "Main_menu\n"
            << "0 exit\n"
            << "1 student\n"
            << "2 course\n"
            << "3 list_all_students\n"
            << "4 list_all_courses\n"
            << ">> ";

        cin >> input;

        if (input == "0")
            exit(0);
        
        else if (input == "1")
            student_menu();
        
        else if (input == "2")
            course_menu();
        
        else if (input == "3")
            list_all_students();
        
        else if (input == "4")
            list_all_courses();
        
        else
            continue;

    } while (input != "0");
}

void SchoolManagementSystem::student_menu(void)
{
    string input;

    do {
        
        cout << "0 up\n"
             << "1 add_student\n"
             << "2 select_student\n"
             << ">> ";

        cin >> input;

        if (input == "0")
            break;
            
        else if (input == "1")
            add_student_to_database();
        
        else if (input == "2")
            student_submenu();
        
        else 
            student_menu();

    } while (input != "0");
}

void SchoolManagementSystem::add_student_to_database(void)
{
    string line; //to take the input as line
    string name1, name2, surname, id; //to extract values from line input
    student_counter++;

    //cout << "student counter:" << student_counter << endl
    //     << "student rfr size:" << student_rfr_size << endl;

    cin.ignore(numeric_limits<streamsize>::max(), '\n'); //clear the cin object
    getline(cin, line);

    istringstream iss(line); //turn line string to a stream

    iss >> name1 >> name2; //take the first two words

    string remaining;

    getline(iss, remaining); //take the rest of the line

    istringstream iss_remaining(remaining);

    if(iss_remaining >> surname >> id) //if exists take the third word and also id
    {
        name1 = name1 + " " + name2 + " " + surname;
    }

    else //if there are 2 words, take the second word and the id
    { 
        istringstream iss_remaining2(remaining);
        iss_remaining2 >> id;
        name1 = name1 + " " + name2;
    }
 
    if(student_counter >= student_rfr_size) //if existing size is not enough, increase it by 5
    {
        Student* new_student_references = new Student[student_rfr_size+5]; 

        for(int i = 0; i < student_rfr_size; i++) //assign elements to the new student references array
        {
            new_student_references[i] = student_references[i];
        } 

        delete[] student_references; //free the existing one

        student_references = new_student_references; //let the old pointer to point to new data

        student_rfr_size += 5; //increase size information
    }

    student_references[student_counter-1] = Student(name1, id); //assign the created Student object
}

void SchoolManagementSystem::delete_student_from_database(string toBeDeletedID)
{
    if(student_references == nullptr)
    {
        cout << "no student!\n";
        exit(1);
    }

    Student* new_student_references = new Student[student_rfr_size];

    for(int i = 0, j = 0; i < student_counter; i++)
    {
        if(student_references[i].get_ID() != toBeDeletedID) //if the element is not the to be deleted, put it in the new references array
        {
            new_student_references[j] = student_references[i];
            j++; //increment the index of new_student_references in just the adding case
        }
    }

    delete[] student_references;

    student_references = new_student_references;

    student_counter--;
}

void SchoolManagementSystem::add_student_to_course(void)
{
    cout << "add student to course\n";
}

void SchoolManagementSystem::drop_student_from_course(void)
{
    cout << "delete student from course\n";
}

void SchoolManagementSystem::student_submenu(void)
{
    string input;

    do {
        
        cout << "0 up\n"
             << "1 delete_student\n"
             << "2 add_selected_student_to_a_course\n"
             << ">> ";

        cin >> input;

        if (input == "0")
            break;
        
        else if (input == "1")
        {
            string id;
            cout << ">> ";
            cin >> id;
            delete_student_from_database(id);
        }
        
        else if (input == "2")
            add_student_to_course();
        
        else
            student_submenu();

    } while (input != "0");  
}

void SchoolManagementSystem::course_menu(void)
{
    string input;

    do {
        
        cout << "0 up\n"
             << "1 add_course\n"
             << "2 select_course\n"
             << ">> ";

        cin >> input;

        if (input == "0")
            break;
        
        else if (input == "1")
            add_course_to_database();
        
        else if (input == "2")
            course_submenu();
        
        else
            course_menu();

    } while (input != "0");  
}

void SchoolManagementSystem::add_course_to_database(void)
{
    cout << "add course to database\n";
}

void SchoolManagementSystem::course_submenu(void)
{
    string input;

    do {
        
        cout << "0 up\n"
             << "1 delete_course\n"
             << "2 list_students_registered_to_the_selected_course\n"
             << ">> ";

        cin >> input;

        if (input == "0")
            break;
        
        else if (input == "1")
            delete_course_from_database();
        
        else if (input == "2")
            list_registered_students();
        
        else
            course_submenu();

    } while (input != "0"); 
}

void SchoolManagementSystem::delete_course_from_database(void)
{
    cout << "delete course from database\n";
}

void SchoolManagementSystem::list_registered_students(void)
{
    cout << "list_registered_students\n";
}

void SchoolManagementSystem::list_all_students(void)
{
    for(int i = 0; i < student_counter; i++)
    {
        cout << student_references[i];
    }
}

void SchoolManagementSystem::list_all_courses(void)
{
    cout << "list_all_courses\n";
}

SchoolManagementSystem::~SchoolManagementSystem() 
{ 
    delete[] course_references;  
    delete[] student_references; 
}

int main()
{
    SchoolManagementSystem system1;

    system1.menu();

    return 0;
}