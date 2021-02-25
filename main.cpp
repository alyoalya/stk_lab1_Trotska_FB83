#include <iostream>
#include<istream>
#include<fstream>
#include<stdlib.h>
#include<string.h>
#include <dos.h>
#include <windows.h>
#include <time.h>
#include <errno.h>

using namespace std;


struct userMenu{
    public:

        void login(){
            int count=0;
            string password, username, usernameAttempt, passwordAttempt, blocked, restriction;

            for(int i=0; i<3; i++){
            cout << "Enter your login and password\nUsername:";
            cin >> usernameAttempt;
            cout << "Password:";
            cin >> passwordAttempt;

            ifstream input("database.txt");
                while(input>>username>>password>>blocked>>restriction)
                {
                        if(username==usernameAttempt && password==passwordAttempt)
                        {
                                count=1;
                        };
                        if (blocked=="y")
                {
                   cout << "You were blocked by admin!Good bye!" << endl;
                   exit(0);
                };
                }
                input.close();

                if(count==1)
                {
                        cout<<"\nHello "<<usernameAttempt<<"\nLOGIN SUCCESS\n";
                        cin.get();
                        cin.get();
                        system("cls");
                        userPanel();
                }
                else
                {
                        cout<<"\nLOGIN ERROR\nPlease check your username and password\n"<<endl;


                }

        }
        Sleep(5000);
        exit(0);
        }


        void logup(){
            string password, username, repassword,blocked, restriction;
            cout << "Select username: ";
            cin >> username;
            cout << "Select password: ";
            cin >> password;
            if (username==password)
                {
                    cout << "Username and password should not be equal!" << endl;
                    logup();
                }
            cout << "Retype password: ";
            cin >> repassword;
            if(repassword==password){
                    ofstream reg("database.txt",ios::app);
                blocked = "n";
                restriction = "y";
                reg<<username<<" "<<password<<" "<<blocked<<" "<<restriction<<endl;
                system("cls");
                cout << "Success!" << endl;
                login();}

            else
            {
                cout << "Wrong password! Please check password" << endl;
                logup();
            }


        };


        void userPanel(){
                        int option;
                        umenu:
                        cout<<"\n";
                        cout<<"\t\t ================================================\n";
                        cout<<"\t\t|                     User                      |\n";
                        cout<<"\t\t ================================================\n\n\n";
                        cout<<"\t\t-------------------------------------------------\n";
                        cout<<"\t\t|\t1. Change password \t\t\t|\n";
                        cout<<"\t\t-------------------------------------------------\n";
                        cout<<"\t\t-------------------------------------------------\n";
                        cout<<"\t\t|\t2. Exit \t\t\t\t|\n";
                        cout<<"\t\t-------------------------------------------------\n";
                        cout << "Choose option: ";
                        cin >> option;
                        switch(option){
                           case 1:
                                {
                                        string deleteline;
                                        string line, newline, newline1, username, password,blocked,restriction;
                                        ifstream input("database.txt");
                                        while(input>>username>>password>>blocked>>restriction)
                                        {
                                        ifstream fin;
                                        fin.open("database.txt");
                                        ofstream temp;
                                        temp.open("temp.txt");
                                        cout << "Enter old password: ";
                                        cin >> deleteline;
                                        cout << "Enter new password:";
                                        cin >> newline;
                                        if (restriction=="y" && newline==username){
                                                        cout << "Username and password should not be equal!";
                                                        Sleep(5000);
                                                        system("cls");
                                                        goto umenu;

                                                }
                                        cout << "Retype new password:";
                                        cin >> newline1;

                                        if(newline==newline1){

                                        while (getline(fin,line))
                                        {
                                            line.replace(line.find(deleteline),deleteline.length(),newline);
                                            temp << line << endl;
                                            remove(line.c_str());
                                        }
                                        while (getline(fin,line))
                                        {
                                            line.replace(line.find(deleteline),deleteline.length(),newline);
                                            temp << line << endl;
                                        }

                                        temp.close();
                                        fin.close();
                                        }
                                        else
                                            {cout << "Passwords should not be equal!" << endl;
                                            system("cls");
                                            goto umenu;};
                                        }
                                        input.close();
                                        remove("database.txt");
                                        rename("temp.txt","database.txt");
                                        cout << "Password was updated!" << endl;
                                        Sleep(5000);
                                        system("cls");
                                        goto umenu;
                                        };

                           case 2:
                                exit(0);
                               }

        };



    private:
        string password;
        string username;
        string usernameAttempt;
        string passwordAttempt;
        string blocked;
        string restriction;
};





struct adminMenu{
    private:
        string adminname = "ADMIN";
        string username;
        string password;
        string blocked;
        string restriction;
        string passwordAdmin;
        string adminnameAttempt;
        string passwordAttemptAdmin;

