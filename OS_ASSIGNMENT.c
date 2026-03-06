#include <stdio.h>
#include <string.h>

struct Process {
    char pid[5];
    int at, bt, pr;
    int wt, tat, ct;
    int completed;
};

int main() {
    int n;
    printf("Enter number of processes: ");
    scanf("%d", &n);

    struct Process p[n];
    for (int i = 0; i < n; i++) {
        scanf("%s %d %d %d", p[i].pid, &p[i].at, &p[i].bt, &p[i].pr);
        p[i].completed = 0;
    }

    int completed = 0, time = 0;
    float totalWT = 0, totalTAT = 0;

    while (completed < n) {
        int idx = -1;
        int minPr = 9999;

        // Find process with highest priority (lowest pr) among arrived and not completed
        for (int i = 0; i < n; i++) {
            if (p[i].at <= time && !p[i].completed) {
                if (p[i].pr < minPr) {
                    minPr = p[i].pr;
                    idx = i;
                } else if (p[i].pr == minPr) {
                    // Tie-breaker: earlier arrival
                    if (p[i].at < p[idx].at) {
                        idx = i;
                    }
                }
            }
        }

        if (idx == -1) {
            time++; // No process available, move time forward
        } else {
            p[idx].wt = time - p[idx].at;
            p[idx].tat = p[idx].wt + p[idx].bt;
            time += p[idx].bt;
            p[idx].ct = time;
            p[idx].completed = 1;
            completed++;

            totalWT += p[idx].wt;
            totalTAT += p[idx].tat;
        }
    }

    printf("Waiting Time:\n");
    for (int i = 0; i < n; i++) {
        printf("%s %d\n", p[i].pid, p[i].wt);
    }

    printf("Turnaround Time:\n");
    for (int i = 0; i < n; i++) {
        printf("%s %d\n", p[i].pid, p[i].tat);
    }

    printf("Average Waiting Time: %.2f\n", totalWT / n);
    printf("Average Turnaround Time: %.2f\n", totalTAT / n);

    return 0;
}