#include <iostream>
#include <sstream>
#include <string>
#include <cstdlib>

using namespace std;

namespace PA3
{
    class Student;

    #ifndef _COURSE_H_
    #define _COURSE_H_

    class Course
    {
        private:
            
            string name;
            string code;
            Student** student_references;
            int student_rfr_size; //number of elements of student_references
            int student_counter;

        public:

            Course(string course_name, string course_code);
            Course();

            string get_name() { return name; }
            string get_code() { return code; }
            int& get_student_counter() { return student_counter; }
            int& get_student_rfr_size() { return student_rfr_size; }
            Student*** get_student_references();
            Student** get_student_referencess();
            int find_student_index(string name, string id);

            friend ostream& operator<<(ostream& os, Course toBePrintedCourse);

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
            Course** course_references;
            int course_rfr_size; //number of elements of course_references
            int course_counter;

        public:

            Student(string student_name, string student_ID);
            Student();

            string get_name() { return name; }
            string get_ID() { return ID; }
            Course*** get_course_references();
            Course** get_course_referencess();
            int& get_course_counter() { return course_counter; }
            int& get_course_rfr_size() { return course_rfr_size; }
            int find_course_index(string name, string code);

            friend ostream& operator<<(ostream& os, Student toBePrintedStudent);

            ~Student();
    };

    #endif

    #ifndef _SCHOOLMANAGEMENTSYSTEM_H_
    #define _SCHOOLMANAGEMENTSYSTEM_H_

    class SchoolManagementSystem
    {
        private:
            
            Course** course_references;
            Student** student_references;
            int student_counter;
            int course_counter;
            int student_rfr_size; //number of elements of student_references
            int course_rfr_size; //number of elements of course_references
            int find_student_index(string name, string id);
            int find_course_index(string name, string code);
            void add_student_to_courses_references(int studentIndex); //adds the student which takes the course to student references of course
            void add_course_to_students_references(int courseIndex, int studentIndex); //adds the course to course references of the student which is gonna take the course

        public:

            SchoolManagementSystem();
            Course** get_course_references(void);
            Student** get_student_references(void);

            void menu(void);
                void student_menu(void);
                    void add_student_to_database(string name, string id); //creates a Student object and adds it to student_references of SchoolManagementSystem
                    void student_submenu(string name, string id); //for the selection 2 in the student menu
                        void delete_student_from_database(int studentIndex); //frees selected Student object and its course_references in SchoolManagementSystem's student_references
                        void add_student_to_course(int studentIndex); //adds selected Course object to course_references of selected Student object and adds selected Student object to student_references of selected Course object 
                        void drop_student_from_all_courses(Student* toBeDeletedStudent); //frees the Course object in the course_references of student
                        void drop_student_from_selected_course();
            
                void course_menu(void); 
                    void add_course_to_database(string code, string name); //creates a Course object and adds it to course_references
                    void course_submenu(string code, string name); //for the selection 2 in the course menu
                        void delete_course_from_database(int courseIndex); //frees selected course object and its student_references
                        void list_registered_students(int courseIndex); //prints the student_references of the selected course
                
                void list_all_students(void); //prints the student_references of SchoolManagementSystem

                void list_all_courses(void); //prints the course_references of SchoolManagementSystem
                void list_nonregistered_courses(int studentIndex); //prints just the nonregistered courses for course selection

            ~SchoolManagementSystem();

    };
}

#endif