    public:
        void loginAdmin(){
            int count=0;
            cout << "Enter admin's login and password\nAdmin name:";
            cin >> adminnameAttempt;
            cout << "Password:";
            cin >> passwordAttemptAdmin;

            ifstream input("admin.txt");
                while(input>>adminname>>passwordAdmin)
                {
                        if("ADMIN"==adminnameAttempt && passwordAdmin==passwordAttemptAdmin)

                        {
                                count=1;
                                //system("cls");
                        }
                }
                input.close();
                if(count==1)
                {
                        cout<<"\nADMIN LOGIN SUCCESS\n";
                        cin.get();
                        cin.get();
                        system("cls");
                        adminPanel();

                }
                else
                {
                        cout<<"\nADMIN LOGIN ERROR\n";
                        exit(0);
                }
        };


        void addUser(){
            string username, password, blocked, restriction;
            cout << "Add user with such username: ";
            cin >> username;
             blocked = "n";
                restriction = "y";
                ofstream reg("database.txt",ios::app);
                reg<<username<<' '<<password<<' '<<blocked<<' '<<restriction<<endl;
                cout << "Successfully added!" << endl;
                Sleep(5000);
                system("cls");
        };

        void blockUser(){
            string symbol;
            cout << "Choose user to change option of block: ";
            cin >> username;
             ifstream input("database.txt");
                while(input>>username>>password>>blocked>>restriction)
                {
                    cout << "Make user be blocked? (y/n): ";
                    cin >> symbol;
                    string line;
                    ifstream fin;
                    fin.open("database.txt");
                    ofstream temp;
                    temp.open("temp3.txt");

                    while (getline(fin,line))
                        {
                        line.replace(line.find(blocked),blocked.length(),symbol);
                        temp << line << endl;
                        remove(line.c_str());
                        }
                    while (getline(fin,line))
                        {
                        line.replace(line.find(blocked),blocked.length(), symbol);
                        temp << line << endl;}


                    temp.close();
                    fin.close();



                }
                input.close();
                remove("database.txt");
                rename("temp3.txt","database.txt");
                cout << "Option of block was updated!" << endl;
                Sleep(5000);
                system("cls");
                }



        void changeOptions(){
            string symbol;
            cout << "Choose user to change option of restriction: ";
            cin >> username;
             ifstream input("database.txt");
                while(input>>username>>password>>blocked>>restriction)
                {
                    cout << "Make restrictions? (y/n): ";
                    cin >> symbol;
                    string line;
                    ifstream fin;
                    fin.open("database.txt");
                    ofstream temp;
                    temp.open("temp3.txt");

                    while (getline(fin,line))
                        {
                        line.replace(line.find(restriction),restriction.length(),symbol);
                        temp << line << endl;
                        remove(line.c_str());
                        }
                    while (getline(fin,line))
                        {
                        line.replace(line.find(restriction),restriction.length(), symbol);
                        temp << line << endl;}


                    temp.close();
                    fin.close();



                }
                input.close();
                remove("database.txt");
                rename("temp3.txt","database.txt");
                cout << "Option of restriction was updated!" << endl;
                Sleep(5000);
                system("cls");
                }


