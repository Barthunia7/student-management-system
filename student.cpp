
#include<iostream>
#include<vector>
#include<fstream>
using namespace std;

class Student{
    public:
        string name;
        int roll_no;
        float marks;

      void input(){
        cout<<"Enter roll number: ";
        cin>>roll_no;
        cin.ignore();
        cout<<"Enter name: ";
        getline(cin, name); // To consume the newline character left in the input buffer
        
        cout<<"Enter marks: ";
        cin>>marks;
      }
      void display(){
        cout<<"Name: "<<name<<endl;
        cout<<"Roll Number: "<<roll_no<<endl;
        cout<<"Marks: "<<marks<<endl;
      }
    };
    void savetofile(vector<Student>& students){
        ofstream File("students.txt");
        for(Student s : students){
            File<<s.name<<" "<<s.roll_no<<" "<<s.marks<<endl;
        }
        File.close();
    }
    void loadfromfile(vector<Student>& students){
        ifstream File("students.txt");
        if(!File){
            cout<<"No existing data found."<<endl;
            return;
        }
        Student s;
        while(File>>s.roll_no){
            File.ignore(); // To ignore the space after roll_no
            getline(File, s.name,',');
            File>>s.marks;
            students.push_back(s);
        }
        File.close();
    }
    void searchStudent(vector<Student>& students){
        int roll_no;
        cout<<"Enter roll number to search: ";
        cin>>roll_no;

        bool found=false;

        for(Student s : students){
            if(s.roll_no==roll_no){
                s.display();
                found=true;
                break;
            }
        }
        if(!found){
            cout<<"Student not found."<<endl;
        }
    }
    void deleteStudent(vector<Student>& students){
        int roll_no;
        cout<<"Enter roll number to delete: ";
        cin>>roll_no;

        bool found=false;

        for(auto it = students.begin(); it != students.end(); ++it){
            if(it->roll_no==roll_no){
                found=true;
                students.erase(it);
                found=true;
                break;
            }
        }
        if(found){
            savetofile(students);
            cout<<"student data deleted succesfully\n";
        }else{
            cout<<"incoorect rool no\n";
        }
    }
    int main(){
        vector<Student> students;
        loadfromfile(students);//load old data at start
        int choice;
        do{
            cout<<"1.Add Students.\n 2.Display all.\n 3.Search Student.\n 4.Delete Student.\n 5.Exit.\n";
            cout<<"Enter your choice: ";
            if(!(cin>>choice)){
                cin.clear();
                cin.ignore(1000, '\n');
                cout<<"invalid input"<<endl;
                continue;
            }
        
            if(choice==1){
                Student s;
                s.input();
                students.push_back(s);
                savetofile(students);
            }
            else if(choice==2){
                if(students.empty()){
                    cout<<"no data found\n";
                }else{
                for(Student s : students){
                    s.display();
                }
            }
        }else if(choice==3){
            searchStudent(students);
        }else if(choice==4){
            deleteStudent(students);
        }
        }while(choice!=5);
        cout<<"Exiting program. Goodbye!"<<endl;
        return 0;
    }
        
        
