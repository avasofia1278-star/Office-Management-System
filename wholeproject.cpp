#include <iostream>
#include <cstring>
#include <fstream>
#include <conio.h>   //  for getch()
using namespace std;

/* ===================================================================
   ENUM: Job levels
   =================================================================== */
enum JobLevel {
    EMPLOYEE = 1,
    HR,
    MANAGER,
    CEO
};

/* ===================================================================
   UNION: Contact info (only one contact type stored at a time)
   =================================================================== */
union Contact {
    char phone[20];
    char email[30];
    char whatsapp[20];
};

/* ===================================================================
   STRUCT: Time structure for login / logout (hours, minutes, seconds)
   =================================================================== */
struct Time {
    int h;
    int m;
    int s;
};

/* ===================================================================
   STRUCT: Employee
   =================================================================== */
struct Employee {
    char name[30];
    int age;
    int id;

    float salaryPerHour;   // hourly rate (default 200)
    int hoursWorked;       // total hours worked in the month

    Contact contact;       // union of contact types
    int contactType;       // 1 = phone, 2 = email, 3 = whatsapp

    char education[30];
    JobLevel level;        // enum for job level
 
    int presentdays;       

    int rating;            // employee rating 1..5

    Time loginTime;        // sample login time
    Time logoutTime;       // sample logout time
};

/* ===================================================================
   LOGIN: simple admin login (username: admin, password: 12345)
   - password input is masked using getch()
   =================================================================== */
bool login() {
    char fileUser[20], filePass[20];
    char User[20], Pass[20];

    // read credentials from file
    ifstream file("login.txt");
    if (!file) {
        cout << "Login file not found ?\n";
        return false;
    }

    file >> fileUser;
    file >> filePass;
    file.close();

    // username input
    cout << "Username: ";
    cin >> User;

    // password input with masking
    cout << "Password: ";
    int i = 0;
    char ch;
    while (true) {
        ch = getch(); // read single character without echo
        if (ch == 13) { // Enter key
            Pass[i] = '\0';
            break;
        } else if (ch == 8) { // Backspace
            if (i > 0) {
                cout << "\b \b"; // erase star
                i--;
            }
        } else {
            Pass[i++] = ch;
            cout << "*"; // show star instead of character
        }
    }

    cout << endl;

    // check login
    if (strcmp(User, fileUser) == 0 && strcmp(Pass, filePass) == 0) {
        cout << "Login successful \n";
        return true;
    } else {
        cout << "Invalid username or password \n";
        return false;
    }
}
/* ===================================================================
   PRELOAD: creates 5 pre-stored employees 
   =================================================================== */
