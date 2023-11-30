#include <bits/stdc++.h>
#ifdef LOCAL
#else
#define dbg(...)
#endif
#define ar array
#define ll long long
#define ld long double
#define sza(x) ((int)x.size())
#define all(a) (a).begin(), (a).end()

using namespace std;

struct Process {
    int p; // Process ID
    int bt; // Burst Time
    int at; // Arrival Time
    int rt; // Remaining Burst Time
    int wt; // Waiting Time
    int tat; // Turn Around Time
    int priority;
    int age = 0;
} *p, temp, *org, *v;

// int arrival_time[25] = {0, 0, 0, 3, 3, 3, 7, 7, 7, 13, 13, 13, 17, 17, 19, 21, 23, 24, 24, 24, 24, 24, 25, 25, 26};
// int burst_time[25] = {1, 1, 1, 1, 2, 3, 3, 2, 1, 1, 2, 3, 5, 2, 4, 7, 3, 5, 1, 3, 5, 4, 8, 4, 3};
// int priority[25] = {3, 4, 5, 1, 3, 1, 1, 2, 1, 2, 1, 4, 5, 8, 6, 2, 1, 6, 7, 3, 3, 3, 4, 1, 2};

struct comp {
    string algo;
    float avg_wt;
    float avg_tat;
    comp()
    {
        algo ="null";
        avg_wt = 0.0;
        avg_tat = 0.0;
    }
};

void menu(vector<comp> &alg);
void input();
void assign();
void comparator(vector<comp> &alg);
void isjf(int, vector<comp> &alg);
void irr(int, vector<comp> &alg);
void priority(int menu_flag, vector<comp> &alg);
void fcfs(int menu_flag, vector<comp> &alg);
int n;
//cin>>n;


void comparator(vector<comp> &alg) {
    isjf(0, alg);
    irr(0, alg);
    fcfs(0, alg);
    priority(0, alg);

    cout << "\n\n############# Comparing #############\n\n";
    cout << "\n\n Algorithm\t\tAVG_WT\t\tAVG_TAT\n\n";
    for (int i = 1; i < 5; i++)
        if (alg[i].algo.size() > 4)
            cout << "     " << alg[i].algo << "\t\t" << alg[i].avg_wt << "\t\t" << alg[i].avg_tat << "\n";
        else
            cout << "     " << alg[i].algo << "\t\t" << alg[i].avg_wt << "\t\t" << alg[i].avg_tat << "\n";

    menu(alg);
}

void input() {
    // Input arrival time, burst time, and priority for each process
    for (int i = 0; i < n; ++i) {
        cout << "Process " << i + 1 << ":\n";
        cout << "  Arrival Time: ";
        cin >> org[i].at;
        cout << "  Burst Time: ";
        cin >> org[i].bt;
        cout << "  Priority: ";
        cin >> org[i].priority;
        org[i].p = i + 1;
        org[i].rt = org[i].bt;
    }
}

int executeCPU() {
    cout << "Enter the number of processes: ";
    cin>>n;
    p = new Process[n];
    org = new Process[n];
    v = new Process[n];
    vector<comp> alg(5);

    // Input arrival time, burst time, and priority for each process
    for (int i = 0; i < n; ++i) {
        cout << "Process " << i + 1 << ":\n";
        cout << "  Arrival Time: ";
        cin >> org[i].at;
        cout << "  Burst Time: ";
        cin >> org[i].bt;
        cout << "  Priority: ";
        cin >> org[i].priority;
        org[i].p = i + 1;
        org[i].rt = org[i].bt;
    }

    system("CLS");

    cout << "---------------------------------------------------------------------------------\n";
    cout << "|         Here are the original Inputs entered by the user                       |\n";
    cout << "---------------------------------------------------------------------------------\n";
    cout << "\t\tProcess ID\t\tProcess Arrival Time\t\tProcess Burst Time\t\tProcess Priority\n\n";
    for (int i = 0; i < n; i++)
        cout << "\t\t" << org[i].p << "\t\t\t\t\t" << org[i].at << "\t\t\t" << org[i].bt
             << "\t\t\t" << org[i].priority << "\n";
    cout << "---------------------------------------------------------------------------------\n";
    menu(alg);
    return 0;
}

void menu(vector<comp> &alg) {
    int ch;
    printf("\n\nTable\n\n1.ISJF Algorithm\n2.IRR Algorithm\n3.fcfs\n4.priority scheduling\n5.Compare All\n6.Exit");
    printf("\n\nEnter your choice from the above table : ");
    cin >> ch;
    switch (ch) {
        case 1:
            isjf(1, alg);
            break;
        case 2:
            irr(1, alg);
            break;
        case 3:
            fcfs(1, alg);
            break;
        case 4:
            priority(1, alg);
            break;
        case 5:
            comparator(alg);
            break;
        case 6:
            return;
            break;
        default:
            cout << "\n\nPlease enter choice from 1 to 6 only\n";
            menu(alg);
    }
}

