#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <ctime>
#include <sstream>
#include <chrono>
#include <cstdio>

using namespace std;

string gen_random(const int len); // Defining this function, its defination is later in program


class Department {

public:
    string dep_name;
    // Constructor
    Department() {
        cout << "\nEnter Department Name: ";
        cin >> dep_name;

    }

    ~Department()
    {

    }
    friend class Management;

};


class ProjectGroup : public Department {
public:
    string pro_name;
    // Constructor
    ProjectGroup() {
        cout << "\nEnter Project Name: ";
        cin >> this->pro_name;

    }
    ~ProjectGroup()
    {

    }
    friend class Management;

};

class Employee : public ProjectGroup {

private:
    double salary;
    double ProjectContribution = 0;
    double PerformanceRating = 0;

public:
    string name;
    int ProjectsWorkedOn = 0;
    string id = gen_random(4);
    int LeavesTaken = 0;
    int LeavesAvailable = 15;
    int NumberOfDaysWorked = 0;

    // Construtor
    Employee() {
        cout << "\nEnter Employee Name: ";
        cin >> this->name;

        cout << "Enter Salary: ";
        cin >> this->salary;
    }
    friend class Management;
    friend class Working;


};

class Management {
    //This is a container class, it contains all the management related methods

    vector <Employee> Employee_list;

public:
    // Construtor 
    Management() {}

    // Methods
    void Performance(Employee& e) {
        double present = e.ProjectContribution;
        int past = e.ProjectsWorkedOn;
        try
        {
            if (e.NumberOfDaysWorked == 0) {
                throw('l');
            }
            e.PerformanceRating = (present * e.NumberOfDaysWorked) + ((double)past * 100);
            cout << "\n\nPerformance has been calculated and Employee Performance rating has been updated\n\n";
           
        }
        catch (...)
        {
            cout << "\nPerformance could not be calculated try later.\n";
        }

    }

    void PromotionStatus(Employee& e) {
        if (e.PerformanceRating > 1000) {
            cout << "\n\nEmployee is eligible for Promotion\n\n";
        }
        else {
            cout << "\n\nEmployee is illegible for Promotion\n";
        }
    }

    void BonusStatus(Employee& e) {
        if (e.PerformanceRating - ((double)e.ProjectsWorkedOn * 100) > 300 && e.ProjectsWorkedOn > 2) {
            cout << "\n\nEmployee is eligible for bonus\n\n";
        }
        else {
            cout << "\nEmployee is illegible for bonus\n";
        }
    }

    void Display(Employee& e) {
        cout << "\n\n";
        cout << "Name: " << e.name << endl;
        cout << "ID: " << e.id << endl;
        cout << "Salary: " << e.salary << endl;
        cout << "Performance Rating: " << e.PerformanceRating << endl;
        cout << "\n\n";

    }

    void DailyUpdate(Employee& e) {
        cout << "\n\n";

        cout << "Enter Number of Working Day: ";
        cin >> e.NumberOfDaysWorked;

        cout << "Enter Current Project Progress: ";
        cin >> e.ProjectContribution;

        cout << "Enter Number of Projects Worked on: ";
        cin >> e.ProjectsWorkedOn;
    }
    friend class Working;
};


class Working : public Management {
public:

    void RequiredCreation() {
        // This function create the neccessary objects for the working of programme
        int count;
        cout << "\n";
        cout << "Enter Number of New Employees: ";
        cin >> count;

        for (size_t i = 0; i < count; i++)
        {
            Employee e;
            Employee_list.push_back(e);
        }
    };

