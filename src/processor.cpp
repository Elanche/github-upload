#include<fstream>
#include<sstream>
#include "processor.h"
#include "linux_parser.h"
using namespace LinuxParser;

// TODO: Return the aggregate CPU utilization
float Processor::Utilization() { 
    std::ifstream in_file(kProcDirectory+kStatFilename);
    if(in_file.is_open()){
        std::string line;
        getline(in_file, line);
        std::string dummy;
        std::stringstream ss(line);
        ss>>dummy;
        std::vector<int> times(10);
        int tot=0;
        for(int i=0;i<10;i++){
            ss>>times[i];
            tot+=times[i];
        }
        float idle=(float)times[3]/(float)tot;
        return 1.0-idle;
    }
    return 0.0;
}