void sort_at() {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (p[j].at > p[j + 1].at) {
                temp = p[j];    
                p[j] = p[j + 1];
                p[j + 1] = temp;
            }
        }
    }
}

void assign() {
    for (int i = 0; i < n; i++)
        p[i] = org[i];
}

bool compare(Process &x, Process &y) {
    return x.priority < y.priority;
}

void findTurnAroundTime(vector<Process> proc, int n, int wt[], int tat[]) {
    for (int i = 0; i < n; i++)
        tat[i] = proc[i].bt + wt[i];
}

void findWaitingTime(vector<Process> proc, int n, int wt[]) {
    int rem_time[n];
    for (int i = 0; i < n; i++)
        rem_time[i] = proc[i].bt;
    int complete = 0, t = 0, minm = INT_MAX;
    int shortest = 0, finish_time;
    bool check = false;
    while (complete != n) {
        for (int j = 0; j < n; j++) {
            if (((proc[j].at <= t && rem_time[j] < minm) || proc[j].age > 2 || proc[j].priority == 0) &&
                rem_time[j] > 0) {
                minm = rem_time[j];
                shortest = j;
                check = true;
            }
        }
        if (check == false) {
            t++;
            if (t % 10 == 0)
                for (int k = 0; k < n; k++)
                    proc[k].age++;
            if (t % 50 == 0)
                for (int k = 0; k < n; k++)
                    proc[k].priority--;
            continue;
        }
        rem_time[shortest]--;
        minm = rem_time[shortest];
        if (minm == 0)
            minm = INT_MAX;
        if (rem_time[shortest] == 0) {
            complete++;
            check = false;
            finish_time = t + 1;
            wt[shortest] = finish_time - proc[shortest].at - proc[shortest].bt;
                //TAT= CT- AT    WT= TAT-BT 
            if (wt[shortest] < 0)
                wt[shortest] = 0;
        }
        t++;
    }
}

void isjf(int menu_flag, vector<comp> &alg) {
    for (int i = 0; i < n; i++) {
        v[i] = org[i];
    }
    vector<Process> vec;
    for (int i = 0; i < n; i++) {
        vec.push_back(v[i]);
    }
    sort(vec.begin(), vec.end(), compare);

    int wt[n], tat[n], total_wt = 0, total_tat = 0;
    findWaitingTime(vec, n, wt);
    findTurnAroundTime(vec, n, wt, tat);


    system("CLS");

    cout << "---------------------------------------------------------------------------------\n";
    cout << "|         Here are the output for isjf                                           |\n";
    cout << "---------------------------------------------------------------------------------\n";

    cout << " PID\t\t" << "Pri\t\t" << "AT\t\t" << "BT\t\t" << "WT\t\t" << "TAT\t\t\n";
    for (int i = 0; i < n; i++) {
        total_wt = total_wt + wt[i];
        total_tat = total_tat + tat[i];
        cout << " " << v[i].p << "\t\t" << v[i].priority << "\t\t" << v[i].at << "\t\t" << v[i].bt << "\t\t "
             << wt[i] << "\t\t " << tat[i] << endl;
    }
    
    cout << "---------------------------------------------------------------------------------\n";

    cout << "\nAverage waiting time = " << (float)total_wt / (float)n;
    cout << "\nAverage turn around time = " << (float)total_tat / (float)n << endl;


    cout << "---------------------------------------------------------------------------------\n";

    alg[1].algo = "isjf";
    alg[1].avg_tat = (float)total_tat / (float)n;
    alg[1].avg_wt = (float)total_wt / (float)n;

    if (menu_flag)
        menu(alg);
}

