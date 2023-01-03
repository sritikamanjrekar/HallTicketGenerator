#include <iostream>
#include <string.h>
#include <fstream>
#include <ctime>

using namespace std;

short hallticketid;
char seattype;

class ExamHall
{
protected:
    char examhallid;
    int subjectid;
    short time = 0;
    char subject[100];
    char seats[100];
    short seatnumber;
    ifstream subjectlist;
    const char *timing[6] = {"8:00", "9:30", "12:00", "01:30", "1:00", "10:30"};

private:
    
    
    char Assign_examHallid(int id)
    {
        switch (id)
        {
        case 1:
            return 'A';
            break;
        case 2:
            return 'B';
            break;
        case 3:
            return 'C';
            break;
        case 4:
            return 'A';
            break;
        case 5:
            return 'B';
            break;
        case 6:
            return 'C';
            break;
        default:
            return '\0';
            break;
        }
    }

public:
    int success()
    {

        examhallid = Assign_examHallid(subjectid);
        if (examhallid == '\0')
            return 1;
        else
            return 0;
    }
};

class Subject : protected ExamHall
{
private:
    void SelectSubject()
    {
        cout << "Please enter the Subject ID: ";
        cin >> subjectid;
        // The cin.ignore() function is used which is used to ignore or clear one or more characters from the input buffer
        cin.ignore();
        // call function success until it return 1
        while (success() == 1)
        {
            cout << "Please enter a valid Subject ID: ";
            cin >> subjectid;
            ////The cin.ignore() function is used which is used to ignore or clear one or more characters from the input buffer

            cin.ignore();
            success();
        }
        // call function timing
        Timing();
    }

    void Timing()
    {
        cout << endl
             << "Timings" << endl
             << endl;

        // if subject id<=3
        if (subjectid <= 3)
        {

            for (int i = 0; i < 6; i++)
            {
                //
                if (i % 2 == 0)
                    cout << i << " " << timing[i] << endl;
            }
        }
        else
        {
            for (int i = 0; i < 6; i++)
            {
                if (i % 2 != 0)
                    cout << i << " " << timing[i] << endl;
            }
        }
        cout << endl
             << "Please enter your exam timings: ";
        cin >> time;

        // The cin.ignore() function is used which is used to ignore or clear one or more characters from the input buffer
        cin.ignore();

        // call function seat map
        Seatmap();
    }

    void Seatmap()
    {

        switch (examhallid)
        {
        case 'A':
        {
            // diplay h1 text file
            ifstream h1("./TextFiles/h1.txt");
            cout << endl;
            while (!h1.eof())
            {
                h1.getline(seats, 100);
                cout << " " << seats << endl;
            }
            h1.close();

            // create output file h1 text that means this will update h1 text file
            ofstream examhall1("./TextFiles/h1.txt", ios::app);
            cout << endl
                 << "Enter your seat number: ";
            cin >> seatnumber;
            cin.ignore();
            examhall1 << " " << seatnumber << " ";
            examhall1.close();
        }
        break;

        case 'B':
        {
            ifstream h2("./TextFiles/h2.txt");
            while (!h2.eof())
            {
                h2.getline(seats, 100);
                cout << " " << seats << endl;
            }
            h2.close();
            ofstream examhall2("./TextFiles/h2.txt", ios::app);
            cout << endl
                 << "Enter your seat number: ";
            cin >> seatnumber;
            cin.ignore();
            examhall2 << " " << seatnumber << " ";
            examhall2.close();
        }
        break;

        case 'C':
        {
            ifstream h3("./TextFiles/h3.txt");
            while (!h3.eof())
            {
                h3.getline(seats, 100);
                cout << " " << seats << endl;
            }
            h3.close();
            ofstream examhall3("./TextFiles/h3.txt", ios::app);
            cout << endl
                 << "Enter your seat number: ";
            cin >> seatnumber;
            cin.ignore();
            examhall3 << " " << seatnumber << " ";
            examhall3.close();
        }
        break;

        default:
            break;
        }

        // this to generate unique seat no with alphabhets
        if (0 <= seatnumber < 20)
            seattype = 'N';
        else if (20 <= seatnumber < 60)
            seattype = 'P';
        else if (60 <= seatnumber < 80)
            seattype = 'E';
        else if (80 <= seatnumber < 100)
            seattype = 'V';
    }

public:
    void DisplayMenu()
    {

        cout << "Welcome User" << endl;
        cout << "--------------------------------" << endl;
        cout << "Now Showing" << endl
             << endl;
        // open file subject list
        subjectlist.open("./TextFiles/subjectlist.txt");
        // display till end of line subject list file
        while (!subjectlist.eof())
        {
            subjectid++;
            subjectlist.getline(subject, 100);
            cout << subjectid << " " << subject << endl
                 << endl;
        }
        // close the file
        subjectlist.close();
        // call the function
        SelectSubject();
    }

