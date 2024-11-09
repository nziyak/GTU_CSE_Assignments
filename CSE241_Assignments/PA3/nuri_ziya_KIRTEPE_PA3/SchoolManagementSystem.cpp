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

    #endif

    SchoolManagementSystem::SchoolManagementSystem() 
    { 
        student_counter = 0; 
        course_counter = 0; 
        student_rfr_size = 0;
        course_rfr_size = 0;

        student_references = nullptr;
        course_references = nullptr;
    }

    Course** SchoolManagementSystem::get_course_references(void)
    {
        return course_references;
    }

    Student** SchoolManagementSystem::get_student_references(void)
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

            //if input is not zero take the name and id and make other operations

            string line, id, name, word; 

            cout << ">> ";

            cin.ignore(); //clear the cin object
            getline(cin, line);

            istringstream iss(line);

            //take the first name
            iss >> name;

            while (iss >> word) 
            {
                //if the next word is a number take it to id
                if (isdigit(word[0])) 
                {
                    id = word;
                } 
                else //else consider it as a part of the word
                {
                    name += " " + word;
                }
            }
                
            if (input == "1")
                add_student_to_database(name, id);
            
            else if (input == "2")
                student_submenu(name, id);
            
            else 
                student_menu();

        } while (input != "0");
    }

    void SchoolManagementSystem::add_student_to_database(string name, string id)
    {
        student_counter++;

        if(student_counter >= student_rfr_size) //if existing size is not enough, increase it by 5
        {
            Student** new_student_references = new Student*[student_rfr_size+5]; 

            for(int i = 0; i < student_rfr_size; i++) //assign elements to the new student references array
            {
                new_student_references[i] = student_references[i];
            } 

            delete[] student_references; //free the existing one

            student_references = new_student_references; //let the old pointer to point to new data

            student_rfr_size += 5; //increase size information
        }

        student_references[student_counter-1] = new Student(name, id); //assign the created Student object
    }

    void SchoolManagementSystem::delete_student_from_database(int studentIndex)
    {
        Student** new_student_references = new Student*[student_rfr_size];

        for(int i = 0, j = 0; i < student_counter; i++)
        {
            if(i != studentIndex) //if the element is not the to be deleted, put it in the new references array
            {
                new_student_references[j] = student_references[i];
                j++; //increment the index of new_student_references in just the adding case
            }
        }

        drop_student_from_all_courses(student_references[studentIndex]);
        
        delete[] student_references[studentIndex]->get_course_referencess();
        delete student_references[studentIndex]; //free the student
        student_references[studentIndex] = nullptr; //make its ptr null
        delete[] student_references; //free the existing one

        student_references = new_student_references;

        student_counter--;
    }

    void SchoolManagementSystem::add_student_to_course(int studentIndex)
    {
        add_student_to_courses_references(studentIndex); //this will call "add_student_to_courses_references"
    }

    void SchoolManagementSystem::add_student_to_courses_references(int studentIndex)
    {
        if(course_references == nullptr)
        {
            return;
        }    
        
        list_nonregistered_courses(studentIndex);
        
        string sel; //selection
        int indexPP; //user selection will be the index of the selected course + 1

        cin.ignore();
        cin >> sel;

        indexPP = stoi(sel);

        indexPP--;

        Student*** stdnt_references = course_references[indexPP]->get_student_references(); //take address of the student references of the selected course
        int& stdnt_counter = course_references[indexPP]->get_student_counter();
        int& stdnt_rfr_size = course_references[indexPP]->get_student_rfr_size();

        stdnt_counter++;

        if(stdnt_counter >= stdnt_rfr_size) //if existing size is not enough, increase it by 5
        {
            Student** new_student_references = new Student*[stdnt_rfr_size+5]; 

            for(int i = 0; i < stdnt_rfr_size; i++) //assign elements to the new student references array
            {
                new_student_references[i] = *(stdnt_references)[i];
            } 

            delete[] *(stdnt_references); //free the existing one

            *(stdnt_references) = new_student_references; //let the old pointer to point to new data

            stdnt_rfr_size += 5; //increase size information
        }

        *(stdnt_references)[stdnt_counter-1] = student_references[studentIndex]; //add the student which is gonna take the course to the student references of the course

        add_course_to_students_references(indexPP, studentIndex);
    }

    void SchoolManagementSystem::add_course_to_students_references(int courseIndex, int studentIndex)
    {
        Course*** crs_references = student_references[studentIndex]->get_course_references(); //take the student references of the selected course
        int& crs_counter = student_references[studentIndex]->get_course_counter();
        int& crs_rfr_size = student_references[studentIndex]->get_course_rfr_size();

        crs_counter++;

        if(crs_counter >= crs_rfr_size) //if existing size is not enough, increase it by 5
        {
            Course** new_course_references = new Course*[crs_rfr_size+5]; 

            for(int i = 0; i < crs_rfr_size; i++) //assign elements to the new student references array
            {
                new_course_references[i] = *(crs_references)[i];
            } 

            delete[] *(crs_references); //free the existing one

            *(crs_references) = new_course_references; //let the old pointer to point to new data

            crs_rfr_size += 5; //increase size information
        }

        *(crs_references)[crs_counter-1] = course_references[courseIndex]; 
    }

    void SchoolManagementSystem::drop_student_from_all_courses(Student* toBeDeletedStudent)
    {
        int crs_counter = toBeDeletedStudent->get_course_counter();
        Course** courses = toBeDeletedStudent->get_course_referencess(); //get course_references of the student
        string student_name = toBeDeletedStudent->get_name();
        string student_ID = toBeDeletedStudent->get_ID();
        int index;

        for(int i = 0; i < crs_counter; i++)
        {
            index = courses[i]->find_student_index(student_name, student_ID); //find the position of the student in the student_references of the current course
            courses[i]->get_student_references()[index] = nullptr; //make the pointer to it nullptr
            courses[i]->get_student_counter()--; //decrement the student counter of the course which's student is deleted
        }    
    }

    void SchoolManagementSystem::drop_student_from_selected_course(void)
    {
        list_all_courses();

        string sel; //selection
        int numSel;

        cin.ignore();
        cin >> sel;

        numSel = stoi(sel);

        //toBeDeletedStudentPtr->get_course_references()[i]->get_student_references()[numSel-1] = 

        //write a function to find the index of the to be added student
        //student_references.get_course_references()[] 
        //course_references[numSel-1].
    }

    int SchoolManagementSystem::find_student_index(string name, string id)
    {
        if(student_references == nullptr)
        {
            exit(1);
        }
        
        for(int i = 0; i < student_counter; i++)
        {
            if(student_references[i]->get_name() == name  && student_references[i]->get_ID() == id)
            {
                return i;
            }
        }

        return -1;
    }

    int SchoolManagementSystem::find_course_index(string name, string code)
    {
        if(course_references == nullptr)
        {
            exit(1);
        }
        
        for(int i = 0; i < course_counter; i++)
        {
            if((course_references[i]->get_name() == name) && (course_references[i]->get_code() == code))
            {
                return i;
            }
        }

        return -1;
    }

    void SchoolManagementSystem::student_submenu(string name, string id)
    {
        string input;
        int studentIndex = find_student_index(name, id);

        do {

            cout << "0 up\n"
                << "1 delete_student\n"
                << "2 add_selected_student_to_a_course\n"
                << "3 drop_selected_student_from_a_course\n"
                << ">> ";

            cin >> input;

            if (input == "0")
                break;
            
            else if (input == "1")
            {
                if(studentIndex == -1)
                {
                    break;
                }
                
                else
                    delete_student_from_database(studentIndex);
            }
            
            else if (input == "2")
                add_student_to_course(studentIndex);
            
            else
                student_submenu(name, id);

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

            string line;

            cout << ">> ";

            cin.ignore(); //clear the cin object
            getline(cin, line); //take the line

            istringstream iss(line);
            string code, name;

            iss >> code; //take the code

            string word;
            string remaining;
            while (iss >> word) 
            { //take the rest of the name
                if (!remaining.empty())
                {
                    remaining += " ";
                }
                remaining += word;
            }

            name = remaining; //take the remaining part to name
            
            if (input == "1")
                add_course_to_database(code, name);
            
            else if (input == "2")
                course_submenu(code, name);
            
            else
                course_menu();

        } while (input != "0");  
    }

    void SchoolManagementSystem::add_course_to_database(string code, string name) 
    {
        course_counter++;
        
        if(course_counter >= course_rfr_size) //if existing size is not enough, increase it by 5
        {
            Course** new_course_references = new Course*[course_rfr_size+5]; 

            for(int i = 0; i < course_rfr_size; i++) //assign elements to the new student references array
            {
                new_course_references[i] = course_references[i];
            } 

            delete[] course_references; //free the existing one

            course_references = new_course_references; //let the old pointer to point to new data

            course_rfr_size += 5; //increase size information
        }

        course_references[course_counter-1] = new Course(name, code); //assign the created Student object
    }

    void SchoolManagementSystem::course_submenu(string code, string name)
    {
        string input;
        int courseIndex = find_course_index(name, code); 

        do {
            
            cout << "0 up\n"
                << "1 delete_course\n"
                << "2 list_students_registered_to_the_selected_course\n"
                << ">> ";

            cin >> input;

            if (input == "0")
                break;
            
            else if (input == "1")
                delete_course_from_database(courseIndex);
            
            else if (input == "2")
                list_registered_students(courseIndex);
            
            else
                course_submenu(code, name);

        } while (input != "0"); 
    }

    void SchoolManagementSystem::delete_course_from_database(int courseIndex)
    {
        cout << "\n";
    }

    void SchoolManagementSystem::list_registered_students(int courseIndex)
    {
        int stdnt_counter = course_references[courseIndex]->get_student_counter();

        if(stdnt_counter == 0)
        {
            return;
        }

        for(int i = 0; i < stdnt_counter; i++)
        {
            cout << i+1 << " " << course_references[courseIndex]->get_student_referencess()[i]->get_name()
                            << " "
                            << course_references[courseIndex]->get_student_referencess()[i]->get_ID()
                            << endl;
        }
    }

    void SchoolManagementSystem::list_all_students(void)
    {
        for(int i = 0; i < student_counter; i++)
        {
            cout << i+1 << " " << student_references[i]->get_name() << " " << student_references[i]->get_ID() << endl;
        }
    }

    void SchoolManagementSystem::list_all_courses(void)
    {
        for(int i = 0; i < course_counter; i++)
        {
            cout << i+1 << " " << course_references[i]->get_code() << " " << course_references[i]->get_name() << endl;
        }
    }

    void SchoolManagementSystem::list_nonregistered_courses(int studentIndex)
    {
        for(int i = 0; i < course_counter; i++)
        {   //print the course, if the course is not taken by the student
            if((student_references[studentIndex]->find_course_index(course_references[i]->get_name(), course_references[i]->get_code())) == -1)
                cout << i+1 << " " << course_references[i]->get_code() << " " << course_references[i]->get_name() << endl;
        }
    }

    SchoolManagementSystem::~SchoolManagementSystem() 
    { 
        for (int i = 0; i < student_counter; ++i) 
        {
            //delete[] student_references[i]->get_course_referencess();
            delete[] student_references[i];
        }
        delete[] student_references; //free the existing one

        for (int i = 0; i < course_counter; ++i) 
        {
            //delete[] course_references[i]->get_student_referencess();
            delete[] course_references[i];
        }
        delete[] course_references; //free the existing one
    }

}