//Simulation of FCFS time scheduling
#include<iostream>
#include<string>
#include<fstream>
#include<algorithm>
#include<vector>
#include<Windows.h> //add it if you use windows OS and want to change text color
using namespace std;

// structure for process
struct process
{
	int arrival_time;
	int burst_time;
	int Waiting_time;
	int Turn_around_time;
};

//Auxiliary function for reading file lines
 string getWord(string& line) {
	string word;
	if (line != "") {
		word = line.substr(0, (line.find(' ') != string::npos) ? line.find(' ') : line.size());
		line.replace(0, (line.find(' ') != string::npos) ? line.find(' ') + 1 : line.size(), "");
	}
	return  word;
}

//Function for reading file and analysis it to Provide processes
vector<process> readFromFile(string filename)
{
	vector<process> processes;
	process proc;
	string line;
	ifstream File(filename);
    
	if (!File) {
		cout << "Cannot open input file.\n";
	}
	else if (File) {
		while (File)
		{
			getline(File, line);
			if (line == "$") break;
			proc.arrival_time = stoi(getWord(line));
			proc.burst_time = stoi(getWord(line));
			processes.push_back(proc);
		}
			
		
	}
	File.close();

	//Sorting processes by arrival time (ASC)
	std::sort(processes.begin(), processes.end(),
		[](const process left, const process right)
		{
			return (left.arrival_time < right.arrival_time);
		}
	);

	return processes;
}

//Function to find the waiting time for all processes
void findWaitingTime(vector<process>& processes)
{
	//waiting time for first process is 0
	processes[0].Waiting_time = 0;

	//calculating each process waiting time
	for (int i = 1; i < processes.size(); i++)
		processes[i].Waiting_time =  (processes[i - 1].burst_time + processes[i - 1].Waiting_time - processes[i].arrival_time) > 0 ? processes[i - 1].burst_time + processes[i - 1].Waiting_time - processes[i].arrival_time : 0 ;
}

// Function to calculate turn around time for all process
void findTurnAroundTime(vector<process>& processes)
{
	// calculating each process turnaround time 
	for (int i = 0; i < processes.size() ; i++)
		processes[i].Turn_around_time =  processes[i].burst_time + processes[i].Waiting_time;
}

//Function to FCFS core operation
void core(vector<process>& processes)
{
	int total_wt = 0, total_tat = 0;

	//Finding processes waiting time 
	findWaitingTime(processes);

	//Finding  processes turn around time
	findTurnAroundTime(processes);

	//Display processes along with all details
	cout << "Processes  " << " Arrival time  " << " Burst time  "<< " Waiting time  " << " Turn around time\n";

	//Calculate total waiting time and total turnaround time
	for (int i = 0; i< processes.size() ; i++)
	{
		total_wt = total_wt + processes[i].Waiting_time;
		total_tat = total_tat + processes[i].Turn_around_time;
		cout << "   " << i + 1 << "\t\t" << processes[i].arrival_time << "\t\t" << processes[i].burst_time << "\t    "<< processes[i].Waiting_time << "\t\t       " << processes[i].Turn_around_time << endl;
	}

	cout << endl;
	cout << "Average waiting time     = "<< (float)total_wt / (float)processes.size()<<endl;
	cout << "Average turn around time = "<< (float)total_tat / (float)processes.size();
}

//Driver code
void main(int argc, char **argv) {
	//Configure text color 
   //Note: it's just working with windows OS if your OS isn't windows you shall remove this part
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO con_info;
	GetConsoleScreenBufferInfo(hConsole, &con_info);
	const int saved_colors = con_info.wAttributes;
	SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_INTENSITY);

	 //Get target file from the first argument that passed  to the terminal and read it and then starts core operation
	if (argc >= 2) {
		vector<process> processes = readFromFile(argv[1]);
		if (!processes.empty())
			core(processes);
	}

	//Return to default color
	SetConsoleTextAttribute(hConsole, saved_colors);
}