void preloadEmployees(Employee emp[], int &count) {
    // Employee 1
    strcpy(emp[0].name, "Ali");
    emp[0].age = 25;
    emp[0].id = 101;
    emp[0].salaryPerHour = 200;
    emp[0].hoursWorked = 243;
    emp[0].contactType = 1;
    strcpy(emp[0].contact.phone, "03001234567");
    strcpy(emp[0].education, "BSCS");
    emp[0].level = EMPLOYEE;
    emp[0].rating = 4;
    emp[0].loginTime = {9,0,0};
    emp[0].logoutTime = {17,0,0};
    emp[0].presentdays = 27;
   

    // Employee 2
    strcpy(emp[1].name, "Sara");
    emp[1].age = 22;
    emp[1].id = 102;
    emp[1].salaryPerHour = 200;
    emp[1].hoursWorked = 261;
    emp[1].contactType = 2;
    strcpy(emp[1].contact.email, "sara@mail.com");
    strcpy(emp[1].education, "BBA");
    emp[1].level = HR;
    emp[1].rating = 5;
    emp[1].loginTime = {9,30,0};
    emp[1].logoutTime = {16,30,0};
    emp[1].presentdays = 29;
    

    // Employee 3
    strcpy(emp[2].name, "Ahmed");
    emp[2].age = 28;
    emp[2].id = 103;
    emp[2].salaryPerHour = 200;
    emp[2].hoursWorked = 189;
    emp[2].contactType = 3;
    strcpy(emp[2].contact.whatsapp, "03009876543");
    strcpy(emp[2].education, "MBA");
    emp[2].level = MANAGER;
    emp[2].rating = 3;
    emp[2].loginTime = {10,0,0};
    emp[2].logoutTime = {16,0,0};
    emp[2].presentdays = 21;

    // Employee 4
    strcpy(emp[3].name, "Hina");
    emp[3].age = 30;
    emp[3].id = 104;
    emp[3].salaryPerHour = 200;
    emp[3].hoursWorked = 270;
    emp[3].contactType = 1;
    strcpy(emp[3].contact.phone, "03110001122");
    strcpy(emp[3].education, "MSCS");
    emp[3].level = MANAGER;
    emp[3].rating = 5;
    emp[3].loginTime = {8,45,0};
    emp[3].logoutTime = {17,45,0};
    emp[3].presentdays = 30;
    
    // Employee 5
    strcpy(emp[4].name, "Omar");
    emp[4].age = 27;
    emp[4].id = 105;
    emp[4].salaryPerHour = 200;
    emp[4].hoursWorked = 234;
    emp[4].contactType = 2;
    strcpy(emp[4].contact.email, "omar@gmail.com");
    strcpy(emp[4].education, "BSIT");
    emp[4].level = CEO;
    emp[4].rating = 4;
    emp[4].loginTime = {9,15,0};
    emp[4].logoutTime = {17,15,0};
    emp[4].presentdays = 26;
    

    // set current count
    count = 5;
}

/* ===================================================================
  find employee index
   =================================================================== */
int findEmployeeIndexByID(Employee emp[], int count, int id) {
    for (int i = 0; i < count; i++) {
        if (emp[i].id == id)
		 return i;
    }
    return -1;
}

/* ===================================================================
   Add/Update/View employees 
   =================================================================== */
void addEmployee(Employee emp[], int &count) {
    cout << "\n--- ADD NEW EMPLOYEE ---\n";
    cout << "Name: ";
	cin >> emp[count].name;
    cout << "Age: "; 
	cin >> emp[count].age;
    cout << "ID: "; 
	cin >> emp[count].id;
    emp[count].salaryPerHour = 200; // default rate
    cout << "Hours Worked (month): "; 
	cin >> emp[count].hoursWorked;
    cout << "Contact Type (1=Phone,2=Email,3=WhatsApp): "; 
	cin >> emp[count].contactType;
    if (emp[count].contactType == 1) {
	 cout << "Phone: "; 
	cin >> emp[count].contact.phone; 
	}
    else if (emp[count].contactType == 2)
	 {
	 cout << "Email: ";
	 cin >> emp[count].contact.email;
	  }
    else { 
	cout << "WhatsApp: "; 
	cin >> emp[count].contact.whatsapp;
	 }
    cout << "Education: ";
	 cin >> emp[count].education;
    cout << "Job Level (1=Employee,2=HR,3=Manager,4=CEO): "; 
	int lvl; 
	cin >> lvl; 
	emp[count].level = (JobLevel)lvl;
    emp[count].presentdays = 0;
    cout << "Rating (1-5): "; 
	cin >> emp[count].rating;
    cout << "Login Time (h m s): ";
    cin >> emp[count].loginTime.h >> emp[count].loginTime.m >> emp[count].loginTime.s;
    cout << "Logout Time (h m s): ";
	cin >> emp[count].logoutTime.h >> emp[count].logoutTime.m >> emp[count].logoutTime.s;
    count++;
    cout << "Employee added successfully.\n";
}

