#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <conio.h>
#include <iomanip>

using namespace std;

int main()
{
    FILE *fp, *ft;
    char another, choice;

    struct student
    {
        string first_name, last_name;
        string course;
        string section;
    };

    struct student e;
    string xfirst_name, xlast_name;
    long int recsize;

    fp=fopen("Users.txt","rb+");

    if (fp == NULL)
    {
        fp = fopen("Users.txt","wb+");

        if (fp==NULL)
        {
            puts("Cannot open file");
            return 0;
        }
    }


    recsize = sizeof(e);

    while(1)
    {
        system("cls");

        cout << "\t\t====== STUDENT DATABASE MANAGEMENT SYSTEM ======";
        cout <<"\n\n                                          ";
        cout << "\n\n";
        cout << "\n \t\t\t 1. Add    Records";
        cout << "\n \t\t\t 2. List   Records";
        cout << "\n \t\t\t 3. Modify Records";
        cout << "\n \t\t\t 4. Delete Records";
        cout << "\n \t\t\t 5. Exit   Program";
        cout << "\n\n";
        cout << "\t\t\t Select Your Choice :=> ";
        fflush(stdin);
        choice = getche();
        switch(choice)
        {
        case '1' :
            fseek(fp,0,SEEK_END);
            another ='Y';
            while(another == 'Y' || another == 'y')
            {
                system("cls");
                cout << "Enter your First Name : \n";
                getline(cin ,e.first_name);
                cout << "Enter your Last Name : \n";
                getline(cin , e.last_name);
                cout << "Enter your Course    : \n";
                getline(cin, e.course);
                cout << "Enter your Section   : \n";
                getline(cin , e.section);
                fwrite(&e,recsize,1,fp);
                cout << "\n Add Another Record (Y/N) \n";
                fflush(stdin);
                another = getchar();
            }
            break;
        case '2':
            system("cls");
            rewind(fp);
            cout << "=== Records in the Database ===";
            cout << "\n";
            while (fread(&e,recsize,1,fp) == 1)
            {
                cout << "\n";
                cout <<"\n Name: " << e.first_name << " "<< e.last_name;
                cout <<"\n Course: " <<e.course ;
                cout<<"\n Section: "<< e.section;
            }
            cout << "\n\n";
            system("pause");
            break;

        case '3' :
            system("cls");
            another = 'Y';
            while (another == 'Y'|| another == 'y')
            {
                cout << "\n Enter the last name of the student : ";
                getline(cin, xlast_name);

                rewind(fp);
                while (fread(&e,recsize,1,fp) == 1)
                {
                    if (e.last_name==xlast_name)
                    {
                        cout << "Enter new First Name : ";
                        getline (cin ,e.first_name);
                        cout << "Enter new Last Name : ";
                        getline(cin ,e.last_name);
                        cout << "Enter new Course    : ";
                        getline(cin, e.course);
                        cout << "Enter new Section   : ";
                        getline (cin , e.section);
                        fseek(fp, - recsize, SEEK_CUR);
                        fwrite(&e,recsize,1,fp);
                        break;
                    }
                    else
                        cout<<"record not found";
                }
                cout << "\n Modify Another Record (Y/N) ";
                fflush(stdin);
                another = getchar();
            }
            break;


        case '4':
            system("cls");
            another = 'Y';
            while (another == 'Y'|| another == 'y')
            {
                cout << "\n Enter the last name of the student to delete : ";
                getline(cin ,xlast_name);

                ft = fopen("temp.dat", "wb");

                rewind(fp);
                while (fread (&e, recsize,1,fp) == 1)

                    if (e.last_name!=xlast_name)
                    {
                        fwrite(&e,recsize,1,ft);
                    }
                fclose(fp);
                fclose(ft);
                remove("Users.txt");
                rename("temp.dat","Users.txt");

                fp=fopen("Users.txt","rb+");

                cout << "\n Delete Another Record (Y/N) ";
                fflush(stdin);
                another = getchar();
            }

            break;

        case '5':
            fclose(fp);
            cout << "\n\n";
            cout << "\t\t     THANK YOU FOR VIEWING MY PROJECT ";
            cout << "\n\n";
            exit(0);
        }
    }


    system("pause");
    return 0;

    //The program might take around 3 seconds to start
}
