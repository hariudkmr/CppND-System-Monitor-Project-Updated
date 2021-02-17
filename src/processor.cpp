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
  float result;
  long cputotal = LinuxParser::Jiffies();
  long idletotal = LinuxParser::IdleJiffies();

  float diffIdle = idletotal - oldidletime;
  float diffTotal = cputotal - oldcputotal;
  result = (diffTotal - diffIdle) / diffTotal;
  oldidletime = idletotal;
  oldcputotal = cputotal;
  return result;
}
