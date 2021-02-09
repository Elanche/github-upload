#include <unistd.h>
#include<time.h>
#include<iostream>
#include<fstream>
#include <cctype>
#include <sstream>
#include <string>
#include <vector>
#include "linux_parser.h"
#include "process.h"
#include "system.h"

using std::string;
using std::to_string;
using std::vector;
using namespace LinuxParser;

Process::Process(int p):pid{p}{}

// TODO: Return this process's ID
int Process::Pid() { return pid; }

// TODO: Return this process's CPU utilization
float Process::CpuUtilization() const{ 
    std::ifstream filestream(kProcDirectory+std::to_string(pid)+kStatFilename);
    string line;
    if(filestream.is_open()){
        while(getline(filestream, line)){
            std::stringstream ss(line);
            vector<string> s;
            while(ss.good()){
                string str;
                getline(ss, str, ' ');
                s.push_back(str);
            }
            float tot_time=std::stoi(s[13], nullptr, 10)+std::stoi(s[14], nullptr, 10)+std::stoi(s[15], nullptr, 10)+std::stoi(s[16], nullptr, 10);
            //std::cout<<std::endl;
            //std::cout<<tot_time<<std::endl;
            float seconds=System::uptime-((float)std::stol(s[21], nullptr, 10)/(float)CLOCKS_PER_SEC);
            //std::cout<<seconds<<std::endl;
            float cpu_usage=(tot_time/seconds);
            //std::cout<<cpu_usage<<std::endl;
            int t;
            //std::cout<<cpu_usage<<std::endl;
            //std::cin>>t;
            return cpu_usage;
        }
    }
    return 0;
}

// TODO: Return the command that generated this process
string Process::Command() { 
    std::ifstream filestream(kProcDirectory+std::to_string(pid)+kCmdlineFilename);
    string line;
    string res="";
    if(filestream.is_open()){
        while(getline(filestream, line)){
            res+=line;
            //std::cout<<line<<"\n";
        }
    }
    return res;
}

// TODO: Return this process's memory utilization
string Process::Ram() { 
    std::ifstream stream(kProcDirectory + std::to_string(pid)+ kStatusFilename);
    if(stream.is_open()){
        string line;
        while(getline(stream, line)){
            if(line.substr(0, 6)=="VmSize"){
                std::stringstream ss(line);
                string temp;
                string kb;
                ss>>temp>>kb;
                int mb=stoi(kb)/1000;
                return to_string(mb);
            }
        }
    }
    return string();
}

// TODO: Return the user (name) that generated this process
string Process::User() { 
    string line;
    int uid;
    std::ifstream tream(kProcDirectory + std::to_string(pid)+kStatusFilename);
    if(tream.is_open()) {
        while(getline(tream, line)){
            if(line.substr(0, 3)=="Uid"){
                std::stringstream ss(line);
                string temp;
                ss>>temp>>uid;
            }
        }
    }
    std::ifstream ream(kPasswordPath);
    if(ream.is_open()) {
        while(std::getline(ream, line)){
            std::stringstream ss(line);
            vector<string> s;
            while(ss.good()){
                string str;
                getline(ss, str, ':');
                s.push_back(str);
            }
            if(s.at(2)==std::to_string(uid)){
                return s.at(0);
            }
        }
    }
    return string();
}

// TODO: Return the age of this process (in seconds)
long int Process::UpTime() { 
    std::ifstream filestream(kProcDirectory+std::to_string(pid)+kStatFilename);
    if(filestream.is_open()){
        string line;
        getline(filestream, line);
        std::stringstream ss(line);
        vector<string> subs;
        while(ss.good()){
            string str;
            getline(ss, str, ' ');
            subs.push_back(str);
        }
        long int res=stol(subs[21]);
        return res;
    }
    return 0; 
}

// TODO: Overload the "less than" comparison operator for Process objects
// REMOVE: [[maybe_unused]] once you define the function
bool Process::operator<(Process const& a) const { 
    return this->CpuUtilization()>a.CpuUtilization();
}