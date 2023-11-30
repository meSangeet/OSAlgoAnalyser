#include<bits/stdc++.h>
#include "cpuschedule.h"
#include "diskSceduling.h"
using namespace std;

int main()
{
    int n;
    do{
        system("CLS");
        int p; 
        cout<<endl<<"-----------------------------------------"<<endl;
        cout<<"|        Welcome To Algo Analyser        |";
        cout<<endl<<"-----------------------------------------"<<endl;
        cout<<"|   Select one of the options            |"<<endl;
        cout<<"|    1. CPU Scheduling Analysis          |\n";
        cout<<"|    2. Disc Scheduling Analysis         |\n";
        cout<<"|    3. Exit                             |";
        cout<<endl<<"-----------------------------------------"<<endl;
        cout<<"\n\n\nEnter here - "; cin>>p;
        n = p;

        if(n == 1)
        {
            executeCPU();
            string a;
            cout<<endl<<"Enter anything to continue - "; cin>>a;
        }

        if(n == 2)
        {
            executeDisk();
            string a;
            cout<<endl<<"Enter anything to continue - "; cin>>a;
        }


    }while(n != 3);
    return 0;
}
