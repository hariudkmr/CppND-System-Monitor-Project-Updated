#ifndef PROCESS_H
#define PROCESS_H

#include <string>
/*
Basic class for Process representation
It contains relevant attributes as shown below
*/
class Process {
 public:
  int Pid();                               // TODO: See src/process.cpp
  std::string User();                      // TODO: See src/process.cpp
  std::string Command();                   // TODO: See src/process.cpp
  float CpuUtilization();                  // TODO: See src/process.cpp
  std::string Ram();                       // TODO: See src/process.cpp
  long int UpTime();                       // TODO: See src/process.cpp
  bool operator<(Process const& a) const;  // TODO: See src/process.cpp

  Process(int pid);
  void findUserName();
  void calculateCpuUtilization();
  void calculateRamSize();
  void calculateUpTime();

  // TODO: Declare any necessary private members
 private:
  int pid_{0};
  std::string user_{};
  float cpu_{0.0};
  std::string ram_{};
  long int uptime_{0};
  std::string command_{};
  enum ePidStat { utime_ = 14, stime_, cutime_, cstime_, starttime_ = 22 };
};

#endif