    void DisplaySlip()
    {
        string sname;
        switch (subjectid)
        {
        case 1:
            sname = "DBMS";
            break;

        case 2:
            sname = "OOP";
            break;

        case 3:
            sname = "SE";
            break;

        case 4:
            sname = "DIVP";
            break;

        case 5:
            sname = "DSP";
            break;

        case 6:
            sname = "EKIT";
            break;

        default:
            break;
        }
        cout << "\nSubject Name: " << sname;
        cout << "\nExam Time: " << timing[time];
        cout << "\nExam Seat No: " << examhallid << subjectid << seatnumber << hallticketid;

        ofstream halltxt;
        halltxt.open("./TextFiles/hallticket.txt", ios::app);
        halltxt << "\nSubject Name: " << sname;
        halltxt << "\nExam Time: " << timing[time];
        halltxt << "\nExam Seat No: " << examhallid << subjectid << seatnumber << hallticketid;

        halltxt.close();
    }
} ticketobj;

class User
{
private:
    short userid;
    string first_name;
    string last_name;
    string mobno;
    string emailid;
    char gender;

    void updatefile()
    {
        //this will just generate file call user.txt in which userid and firstname just for debug if code is working
        ofstream usertxt;
        usertxt.open("./TextFiles/user.txt", ios::app);
        usertxt << userid << " " << first_name;
        usertxt.close();
        displayprompt();
    }

protected:
    void userprompt()
    {
        //srand and rand together will create a different sequence of random numbers on every program run 
        srand(time(0));

        //so we will get always unique id everytime we run the program
        userid = rand();

        cout << endl
             << "Please enter your First Name: ";
        cin >> first_name;
        cout << endl
             << "Please enter your Last Name: ";
        cin >> last_name;
        cout << "\nPlease enter your Mobile Number: ";
        cin >> mobno;
        cout << "\nPlease enter your Email ID: ";
        cin >> emailid;
        cout << "\nPlease select you Gender (M, F): ";
        cin >> gender;

        //in fail safe function is call where we will check enter data is valid or not
        failsafe();
    }

    void failsafe()
    {
        while (mobno.size() != 10)
        {
            cout << "\nXX Please a 10 digit Mobile Number: ";
            cin >> mobno;
        }
        while (emailid.find('@') == string::npos || emailid.find('.') == string::npos)
        {
            cout << "\nXX Please enter a valid Emaild ID: ";
            cin >> emailid;
        }
        while (gender != 'M' && gender != 'F' && gender != 'O')
        {
            cout << "\nXX Please select a Gender from the given options: ";
            cin >> gender;
        }

        //call function update file
        updatefile();
    }

public:

    void displayprompt()
    {
        if (gender == '\0')//if gender is null
            // call function user prompt
            userprompt();
        else
        {

            cout << "\nHall Ticket No: " << userid;
            cout << "\nStudent Name: " << first_name << " " << last_name;
            cout << "\nStudent Mobile Number: " << mobno;
            cout << "\nStudent Email ID: " << emailid;
            cout << "\nStudent Gender: " << gender;

            // generate hallticket text file
            ofstream halltxt;
            halltxt.open("./TextFiles/hallticket.txt", ios::app);
            halltxt << "\nHall Ticket No: " << userid;
            halltxt << "\nStudent Name: " << first_name << " " << last_name;
            halltxt << "\nStudent Mobile Number: " << mobno;
            halltxt << "\nStudent Email ID: " << emailid;
            halltxt << "\nStudent Gender: " << gender;
            halltxt.close();
        }
    }
} user;

class Payment
{
private:
    short amount;
    string upi;

public:
    bool paymentGateway()
    {
        switch (seattype)
        {
        case 'N':
            amount = 100;
            cout << "\nExam Fees Rs." << amount << endl;
            break;
        case 'P':
            amount = 100;
            cout << "\nExam Fees Rs." << amount << endl;
            break;
        case 'E':
            amount = 100;
            cout << "\nExam Fees Rs." << amount << endl;
            break;
        case 'V':
            amount = 100;
            cout << "Exam Fees Rs." << amount << endl;
            break;
        default:
            break;
        }
        hallticketid = rand();
        cout << "\nPlease enter your UPI ID: ";
        cin >> upi;
        //find()- Find position of a character
        if (upi.find('@') == string::npos || upi.find('.') == string::npos)
        {
            cout << "\nXX Please enter a valid UPI ID: ";
            cin >> upi;
            return false;
        }
        else
            return true;
    }


    void display_amount_paid()
    {
        cout << "\nExam Fees Paid: Rs." << amount << "\nUPI ID: " << upi << endl;

        ofstream halltxt;
        halltxt.open("./TextFiles/hallticket.txt", ios::app);
        halltxt << "\nExam Fees Paid: Rs." << amount << "\nUPI ID: " << upi << endl
                << endl;
        halltxt.close();
    }
} booking;

int main()
{
    ticketobj.DisplayMenu();

    // this will always true after display menu function
    if (booking.paymentGateway())
    {
        user.displayprompt();
        ticketobj.DisplaySlip();
        booking.display_amount_paid();
    }
    return 0;
}