void updateEmployee(Employee emp[], int count) {
    cout << "\nEnter Employee ID to update: "; 
	int id;
	cin >> id;
    int idx = findEmployeeIndexByID(emp, count, id);
    if (idx == -1) { 
	cout << "Employee not found.\n";
	return; 
	}
    cout << "\n--- UPDATE MENU ---\n1.Name\n2.Education\n3.Job Level\n4.Hours Worked\n5.Rating\nSelect: ";
	int ch;
    cin >> ch;
    switch (ch) {
        case 1: cout << "New Name: ";
		 cin >> emp[idx].name;
		  break;
        case 2: cout << "New Education: ";
		 cin >> emp[idx].education; 
		 break;
        case 3: cout << "New Job Level (1..4): ";
		 int lvl; 
		cin >> lvl; emp[idx].level = (JobLevel)lvl; 
		break;
        case 4: cout << "New Hours Worked: ";
		 cin >> emp[idx].hoursWorked; 
		 break;
        case 5: cout << "New Rating (1..5): ";
		 cin >> emp[idx].rating; 
		 break;
        default: cout << "Invalid selection.\n";
    }
    cout << "Update complete.\n";
}

void viewEmployee(Employee *ptr) {
    cout << "\n--- EMPLOYEE DETAILS ---\n";
    cout << "Name       : " << ptr->name << "\n";
    cout << "Age        : " << ptr->age << "\n";
    cout << "ID         : " << ptr->id << "\n";
    cout << "Contact    : ";
    if (ptr->contactType == 1) 
	cout << ptr->contact.phone << "\n";
    else if (ptr->contactType == 2) 
	cout << ptr->contact.email << "\n";
    else cout << ptr->contact.whatsapp << "\n";
    cout << "Education  : " << ptr->education << "\n";
    cout << "Job Level  : ";
    if (ptr->level == EMPLOYEE)
	cout << "Employee\n";
    else if (ptr->level == HR)
	cout << "HR\n";
    else if (ptr->level == MANAGER) 
	cout << "Manager\n";
    else cout << "CEO\n";
    cout << "Hours Worked: " << ptr->hoursWorked << "\n";
    cout << "Rate/hour  : " << ptr->salaryPerHour << "\n";
    cout << "Base Salary: " << (ptr->hoursWorked * ptr->salaryPerHour) << "\n";
    cout << "Rating     : " << ptr->rating << "/5\n";
    cout << "Login Time : " << ptr->loginTime.h << ":" << ptr->loginTime.m << ":" << ptr->loginTime.s << "\n";
    cout << "Logout Time: " << ptr->logoutTime.h << ":" << ptr->logoutTime.m << ":" << ptr->logoutTime.s << "\n";
}


float calculateSalary(const Employee &e) {
    float baseSalary = e.hoursWorked * e.salaryPerHour;
    float bonus = 0;
    float deduction = 0;
    if (e.rating >= 4) bonus += 2500;
    if (e.presentdays >= 25) bonus += 2000;
    if (e.presentdays < 20) deduction += 1000;
    return baseSalary + bonus - deduction;
}

void salarySlip(Employee &e) {
    cout << "\n===== SALARY SLIP =====\n";
    cout << "Name          : " << e.name << "\n";
    cout << "ID            : " << e.id << "\n";
    cout << "Hours Worked  : " << e.hoursWorked << "\n";
    cout << "Rate / hour   : " << e.salaryPerHour << "\n";
    cout << "Base Salary   : " << (e.hoursWorked * e.salaryPerHour) << "\n";
    cout << "Present Days  : " << e.presentdays << "/31\n";
    cout << "Rating        : " << e.rating << "/5\n";
    float finalPay = calculateSalary(e);
    cout << "Final Pay     : " << finalPay << "\n";
    cout << "========================\n";
}

void salaryForAll(Employee emp[], int count) {
    cout << "\n--- MONTHLY SALARY REPORT ---\n";
    for (int i = 0; i < count; i++) {
        float pay = calculateSalary(emp[i]);
        cout << emp[i].id << " | " << emp[i].name << " | Pay: " << pay << "\n";
    }
}

