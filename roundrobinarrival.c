#include<stdio.h>

// -------------------- ROUND ROBIN WAITING TIME --------------------
void findwaitingtime(int process[], int n, int bt[], int at[], int wt[])
{
    int rem_bt[n];
    int t = 0;
    int quantum = 4;  // your time quantum

    for(int i=0;i<n;i++)
        rem_bt[i] = bt[i];

    int done;

    while(1)
    {
        done = 1;

        for(int i=0;i<n;i++)
        {
            if(rem_bt[i] > 0)
            {
                // ★ if process has NOT arrived yet → skip
                if(at[i] > t)
                {
                    t++;    // time moves until someone arrives
                    continue;
                }

                done = 0;

                if(rem_bt[i] > quantum)
                {
                    t += quantum;
                    rem_bt[i] -= quantum;
                }
                else
                {
                    t += rem_bt[i];
                    wt[i] = t - bt[i] - at[i];   // ★ RR waiting time with AT
                    rem_bt[i] = 0;
                }
            }
        }

        if(done)
            break;
    }
}

// ---------------- TURNAROUND TIME (same as yours) ----------------
void findturnaroundtime(int process[],int n, int bt[],int wt[],int tat[])
{
    for(int i=0;i<n;i++)
        tat[i]=bt[i]+wt[i];
}

// ---------------- AVERAGE + PRINT WITH GANTT CHART ----------------
void findaveragetime(int process[],int n, int bt[], int at[])
{
    int wt[n],tat[n];
    int twt=0, ttat=0;

    findwaitingtime(process,n,bt,at,wt);
    findturnaroundtime(process,n,bt,wt,tat);

    printf("Process\tAT\tBT\tWT\tTAT\n");
    for(int i=0;i<n;i++)
    {
        twt+=wt[i];
        ttat+=tat[i];
        printf("P%d\t%d\t%d\t%d\t%d\n",
                process[i],at[i],bt[i],wt[i],tat[i]);
    }

    printf("\nAverage Waiting Time: %f\n",(float)twt/n);
    printf("Average Turnaround Time: %f\n",(float)ttat/n);

    // -------------------- GANTT CHART --------------------
    printf("\nGantt Chart:\n");

    printf(" ");
    for(int i=0;i<n;i++) printf("---------");
    printf("\n|");

    for(int i=0;i<n;i++) printf("   P%d   |", process[i]);
    printf("\n ");

    for(int i=0;i<n;i++) printf("---------");

    printf("\n%d", at[0]);
    int time = at[0];

    for(int i=0;i<n;i++)
    {
        if(time < at[i]) time = at[i]; // ★ idle time
        time += bt[i];
        printf("        %d", time);
    }

    printf("\n");
}

// -------------------- MAIN (only AT added) --------------------
int main()
{
    int process[]={1,2,3};
    int n = sizeof(process)/sizeof(process[0]);

    int bt[]={23,3,3};
    int at[]={0,2,4};   // ★ arrival times added

    findaveragetime(process,n,bt,at);

    return 0;
}