void irr(int menu_flag, vector<comp> &alg) {
        system("CLS");

    cout << "---------------------------------------------------------------------------------\n";
    cout << "|         Here are the output for irr                                           |\n";
    cout << "---------------------------------------------------------------------------------\n";
    assign();
    int remain = n, rt[n], time_quantum, tot_wt = 0, tot_tat = 0, flag = 0;
    sort_at();
    for (int i = 0; i < n; i++)
        rt[p[i].p - 1] = p[p[i].p - 1].bt;

    cout << "\nEnter Time Quantum : ";
    cin >> time_quantum;

        system("CLS");

    cout << "---------------------------------------------------------------------------------\n";
    cout << "|         Here are the output for irr                                           |\n";
    cout << "---------------------------------------------------------------------------------\n";

    for (int i = 0, time = 0; remain != 0;) {
        if (p[i].rt <= time_quantum && p[i].rt > 0) {
            time += p[i].rt;
            p[i].rt = 0;
            flag = 1;
        } else if (p[i].rt > time_quantum && p[i].rt > 0 && time_quantum * 2 - p[i].rt >= 0) {
            time += p[i].rt;
            p[i].rt = 0;
            flag = 1;
        } else if (p[i].rt > 0) {
            p[i].rt -= time_quantum;
            time += time_quantum;
        }

        if (p[i].rt == 0 && flag == 1) {
            remain--;
            p[i].wt = time - p[i].at - p[i].bt;
            p[i].tat = time - p[i].at;
            tot_wt += p[i].wt;
            tot_tat += p[i].tat;
            flag = 0;
        }

        if (i == n - 1)
            i = 0;
        else if (p[i + 1].at <= time)
            i++;
        else
            i = 0;
    }

    cout << "Process    Burst Time    Arrival Time     Waiting Time    Turn Around Time\n";
    for (int i = 0; i < n; i++)
        cout << p[i].p << "\t\t" << p[i].bt << "\t\t" << p[i].at << "\t\t" << p[i].wt << "\t\t" << p[i].tat << "\n";

    cout << "---------------------------------------------------------------------------------\n";
    cout << "\nAverage Waiting Time = " << (float)tot_wt / n;
    cout << "\nAverage Turn Around Time = " << (float)tot_tat / n << "\n";

    alg[2].algo = "irr";
    alg[2].avg_tat = (float)tot_tat / n;
    alg[2].avg_wt = (float)tot_wt / n;

    if (menu_flag)
        menu(alg);
}




void fcfs(int menu_flag, vector<comp> &alg) {
    assign();
    sort_at();

    int wt[n], tat[n], total_wt = 0, total_tat = 0;
    wt[0] = 0;

    for (int i = 1; i < n; i++) {
        wt[i] = p[i - 1].bt + wt[i - 1];
    }

    for (int i = 0; i < n; i++) {
        tat[i] = p[i].bt + wt[i];
        total_wt += wt[i];
        total_tat += tat[i];
    }

            system("CLS");

    cout << "---------------------------------------------------------------------------------\n";
    cout << "|         Here are the output for fcfs                                           |\n";
    cout << "---------------------------------------------------------------------------------\n";
    cout << " Process\tBurst Time\tArrival Time\tWaiting Time\tTurn Around Time\n";
    for (int i = 0; i < n; i++) {
        cout << " " << p[i].p << "\t\t" << p[i].bt << "\t\t" << p[i].at << "\t\t" << wt[i] << "\t\t" << tat[i] << endl;
    }

    cout << "---------------------------------------------------------------------------------\n";
    cout << "\nAverage Waiting Time = " << (float)total_wt / n;
    cout << "\nAverage Turn Around Time = " << (float)total_tat / n << "\n";

    alg[3].algo = "fcfs";
    alg[3].avg_tat = (float)total_tat / n;
    alg[3].avg_wt = (float)total_wt / n;

    if (menu_flag)
        menu(alg);
}

void priority(int menu_flag, vector<comp> &alg) {
    assign();
    sort(p, p + n, [](const Process &a, const Process &b) {
        return a.priority < b.priority;
    });

    int wt[n], tat[n], total_wt = 0, total_tat = 0;
    wt[0] = 0;

    for (int i = 1; i < n; i++) {
        wt[i] = p[i - 1].bt + wt[i - 1];
    }

    for (int i = 0; i < n; i++) {
        tat[i] = p[i].bt + wt[i];
        total_wt += wt[i];
        total_tat += tat[i];
    }
            system("CLS");

    cout << "---------------------------------------------------------------------------------\n";
    cout << "|         Here are the output for priority scheduling                           |\n";
    cout << "---------------------------------------------------------------------------------\n";
    cout << " Process\tBurst Time\tArrival Time\tPriority\tWaiting Time\tTurn Around Time\n";
    for (int i = 0; i < n; i++) {
        cout << " " << p[i].p << "\t\t" << p[i].bt << "\t\t" << p[i].at << "\t\t" << p[i].priority << "\t\t" << wt[i] << "\t\t" << tat[i] << endl;
    }

    cout << "---------------------------------------------------------------------------------\n";
    cout << "\nAverage Waiting Time = " << (float)total_wt / n;
    cout << "\nAverage Turn Around Time = " << (float)total_tat / n << "\n";

    alg[4].algo = "priority";
    alg[4].avg_tat = (float)total_tat / n;
    alg[4].avg_wt = (float)total_wt / n;

    if (menu_flag)
        menu(alg);
}
