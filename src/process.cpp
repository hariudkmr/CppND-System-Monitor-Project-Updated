#include "process.h"

#include <unistd.h>

#include <cctype>
#include <sstream>
#include <string>
#include <vector>

#include "linux_parser.h"

using std::string;
using std::to_string;
using std::vector;
using namespace LinuxParser;

Process::Process(int pid) : pid_(pid) {
  findUserName();
  calculateCpuUtilization();
  calculateRamSize();
  calculateUpTime();
}

// TODO: Return this process's ID
int Process::Pid() { return pid_; }

// TODO: Return this process's CPU utilization
float Process::CpuUtilization() { return cpu_; }

// TODO: Return the command that generated this process
string Process::Command() { return command_; }

// TODO: Return this process's memory utilization
string Process::Ram() { return ram_; }

// TODO: Return the user (name) that generated this process
string Process::User() { return user_; }

// TODO: Return the age of this process (in seconds)
long int Process::UpTime() { return uptime_; }

// TODO: Overload the "less than" comparison operator for Process objects
// REMOVE: [[maybe_unused]] once you define the function
bool Process::operator<(Process const& a [[maybe_unused]]) const {
  return true;
}

void Process::findUserName() { user_ = LinuxParser::User(Pid()); }

void Process::calculateCpuUtilization() {
  vector<string> pid_stat_parameters;
  long cpu_uptime = LinuxParser::UpTime();
  pid_stat_parameters = LinuxParser::CpuUtilization(Pid());
  float total_pid_time, active_pid_time;

  active_pid_time = stof(pid_stat_parameters.at(utime_)) +
                    stof(pid_stat_parameters.at(stime_)) +
                    stof(pid_stat_parameters.at(cutime_)) +
                    stof(pid_stat_parameters.at(cstime_));

  total_pid_time = cpu_uptime - stof(pid_stat_parameters.at(starttime_));
  cpu_ = (total_pid_time - active_pid_time) / active_pid_time;
}
void Process::calculateRamSize() { ram_ = LinuxParser::Ram(Pid()); }
void Process::calculateUpTime() { uptime_ = LinuxParser::UpTime(Pid()); }
