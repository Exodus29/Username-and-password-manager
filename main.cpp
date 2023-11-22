#include <iostream>
#include <fstream>
#include <ctype.h>
#include <vector>
using namespace std;

/*
The user can create an account with a unique username of their choice and their own password. They can then login
and the program will notify of incorrect account details. The program also can allow the user to change their password
*/

void signUp()
{
    // create an object for usernames and for the passwords
    fstream usr, pass;
    usr.open("usernames.txt", ios::app);    // usernames file
    pass.open("passwords.txt", ios::app);   // passwords file
    string username;    // contains their username
    string password;    // contains their password
    string confirmPass; // contains their password that will be compared to string password to confirm their password


    // get username and password
    cout<<"Enter your desired username: ";
    getline(cin, username);
    cout<<"Enter your password: ";
    getline(cin, password);
    cout<<"confirm your password: ";
    getline(cin, confirmPass);


    // check if the entered username contains any spaces and ask to re-enter. It will continue to ask until they enter a valid username
    while(true)
    {
        for(int i = 0; i < username.length(); i++)
        {
            if(isspace(username[i]) == 8)
            {
                cout<<"Invalid. Username can not contain spaces. Enter a valid username: ";
                getline(cin, username);
                i = 0;
            }
        }
        break;
    }


    // check if the password matches the password confirmation and ask to re-enter if it doesn't match
    while(true)
    {
        if(password != confirmPass)
        {
            cout<<"Your the two passwords entered do not match. Try again."<<endl;
            cout<<"Enter password: ";
            getline(cin, password);
            cout<<"Confirm password: ";
            getline(cin, confirmPass);
        }
        else
        {
            break;
        }
    }


    // check if the entered password contains any spaces and ask to re-enter. It will continue to ask until they enter a valid password
    while(true)
    {
        for(int i = 0; i < password.length(); i++)
        {
            if(isspace(password[i]) == 8)
            {
                cout<<"Invalid Password can't contain any spaces. Enter a valid password: ";
                getline(cin, password);
                i = 0;
            }
        }
        break;
    }


    // store the username and password in seperate files
    usr<<username<<endl;
    pass<<password<<endl;
    usr.close();
    pass.close();

}

void login()
{
    ifstream readUsr, readPass;
    readUsr.open("usernames.txt");
    readPass.open("passwords.txt");
    vector<string> ifstreamPass(0); // stores all the passwords from the password file
    vector<string> ifstreamUsr(0);  // stores all the usernames from the username file
    string readU; // stores the individual usernames from username file
    string readP;   // stores the individual passwords from password file
    string loginUsr;    // entered username
    string loginPass;   // enetered password

    // get login info
    cout<<"Enter username: ";
    getline(cin, loginUsr);
    cin.clear();
    cout<<"Enter password: ";
    getline(cin, loginPass);
    cin.clear();

    // take all the usernames and passwords and store them in seperate vector arrays
    while(readUsr>>readU && readPass>>readP)
    {
        ifstreamUsr.push_back(readU);
        ifstreamPass.push_back(readP);
    }


    // loop through both vector arrays to compare and see if any the login info entered matches any of the info in the files
    for(int i = 0; i < readU.size(); i++)
    {
        if(loginUsr == ifstreamUsr[i] && loginPass == ifstreamPass[i]) // check if the entered info matches the currently read lines from the file
        {
            break;
        }
        else if(i = readU.size()-1 && loginUsr != ifstreamUsr[i] && loginPass == ifstreamPass[i]) // check if we have reached the end of the loop. If so this means that either the username or password entered is incorrect
        {
            cout<<"Username or password is incorrect. Try again."<<endl;
            cout<<"Enter username: ";
            getline(cin, loginUsr);
            cin.clear();
            cout<<"Enter password: ";
            getline(cin, loginPass);
            cin.clear();
            i = 0;
            continue;
        }
    }
    cout<<"Logged in"<<endl;

    readUsr.close();
    readPass.close();
}

void forgotPass()
{
    ifstream readUsernames, readPass;
    readUsernames.open("usernames.txt");     // used to read username file
    readPass.open("passwords.txt");         // used to read password file

    string targetUsr;                     // username of the passoword being changed
    string read_username;                // used to store each individual username and will be used to be compared to targetUsr later
    string pass;                         // used to store each inidivdual password
    vector<string> passwords;           // stores all the passwords
    string newPass;                     // contains user's new password
    int line_number = passwords.size(); // contains the total number of passwords in the password file
    int usrnameLine = 0;                //stores the line position of the target username

    // get the username
    cout<<"Enter your username: ";
    getline(cin, targetUsr);
    cin.clear();

    // run through the username file and find the target username and it's line number
    while(getline(readUsernames, read_username))
    {
        if(read_username == targetUsr) // checks if we found the correct username
        {
            break;
        }
        else if(readUsernames.eof() == true && targetUsr != read_username)
        {
            cout<<"Username does not exist, try again."<<endl;
            cout<<"Enter username: ";
            getline(cin, targetUsr);
            cin.clear();
            usrnameLine = 0;
        }
        else
        {
            usrnameLine++;
        }
    }
    readUsernames.close();

    // take every password and store it in a vector array from the top to bottom of the file
    while(getline(readPass, pass))
    {
        passwords.push_back(pass);
    }
    readPass.close();


    // get their new password
    cout<<"Enter your new password: ";
    getline(cin, newPass);
    cin.clear();

    // check if the entered password contains any spaces and ask to re-enter. It will continue to ask until they enter a valid password
    while(true)
    {
        for(int i = 0; i < newPass.length(); i++)
        {
            if(isspace(newPass[i]) == 8)
            {
                cout<<"Invalid Password can't contain any spaces. Enter a valid password: ";
                getline(cin, newPass);
                cin.clear();
                i = 0;
            }
        }
        break;
    }
    passwords[usrnameLine] = newPass; // store their password in the array at the same

    ofstream writePass;
    writePass.open("passwords.txt");    // used to overwrite the passwords file with the new password

    // overwrite the password file with the changed list of passwords
    for(int i = 0; i < passwords.size(); i++)
    {
        writePass<<passwords[i]<<endl;
    }
    writePass.close();
    cout<<endl;
    cout<<"Password successfully changed."<<endl;

}

int main()
{

    int input; // contains the user's choice of loging in or signing up 

    // main screen
    cout<<"-------------------------------------------------"<<endl;
    cout<<"| Welcome to my Login and registration program  |"<<endl;
    cout<<"-------------------------------------------------"<<endl;
    cout<<endl;
    cout<<"1. Login"<<endl;
    cout<<"2. sign up"<<endl;
    cout<<"3. Forgot password"<<endl;
    cout<<endl;
    cout<<"choose an option: ";
    cin>>input;
    cin.ignore();

    switch (input)
    {
    case 1:
        login();
        break;
    case 2:
        signUp();
        break;
    case 3:
        forgotPass();
        break;
    default:
        break;
    }


    return 0;
}