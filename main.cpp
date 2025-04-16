#include <iostream>
#include <bits/stdc++.h>
using namespace std;
struct Process {
    int id, arrival, burst, remaining, priority, start = -1, end = 0;
};
void printTimeline(const vector<int>& timeline) {
    cout << "\n\tTime\tProcess\n";
    for (int i = 0; i < timeline.size(); i++) {
        cout << setw(4) << i <<" ~ "<< i+1 << "\t" << (timeline[i] == -1 ? "Idle" : "P" + to_string(timeline[i])) << "\n";
    }
}

// FCFS
void FCFS(vector<Process> processes) {
    vector<int> timeline;
    sort(processes.begin(), processes.end(), [](Process a, Process b) {
        return a.arrival < b.arrival;
    });

    int time = 0;
    for (auto& p : processes) {
        if (time < p.arrival)
            time = p.arrival;
        for (int i = 0; i < p.burst; ++i)
            timeline.push_back(p.id);
        time += p.burst;
    }
    printTimeline(timeline);
}

// SJF Non-preemptive
void SJF_NonPreemptive(vector<Process> processes) {
    vector<int> timeline;
    int n = processes.size(), time = 0, completed = 0;
    vector<bool> done(n, false);

    while (completed < n) {
        int idx = -1, minBT = 1e9;
        for (int i = 0; i < n; i++) {
            if (!done[i] && processes[i].arrival <= time && processes[i].burst < minBT) {
                minBT = processes[i].burst;
                idx = i;
            }
        }
        if (idx == -1) {
            timeline.push_back(-1);
            time++;
        } else {
            for (int i = 0; i < processes[idx].burst; i++)
                timeline.push_back(processes[idx].id);
            time += processes[idx].burst;
            done[idx] = true;
            completed++;
        }
    }
    printTimeline(timeline);
}

// SJF Preemptive
void SJF_Preemptive(vector<Process> processes) {
    vector<int> timeline;
    int n = processes.size(), time = 0, completed = 0;
    for (auto& p : processes) p.remaining = p.burst;
    while (completed < n) {
        int idx = -1, minBT = 1e9;
        for (int i = 0; i < n; i++) {
            if (processes[i].arrival <= time && processes[i].remaining > 0 && processes[i].remaining < minBT) {
                minBT = processes[i].remaining;
                idx = i;
            }
        }
        if (idx == -1) {
            timeline.push_back(-1);
        } else {
            processes[idx].remaining--;
            timeline.push_back(processes[idx].id);
            if (processes[idx].remaining == 0) completed++;
        }
        time++;
    }
    printTimeline(timeline);
}

// Priority Non-preemptive
void Priority_NonPreemptive(vector<Process> processes) {
    vector<int> timeline;
    int time = 0, completed = 0, n = processes.size();
    vector<bool> done(n, false);

    while (completed < n) {
        int idx = -1, minPriority = 1e9;
        for (int i = 0; i < n; i++) {
            if (!done[i] && processes[i].arrival <= time && processes[i].priority < minPriority) {
                minPriority = processes[i].priority;
                idx = i;
            }
        }
        if (idx == -1) {
            timeline.push_back(-1);
            time++;
        } else {
            for (int i = 0; i < processes[idx].burst; ++i)
                timeline.push_back(processes[idx].id);
            time += processes[idx].burst;
            done[idx] = true;
            completed++;
        }
    }
    printTimeline(timeline);
}

// Priority Preemptive
void Priority_Preemptive(vector<Process> processes) {
    vector<int> timeline;
    int n = processes.size(), time = 0, completed = 0;

    for (auto& p : processes) p.remaining = p.burst;

    while (completed < n) {
        int idx = -1, minPriority = 1e9;
        for (int i = 0; i < n; i++) {
            if (processes[i].arrival <= time && processes[i].remaining > 0 && processes[i].priority < minPriority) {
                minPriority = processes[i].priority;
                idx = i;
            }
        }
        if (idx == -1) {
            timeline.push_back(-1);
        } else {
            processes[idx].remaining--;
            timeline.push_back(processes[idx].id);
            if (processes[idx].remaining == 0) completed++;
        }
        time++;
    }
    printTimeline(timeline);
}

// Round Robin
void RoundRobin(vector<Process> p, int quantum) {
    int n = p.size(), time = 0, completed = 0;
    for (auto& proc : p) proc.remaining = proc.burst;
    vector<int> timeline;
    queue<int> q;
    vector<bool> inQueue(n, false);

    while (completed < n) {
        // Add all processes that have arrived by current time
        for (int i = 0; i < n; ++i) {
            if (!inQueue[i] && p[i].arrival <= time && p[i].remaining > 0) {
                q.push(i);
                inQueue[i] = true;
            }
        }

        if (q.empty()) {
            timeline.push_back(-1);
            ++time;
            continue;
        }

        int idx = q.front(); q.pop();
        int execTime = min(quantum, p[idx].remaining);

        for (int i = 0; i < execTime; ++i) {
            timeline.push_back(p[idx].id);
            ++time;
            --p[idx].remaining;

            // During each second, add newly arrived processes
            for (int j = 0; j < n; ++j) {
                if (!inQueue[j] && p[j].arrival <= time && p[j].remaining > 0) {
                    q.push(j);
                    inQueue[j] = true;
                }
            }
        }

        if (p[idx].remaining > 0) {
            q.push(idx);  // Put it at the end of the queue
        } else {
            ++completed;
        }
    }

    printTimeline(timeline);
}

int main() {
    int n, algo;
    cout << "Enter number of processes: ";
    cin >> n;
    vector<Process> processes(n);

    cout << "Enter Arrival Time, Burst Time, Priority (lower = higher priority):\n";
    for (int i = 0; i < n; ++i) {
        processes[i].id = i + 1;
        cout << "Process P" << i+1 << ": ";
        cin >> processes[i].arrival >> processes[i].burst >> processes[i].priority;
    }

    cout << "\nChoose Scheduling Algorithm:\n";
    cout << "1. FCFS\n2. SJF (Non-Preemptive)\n3. SJF (Preemptive)\n";
    cout << "4. Priority (Non-Preemptive)\n5. Priority (Preemptive)\n6. Round Robin\n";
    cin >> algo;

    switch (algo) {
        case 1: FCFS(processes); break;
        case 2: SJF_NonPreemptive(processes); break;
        case 3: SJF_Preemptive(processes); break;
        case 4: Priority_NonPreemptive(processes); break;
        case 5: Priority_Preemptive(processes); break;
        case 6: {
            int q;
            cout << "Enter time quantum: ";
            cin >> q;
            RoundRobin(processes, q);
            break;
        }
        default: cout << "Invalid option!\n";
    }
    return 0;
}