        void adminPanel(){
            int option;
            umenu:

                        cout<<"\n";
                        cout<<"\t\t ================================================\n";
                        cout<<"\t\t|                     Admin                      |\n";
                        cout<<"\t\t ================================================\n\n\n";
                        cout<<"\t\t-------------------------------------------------\n";
                        cout<<"\t\t|\t1. Change password \t\t\t|\n";
                        cout<<"\t\t-------------------------------------------------\n";
                        cout<<"\t\t-------------------------------------------------\n";
                        cout<<"\t\t|\t2. View users \t\t\t\t|\n";
                        cout<<"\t\t-------------------------------------------------\n";
                        cout<<"\t\t-------------------------------------------------\n";
                        cout<<"\t\t|\t3. Add user \t\t\t\t|\n";
                        cout<<"\t\t-------------------------------------------------\n";
                        cout<<"\t\t-------------------------------------------------\n";
                        cout<<"\t\t|\t4. Block user \t\t\t\t|\n";
                        cout<<"\t\t-------------------------------------------------\n";
                        cout<<"\t\t-------------------------------------------------\n";
                        cout<<"\t\t|\t5. Change user options \t\t\t|\n";
                        cout<<"\t\t-------------------------------------------------\n";
                        cout<<"\t\t-------------------------------------------------\n";
                        cout<<"\t\t|\t6. Exit \t\t\t\t|\n";
                        cout<<"\t\t-------------------------------------------------\n\n";
                        cout << "Choose option: ";
                        cin >> option;
                        switch(option){
                           case 1:
                                {
                                        string deleteline;
                                        string line, newline, newline1;

                                        ifstream fin;
                                        fin.open("admin.txt");
                                        ofstream temp;
                                        temp.open("temp1.txt");
                                        cout << "Enter old password: ";
                                        cin >> deleteline;
                                        cout << "Enter new password:";
                                        cin >> newline;
                                        cout << "Retype new password:";
                                        cin >> newline1;

                                        if(newline==newline1){
                                        while (getline(fin,line))
                                        {
                                            line.replace(line.find(deleteline),deleteline.length(),newline);
                                            temp << line << endl;
                                        }

                                        temp.close();
                                        fin.close();
                                        remove("admin.txt");
                                        rename("temp1.txt","admin.txt");
                                        cout << "Password was updated!" << endl;
                                        Sleep(5000);
                                        system("cls");
                                        goto umenu;
                                        }
                                        else
                                            {cout << "Passwords are not equal!"<<endl;
                                            system("cls");
                                            goto umenu;};
                                        break;

                            };


                           case 2:
                            {
                                string line;
                                ifstream in("database.txt");
                                if (in.is_open())
                                {
                                    while (getline(in, line))
                                    {
                                        cout << line << endl;
                                    }
                                }
                                in.close();
                                Sleep(5000);
                                system("cls");
                                goto umenu;
                            };


                           case 3:
                            {
                                addUser();
                                goto umenu;
                            };

                           case 4:
                            {
                                blockUser();
                                goto umenu;
                            };

                            case 5:
                            {
                                changeOptions();
                                goto umenu;
                            };

                           case 6:
                            exit(0);
                        }
        };
        };




void exit()
{
	cout<<"\nYou choose to exit.\n"<<endl;
}

int main()
{
    system("COLOR 79");
	int option;
	userMenu app;
	adminMenu appadmin;
	do
	{
	    menu:
	cout<<"\n";
    cout<<"\t\t ================================================\n";
	cout<<"\t\t|                 My system                     |\n";
	cout<<"\t\t ================================================\n\n\n";
	cout<<"\t\t-------------------------------------------------\n";
	cout<<"\t\t|\t1. User \t\t\t\t|\n";
	cout<<"\t\t-------------------------------------------------\n";
	cout<<"\t\t-------------------------------------------------\n";
	cout<<"\t\t|\t2. Administrator \t\t\t|\n";
	cout<<"\t\t-------------------------------------------------\n";
	cout<<"\t\t-------------------------------------------------\n";
	cout<<"\t\t|\t3. About program \t\t\t|\n";
	cout<<"\t\t-------------------------------------------------\n";
	cout<<"\t\t-------------------------------------------------\n";
	cout<<"\t\t|\t4.  Exit \t\t\t\t|\n";
	cout<<"\t\t-------------------------------------------------\n\n";

    	cout<<"\t\tWho are you? Choose your user type: ";
	cin>>option;
	system("cls");
	switch(option)
	{
		case 1:
            int choice;
            cout<<"\n";
            cout<<"\t\t ================================================\n";
            cout<<"\t\t|                     User                       |\n";
            cout<<"\t\t ================================================\n\n\n";
            cout<<"\t\t-------------------------------------------------\n";
            cout<<"\t\t|\t1. Log in \t\t\t\t|\n";
            cout<<"\t\t-------------------------------------------------\n";
            cout<<"\t\t-------------------------------------------------\n";
            cout<<"\t\t|\t2. Log up \t\t\t\t|\n";
            cout<<"\t\t-------------------------------------------------\n";
            cout<<"\t\t-------------------------------------------------\n";
            cout<<"\t\t|\t3. Exit \t\t\t\t|\n";
            cout<<"\t\t-------------------------------------------------\n\n";

            cout << "Choose your option: ";
            cin >> choice;
            switch(choice)
            {
            case 1:
                app.login();

            case 2:
                app.logup();

            case 3:
                system ("PAUSE");
                return 0;
            }
			break;

		case 2:
		    cout<<"\t\t|                 Admin                     |\n";
		    cout<<"\t\t---------------------------------------------\n";
			appadmin.loginAdmin();
			break;

        case 3:
            char symbol;
            cout << "Author: Alina Trotska"<< endl << "Variant: 17" << endl << "Task: Username and password should not be equal." << endl;
            cout << "Do you want to go back to menu? (y/n): ";
            cin >> symbol;
            switch(symbol)
            {
                case 'y':
                    system("cls");
                    goto menu;
                case 'n':
                    exit(0);
            }

		case 4:
			goto a;
			break;
	}

	}
	while(option!=4);//end do
		a://goto
		cout<<"thank you"<<endl;
		system ("PAUSE");
        return 0;
}
