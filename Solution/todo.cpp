#include <bits/stdc++.h>

using namespace std;

string menu = "Usage :-\n$ ./todo add \"todo item\"  # Add a new todo\n$ ./todo ls               # Show remaining todos\n$ ./todo del NUMBER       # Delete a todo\n$ ./todo done NUMBER      # Complete a todo\n$ ./todo help             # Show usage\n$ ./todo report           # Statistics";

int main(int argc, char* argv[])
{
    fstream fileStream;

    //creating todo.txt if file does not exist
    fileStream.open("todo.txt");
    if (fileStream.fail()) {
        ofstream file;
        file.open ("todo.txt");
        file.close();
    }
    fileStream.close();

    //creating done.txt if file does not exist
    fileStream.open("done.txt");
    if (fileStream.fail()) {
        ofstream file;
        file.open ("done.txt");
        file.close();
    }
    fileStream.close();

    clock_t start = clock();    //get the starting value of clock
    tm* my_time;
    time_t t = time(NULL);      //get current time in format of time_t
    my_time = localtime(&t);    //convert time_t to tm

    string line;
    vector<string> v1;
    int completed = 0, pending = 0;
    fstream file1, file2, file3;

    if(argc == 1){                      //if no command line arguments are given
        cout << menu << endl;
    }
    else if(argc == 2){                     //if only one command line arguments is given
        if( strcmp(argv[1],"help") == 0)    //for help
            cout << menu << endl;

        else if(strcmp(argv[1],"report") == 0){     //for report
            pending = completed = 0;

            //Counting Number of lines in file1 and file2
            file1.open ("todo.txt", ios::in);
            file2.open ("done.txt", ios::in);

            //Counting Number of lines in file1
            while(getline(file1, line))
                pending++;

            //Counting Number of lines in file2
            while(getline(file2, line))
                completed++;

            //closing file pointers
            file1.close();
            file2.close();

            //Code for printing current date in 01/01/2021 Format
            string month = "";
            string day = "";

            if(my_time->tm_mon + 1 < 10)
                month += "0" + to_string(my_time->tm_mon + 1);
            else
                month += to_string(my_time->tm_mon + 1);

            if(my_time-> tm_mday < 10)
                day += "0" + to_string(my_time-> tm_mday);
            else
                day += to_string(my_time-> tm_mday);

            cout << 1900 + my_time->tm_year << "-" << month << "-" << day
            << " Pending: " << pending << " Completed: " << completed << endl;
        }
        else if(strcmp(argv[1],"ls") == 0){     //for ls
            file1.open ("todo.txt", ios::in);

            string str;
            //taking todos from todo.txt into an string vector
            while (getline(file1, str))
                v1.push_back(str);

            int n = v1.size();
            if(n == 0)
                cout << "There are no pending todos!" << endl;
            else{
                for(int i = n-1; i >= 0; i--){
                    //printing todos
                    cout << "[" << i+1 << "]" << " " << v1[i] << endl;
                }
                file1.close();
            }
        }
        else if(strcmp(argv[1],"add") == 0){
            cout << "Error: Missing todo string. Nothing added!" << endl;
        }
        else if(strcmp(argv[1],"del") == 0){
            cout << "Error: Missing NUMBER for deleting todo." << endl;
        }
        else if(strcmp(argv[1],"done") == 0){
            cout << "Error: Missing NUMBER for marking todo as done." << endl;
        }


    }
    else if(argc == 3){                             //if two command line arguments are given
        if( strcmp(argv[1],"add") == 0 ){           //for add
            file1.open ("todo.txt", ios::app);
            file1 << argv[2] << endl;
            cout << "Added todo: " << "\"" << argv[2] << "\"" << endl;
            v1.push_back(argv[2]);
            file1.close();
        }
        else if( strcmp(argv[1],"del") == 0 ){      //for del
            file1.open ("todo.txt", ios::in);
            string str;
            //taking todos from todo.txt into an string vector
            while (getline(file1, str))
                v1.push_back(str);

            int x = stoi(argv[2]);
            if(x == 0)
                cout << "Error: todo #0 does not exist. Nothing deleted." << endl;
            else if(x > v1.size())
                cout << "Error: todo #" << x << " does not exist. Nothing deleted." << endl;
            else{
                //adding all todos except for the deleted todo to the new file temp.txt
                //then removing todo.txt and renaming temp.txt to todo.txt
                file2.open ("todo.txt", ios::in);
                fstream ofs;
                ofs.open("temp.txt", ofstream::out);
                string str1;
                int line_no = 1;
                while (getline(file2, str1))
                {
                    // file content not to be deleted
                    if (line_no != x)
                        ofs << str1 << endl;
                    line_no++;
                }
                cout << "Deleted todo #" << x << endl;
                ofs.close();
                file2.close();
                remove("todo.txt");
                rename("temp.txt", "todo.txt");
            }
            file1.close();
        }
        else if( strcmp(argv[1],"done") == 0 ){     //for done
            file1.open ("todo.txt", ios::in);
            string str;
            //taking todos from todo.txt into an string vector
            while (getline(file1, str))
                v1.push_back(str);

            int x = stoi(argv[2]);
            if(x == 0)
                cout << "Error: todo #0 does not exist." << endl;
            else if(x > v1.size())
                cout << "Error: todo #" << x << " does not exist." << endl;
            else{
                //adding all todos except for the done todo to the new file temp.txt
                //adding done todo in done.txt in specified format
                //then removing todo.txt and renaming temp.txt to todo.txt
                file2.open ("todo.txt", ios::in);
                file3.open ("done.txt", ios::app);
                fstream ofs;
                ofs.open("temp.txt", ofstream::out);
                string str1;
                int line_no = 1;
                while (getline(file2, str1))
                {
                    // file content not to be deleted
                    if (line_no != x)
                        ofs << str1 << endl;
                    else
                    {
                        string month = "";
                        string day = "";
                        if(my_time->tm_mon + 1 < 10)
                            month += "0" + to_string(my_time->tm_mon + 1);
                        else
                            month += to_string(my_time->tm_mon + 1);

                        if(my_time-> tm_mday < 10)
                            day += "0" + to_string(my_time-> tm_mday);
                        else
                            day += to_string(my_time-> tm_mday);

                        file3 << "x " << 1900 + my_time->tm_year << "-"
                        << month<< "-" << day << " " << str1 << endl;
                    }
                    line_no++;
                }
                cout << "Marked todo #" << x << " as done." << endl;
                ofs.close();
                file2.close();
                file3.close();
                remove("todo.txt");
                rename("temp.txt", "todo.txt");
            }
            file1.close();
        }
    }
    return 0;
}