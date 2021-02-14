#include "processor.h"

#include <iostream>
#include <sstream>
#include <string>

#include "linux_parser.h"

using namespace std;
using namespace LinuxParser;

/*

PrevIdle = previdle + previowait
Idle = idle + iowait

PrevNonIdle = prevuser + prevnice + prevsystem + previrq + prevsoftirq +
prevsteal NonIdle = user + nice + system + irq + softirq + steal

PrevTotal = PrevIdle + PrevNonIdle
Total = Idle + NonIdle

# differentiate: actual value minus the previous one
totald = Total - PrevTotal
idled = Idle - PrevIdle

CPU_Percentage = (totald - idled)/totald

*/

// TODO: Return the aggregate CPU utilization
float Processor::Utilization() {
  string line;
  float result;
  float cputotal, idletotal;
  string cpuname;
  float user, nice, system, idle, iowait, irq, softirq, steal, guest,
      guest_nice;
  std::ifstream filestream(kProcDirectory + kStatFilename);
  if (filestream.is_open()) {
    std::getline(filestream, line);
    std::istringstream linestream(line);
    linestream >> cpuname;
    linestream >> user;
    linestream >> nice;
    linestream >> system;
    linestream >> idle;
    linestream >> iowait;
    linestream >> irq;
    linestream >> softirq;
    linestream >> steal;
    linestream >> guest;
    linestream >> guest_nice;

    cputotal = user + nice + system + idle + iowait + irq + softirq + steal +
               guest + guest_nice;

    idletotal = idle + iowait;
    result = (cputotal - idletotal) / cputotal;
  }
  return result;
}