    void WriteInData() {
        // This function writes data in log file
        fstream file;
        file.open("employeebackupdata.csv", ios::out | ios::app);

        time_t now = time(0);
        #pragma warning(disable : 4996)
        char* date_time = ctime(&now);

        file << "\n\nDate:\n\n" << date_time << "\n\n";

        file << "ID," << "Employee Name," << "Project Name," << "Department Name," << "Salary," << "Number of Projects Worked On," << "Performance Rating," << "Project Contribution,"
            << "Leaves Taken," << "Leaves Available," << "Number of Days Worked\n";

        for (size_t i = 0; i < Employee_list.size(); i++)
        {
            file << Employee_list[i].id << ','
                << Employee_list[i].name << ','
                << Employee_list[i].pro_name << ','
                << Employee_list[i].dep_name << ','
                << Employee_list[i].salary << ','
                << Employee_list[i].ProjectsWorkedOn << ','
                << Employee_list[i].PerformanceRating << ','
                << Employee_list[i].ProjectContribution << ','
                << Employee_list[i].LeavesTaken << ','
                << Employee_list[i].LeavesAvailable << ','
                << Employee_list[i].NumberOfDaysWorked
                << "\n";
        }
        file.close();
    }

    void YearStartReset() {
        for (size_t i = 0; i < Employee_list.size(); i++)
        {
            Employee_list[i].LeavesAvailable = 15;
            Employee_list[i].LeavesTaken = 0;
            Employee_list[i].NumberOfDaysWorked = 0;
        }
    }

    void Start() {
        for (size_t i = 0; i < Employee_list.size(); i++)
        {
            DailyUpdate(Employee_list[i]);
            Performance(Employee_list[i]);
            BonusStatus(Employee_list[i]);
            PromotionStatus(Employee_list[i]);
            
        }
    }

    void DisplayStart() {
        for (size_t i = 0; i < Employee_list.size(); i++)
        {
            Display(Employee_list[i]);

        }
    }
};


void Help() {
    // This function is to provide details of each class and methods available
    cout << "\n--------------------------------------------------------Help--------------------------------------------------------\n\n";
    cout << "This software records log under name employeebackupdata.\n";
    cout << "\n\nCreate: Use this to write employee data.\n";
    cout << "\nStart: Use this to start updation process and calculate performance and bonus\n";
    cout << "\nLog: Use this to log changes in the csv file named employeebackupdata in same folder.\n";
    cout << "\nNew Year: Use this to start new working year, do backup before starting.\n";
    cout << "\nExit: Use this to exit from application.\n";
    cout << "\n--------------------------------------------------------------------------------------------------------------------\n\n";

}

// Random Id generator
string gen_random(const int len) {

    string tmp_s;
    static const char alphanum[] =
        "0123456789";

    srand((unsigned)time(NULL));

    tmp_s.reserve(len);

    for (int i = 0; i < len; ++i)
        tmp_s += alphanum[rand() % (sizeof(alphanum) - 1)];

    return tmp_s;
}

// Required Globals
Management M;
Working W;

int main() {

    cout << "______________________________________________________________________________________________________________________";
    cout << "\nEmployee Management Software\n";
    cout << "______________________________________________________________________________________________________________________";
    cout << "\nAvailable Operations: \n";
    cout << "1.Create\n2.Start\n3.Log\n4.Help\n5.New Year\n6.Exit\n";
    cout << "______________________________________________________________________________________________________________________";

    int DayOfWorking = 0;

    while (true)
    {
        int operation;
        cout << "\n\nType Operation Number: ";
        cin >> operation;

        if (operation == 1) { // create
            cout << "\n";
            W.RequiredCreation();
        }
        else if (operation == 4) { // help
            Help();
        }
        else if (operation == 2) { // start
            W.Start();

            string state;
            cout << "\n\nDo you want to see employee data?\nEnter 1 for yes and any other key for no: ";
            cin >> state;
            cout << "\n\n";
            if (state == "1") {
                W.DisplayStart();
            }
        }
        else if (operation == 3) { // log
            W.WriteInData();
            cout << "\n Day Ended \n";
            cout << "\n Logs Recorded \n";
            break;
        }
        else if (operation == 6) { // exit
            break;
        }
        else if (operation == 5) { // new year
            W.YearStartReset();
        }
        else {
            cout << "\n! Enter Valid Operation !\n";
        }

    }
    return 0;
}

