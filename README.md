# 🧠 CPU Scheduling Algorithms Simulator (C++)

This project is a command-line simulation of **six classic CPU scheduling algorithms**, built using C++. The program accepts process information (arrival and burst time) and prints a second-by-second execution timeline for the selected algorithm.

## 📋 Supported Algorithms

- **FCFS** (First Come First Serve)
- **SJF** (Shortest Job First - Non-Preemptive)
- **Priority Scheduling** (Non-Preemptive)
- **Round Robin**
- **Preemptive SJF** (Shortest Remaining Time First)
- **Preemptive Priority Scheduling**

---

## 🚀 How It Works

1. **Input**:
    - Number of processes
    - For each process: Arrival Time, Burst Time (and Priority if applicable)
    - Time Quantum (if Round Robin is selected)

2. **Output**:
    - A timeline that shows which process runs during each second.
    - Example output:
      ```
      0 ~ 1  P0
      1 ~ 2  P1
      2 ~ 3  P1
      ...
      ```

---
🧠 Educational Purpose
This simulator is designed to help students and learners:
Understand how scheduling algorithms work
Compare scheduling techniques
Visualize CPU behavior over time

🤝 Contributions
Feel free to fork and modify this project!

📬 Contact
Made with ❤️ for Operating Systems lovers.
If you have suggestions or feedback, feel free to reach out!
