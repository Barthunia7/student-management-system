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
        cin.ignore(1000, '\n'); // To clear the input buffer before reading the name
        cout<<"Enter name: ";
        getline(cin, name); // To consume the newline character left in the input buffer
        
        cout<<"Enter marks: ";
        cin>>marks;
      }
      void display(){
       
        cout<<"Roll Number: "<<roll_no<<endl;
         cout<<"Name: "<<name<<endl;
        cout<<"Marks: "<<marks<<endl;
      }
    };
    void savetofile(Student &s){
        ofstream File("students.txt",ios::app);
        if(!File){
            cout<<"Error opening file for writing."<<endl;
            return;
        }
        File<<s.roll_no<<","<<s.name<<","<<s.marks<<endl;
        File.close();
    }
    // ✅ Overwrite ALL students (used after delete)
void savetofile_all(vector<Student>& students){
    ofstream File("students.txt");
    if(!File){
        cout<<"Error opening file!\n";
        return;
    }

    for(Student &s : students){
        File << s.roll_no << "," << s.name << "," << s.marks << endl;
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
        while(true)
        {
            if(!(File>>s.roll_no)) break;
    
            File.ignore(1000, ','); // To ignore the comma after roll_no
            getline(File, s.name, ',');
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

        for(Student &s : students){
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
            
                break;
            }
        }
        if(found){
            savetofile_all(students);
            cout<<"student data deleted succesfully\n";
        }else{
            cout<<"incoorect roll no\n";
        }
    }
    void updateStudent(vector<Student>& students){
    int roll_no;
    cout<<"Enter roll number to update: ";
    cin>>roll_no;

    bool found=false;

    for(Student &s : students){
        if(s.roll_no == roll_no){
            cout<<"Enter new name: ";
            cin.ignore(1000, '\n');
            getline(cin, s.name);

            cout<<"Enter new marks: ";
            cin>>s.marks;

            found=true;
            break;
        }
    }

    if(found){
        savetofile_all(students);
        cout<<"Student updated successfully\n";
    } else {
        cout<<"Student not found\n";
    }
}
    int main(){
        vector<Student> students;

        loadfromfile(students);//load old data at start
        int choice;
        do{
            cout<<"1.Add Students.\n 2.Display all.\n 3.Search Student.\n 4.Delete Student.\n 5.Update Student.\n 6.Exit.\n";
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
                savetofile(s);
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
        }else if(choice==5){
            updateStudent(students);    
        }
        }while(choice!=6);
        cout<<"Exiting program. Goodbye!"<<endl;
        return 0;
    }
        
        
