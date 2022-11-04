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
    void Seat_Arrangement()
    {
        ofstream seats;
        seats.open("./TextFiles/h1.txt");
        seats << "\tSeats Arrangement" << endl;
        for (int i = 0; i < 10; i++)
        {
            for (int j = 0; j < 10; j++)
            {
                seats << i << j << " ";
                if (j == 9)
                    seats << endl;
            }
        }
        seats.close();
    }
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
        cin.ignore();
        while (success() == 1)
        {
            cout << "Please enter a valid Subject ID: ";
            cin >> subjectid;
            cin.ignore();
            success();
        }
        Timing();
    }

    void Timing()
    {
        cout << endl
             << "Timings" << endl
             << endl;
        if (subjectid <= 3)
        {
            for (int i = 0; i < 6; i++)
            {
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
        cin.ignore();
        Seatmap();
    }

    void Seatmap()
    {
        switch (examhallid)
        {
        case 'A':
        {
            ifstream h1("./TextFiles/h1.txt");
            cout << endl;
            while (!h1.eof())
            {
                h1.getline(seats, 100);
                cout << " " << seats << endl;
            }
            h1.close();
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

        system("clear");
        cout << "Welcome User" << endl;
        cout << "--------------------------------" << endl;
        cout << "Now Showing" << endl
             << endl;
        subjectlist.open("./TextFiles/subjectlist.txt");
        while (!subjectlist.eof())
        {
            subjectid++;
            subjectlist.getline(subject, 100);
            cout << subjectid << " " << subject << endl
                 << endl;
        }
        subjectlist.close();
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
        cout << "\nExam Seat No: " << examhallid << subjectid << seatnumber<<hallticketid;
        

        ofstream halltxt;
        halltxt.open("./TextFiles/hallticket.txt", ios::app);
        halltxt << "\nSubject Name: " << sname;
        halltxt << "\nExam Time: " << timing[time];
        halltxt << "\nExam Seat No: " << examhallid << subjectid << seatnumber<<hallticketid;
        
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
        ofstream usertxt;
        usertxt.open("./TextFiles/user.txt", ios::app);
        usertxt << userid << " " << first_name;
        usertxt.close();
        displayprompt();
    }

protected:
    void userprompt()
    {
        srand(time(0));
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
        updatefile();
    }

public:
    void displayprompt()
    {
        if (gender == '\0')
            userprompt();
        else
        {

            cout << "\nHall Ticket No: " << userid;
            cout << "\nStudent Name: " << first_name << " " << last_name;
            cout << "\nStudent Mobile Number: " << mobno;
            cout << "\nStudent Email ID: " << emailid;
            cout << "\nStudent Gender: " << gender;

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

    if (booking.paymentGateway())
    {
        user.displayprompt();
        ticketobj.DisplaySlip();
        booking.display_amount_paid();
    }
    return 0;
}