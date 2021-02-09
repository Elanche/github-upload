#include <unistd.h>
#include <dirent.h>
#include <cstddef>
#include <set>
#include <string>
#include <vector>
#include<iostream>

#include "process.h"
#include "processor.h"
#include "system.h"
#include "linux_parser.h"

using std::set;
using std::size_t;
using std::string;
using std::vector;
using namespace LinuxParser;

long int System::uptime;

// TODO: Return the system's CPU
Processor& System::Cpu() { return cpu_; }

// TODO: Return a container composed of the system's processes
vector<Process>& System::Processes() { 
    int n=LinuxParser::Pids().size();
    for(int i=0;i<n;i++){
        Process p(LinuxParser::Pids()[i]);
        processes_.push_back(p);
    }
    return processes_;
}

// TODO: Return the system's kernel identifier (string)
std::string System::Kernel() { 
    kernel=LinuxParser::Kernel();
    return kernel;
}

// TODO: Return the system's memory utilization
float System::MemoryUtilization() { 
    mem_util=LinuxParser::MemoryUtilization();
    return mem_util;
}

// TODO: Return the operating system name
std::string System::OperatingSystem() {
    os=LinuxParser::OperatingSystem();
    return os;
}

// TODO: Return the number of processes actively running on the system
int System::RunningProcesses() { 
    running_procs=LinuxParser::RunningProcesses();
    return running_procs;
}

// TODO: Return the total number of processes on the system
int System::TotalProcesses() { 
    total_procs=LinuxParser::TotalProcesses();
    return total_procs;
}

// TODO: Return the number of seconds since the system started running
long int System::UpTime() { 
    uptime=LinuxParser::UpTime();
    return uptime; 
}