void salaryMenu(Employee emp[], int count) {
    int ch;
    do {
        cout << "\n--- SALARY PANEL ---\n";
        cout << "1. Generate salary slip for one employee\n";
        cout << "2. Generate salary for all employees\n";
        cout << "3. Back to main menu\n";
        cout << "Enter choice: ";
        cin >> ch;
        if (ch == 1) {
            cout << "Enter employee ID: ";
            int id; cin >> id;
            int idx = findEmployeeIndexByID(emp, count, id);
            if (idx == -1) cout << "Employee not found.\n";
            else salarySlip(emp[idx]);
        } 
		else if (ch == 2) {
            salaryForAll(emp, count);
        } 
		else if (ch == 3) {
            break;
        } 
		else {
            cout << "Invalid selection.\n";
        }
    } while (ch != 3);
}

/* ===================================================================
   DEVICE FUNCTIONS ( appliance code)
   =================================================================== */
void devicePanel() {
    bool status1=false, status2=false, status3=false, status4=false, status5=false, status6=false, status7=false;
    int choic;
    do {
        cout<<"\n--- DEVICE STATUS ---\n";
        cout<<"1.Computer\t: "<<(status1?"ON":"OFF")<<"\n";
        cout<<"2.AC      \t: "<<(status2?"ON":"OFF")<<"\n";
        cout<<"3.Heater  \t: "<<(status3?"ON":"OFF")<<"\n";
        cout<<"4.Lights  \t: "<<(status4?"ON":"OFF")<<"\n";
        cout<<"5.Coffeemaker\t: "<<(status5?"ON":"OFF")<<"\n";
        cout<<"6.Printer \t: "<<(status6?"ON":"OFF")<<"\n";
        cout<<"7.Doorlock\t: "<<(status7?"Unlocked":"Locked")<<"\n";

        cout<<"Choose device number to toggle(1-7) or 0 to exit: "; cin>>choic;
        if(choic==1)
		{ status1=!status1; 
		cout<<"Computer is now "<<(status1?"ON":"OFF")<<"\n"; 
		}
        else if(choic==2)
		{ status2=!status2; cout<<"AC is now "<<(status2?"ON":"OFF")<<"\n";
		 }
        else if(choic==3){ status3=!status3; cout<<"Heater is now "<<(status3?"ON":"OFF")<<"\n"; }
        else if(choic==4){ status4=!status4; cout<<"Lights is now "<<(status4?"ON":"OFF")<<"\n"; }
        else if(choic==5){ status5=!status5; cout<<"Coffeemaker is now "<<(status5?"ON":"OFF")<<"\n"; }
        else if(choic==6){ status6=!status6; cout<<"Printer is now "<<(status6?"ON":"OFF")<<"\n"; }
        else if(choic==7){ status7=!status7; cout<<"Doorlock is now "<<(status7?"Unlocked":"Locked")<<"\n"; }
    } while(choic!=0);

} 

/* ===================================================================
   MAIN: program entry 
   =================================================================== */
int main() {
    // require admin login first
    while (!login()) {
        cout << "Please try again.\n";
    }

    Employee emp[100];   
    int count = 0;
    preloadEmployees(emp, count); 

    int choice;
    do {
        cout << "\n===== OFFICE ADMIN - MAIN MENU =====\n";
        cout << "1. Add Employee\n";
        cout << "2. Update Employee\n";
        cout << "3. View Employee Details \n";
        cout << "4. Device Control Panel\n";
        cout << "5. Salary Panel\n";
        cout << "6. Exit\n";
        cout << "Please enter your choice: ";
        cin >> choice;

        if (choice == 1) {
            addEmployee(emp, count);
        }
        else if (choice == 2) {
            updateEmployee(emp, count);
        }
        else if (choice == 3) {
                cout << "Enter employee ID: ";
                int id; cin >> id;
                int idx = findEmployeeIndexByID(emp, count, id);
                if (idx == -1) cout << "Employee not found.\n";
                else viewEmployee(&emp[idx]);
            }
        
        else if (choice == 4) {
            devicePanel();   // NEW device-based control panel
        }
        else if (choice == 5) {
            salaryMenu(emp, count);
        }
        else if (choice == 6) {
            cout << "Exiting system. Goodbye.\n";
            break;
        }
        else {
            cout << "Invalid menu choice. Try again.\n";
        }
    } while (choice != 6);

    return 0;
}

