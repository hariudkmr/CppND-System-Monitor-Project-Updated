#include "linux_parser.h"

#include <dirent.h>
#include <unistd.h>

#include <string>
#include <vector>

using std::stof;
using std::string;
using std::to_string;
using std::vector;

// DONE: An example of how to read data from the filesystem
string LinuxParser::OperatingSystem() {
  string line;
  string key;
  string value;
  std::ifstream filestream(kOSPath);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::replace(line.begin(), line.end(), ' ', '_');
      std::replace(line.begin(), line.end(), '=', ' ');
      std::replace(line.begin(), line.end(), '"', ' ');
      std::istringstream linestream(line);
      while (linestream >> key >> value) {
        if (key == "PRETTY_NAME") {
          std::replace(value.begin(), value.end(), '_', ' ');
          return value;
        }
      }
    }
  }
  return value;
}

// DONE: An example of how to read data from the filesystem
string LinuxParser::Kernel() {
  string os, version, kernel;
  string line;
  std::ifstream stream(kProcDirectory + kVersionFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    linestream >> os >> version >> kernel;
  }
  return kernel;
}

// BONUS: Update this to use std::filesystem
vector<int> LinuxParser::Pids() {
  vector<int> pids;
  DIR* directory = opendir(kProcDirectory.c_str());
  struct dirent* file;
  while ((file = readdir(directory)) != nullptr) {
    // Is this a directory?
    if (file->d_type == DT_DIR) {
      // Is every character of the name a digit?
      string filename(file->d_name);
      if (std::all_of(filename.begin(), filename.end(), isdigit)) {
        int pid = stoi(filename);
        pids.push_back(pid);
      }
    }
  }
  closedir(directory);
  return pids;
}

// TODO: Read and return the system memory utilization
float LinuxParser::MemoryUtilization() {
  string line;
  string name;
  float memoryinfo[5];

  std::ifstream stream(kProcDirectory + kMeminfoFilename);
  if (stream.is_open()) {
    for (int i = 0; i < MemoryTypes::kMemTypes_; i++) {
      std::getline(stream, line);
      std::istringstream linestream(line);
      linestream >> name >> memoryinfo[i];
    }
  }
  return ((memoryinfo[MemoryTypes::kMemTotal_] -
           memoryinfo[MemoryTypes::kMemFree_] -
           memoryinfo[MemoryTypes::kBuffers_] -
           memoryinfo[MemoryTypes::kCached_]) /
          memoryinfo[MemoryTypes::kMemTotal_]);
}

// TODO: Read and return the system uptime
long LinuxParser::UpTime() {
  string line;
  long result{0};
  std::ifstream filestream(kProcDirectory + kUptimeFilename);
  if (filestream.is_open()) {
    std::getline(filestream, line);
    std::istringstream linestream(line);
    linestream >> result;
  }
  return result;
}

// TODO: Read and return the number of jiffies for the system
long LinuxParser::Jiffies() {
  string line, cpuname;
  long tempjiffy{0}, result{0};
  std::ifstream filestream(kProcDirectory + kStatFilename);
  if (filestream.is_open()) {
    std::getline(filestream, line);
    std::istringstream linestream(line);
    linestream >> cpuname;  // pop first string
    while (linestream >> tempjiffy) {
      result += tempjiffy;
    }
  }
  return result;
}

// TODO: Read and return the number of active jiffies for a PID
// REMOVE: [[maybe_unused]] once you define the function
long LinuxParser::ActiveJiffies(int pid) {
  string line, cpuname;
  long result{0};
  long cpu_data[CPUStates::kCpuStates_]{0};
  std::ifstream filestream(kProcDirectory + "/" + std::to_string(pid) +
                           kStatFilename);
  if (filestream.is_open()) {
    std::getline(filestream, line);
    std::istringstream linestream(line);
    linestream >> cpuname;  // pop first string
    for (int i = 0; i < CPUStates::kCpuStates_; i++) {
      linestream >> cpu_data[i];
    }
  }
  result = cpu_data[CPUStates::kUser_] + cpu_data[CPUStates::kNice_] +
           cpu_data[CPUStates::kSystem_] + cpu_data[CPUStates::kIRQ_] +
           cpu_data[CPUStates::kSoftIRQ_] + cpu_data[CPUStates::kSteal_];
  return result;
}

// TODO: Read and return the number of active jiffies for the system
long LinuxParser::ActiveJiffies() {
  string line, cpuname;
  long result{0};
  long cpu_data[CPUStates::kCpuStates_]{0};
  std::ifstream filestream(kProcDirectory + kStatFilename);
  if (filestream.is_open()) {
    std::getline(filestream, line);
    std::istringstream linestream(line);
    linestream >> cpuname;  // pop first string
    for (int i = 0; i < CPUStates::kCpuStates_; i++) {
      linestream >> cpu_data[i];
    }
  }
  result = cpu_data[CPUStates::kUser_] + cpu_data[CPUStates::kNice_] +
           cpu_data[CPUStates::kSystem_] + cpu_data[CPUStates::kIRQ_] +
           cpu_data[CPUStates::kSoftIRQ_] + cpu_data[CPUStates::kSteal_];
  return result;
}

// TODO: Read and return the number of idle jiffies for the system
long LinuxParser::IdleJiffies() {
  string line, cpuname;
  long result{0};
  long cpu_data[CPUStates::kCpuStates_]{0};
  std::ifstream filestream(kProcDirectory + kStatFilename);
  if (filestream.is_open()) {
    std::getline(filestream, line);
    std::istringstream linestream(line);
    linestream >> cpuname;  // pop first string
    for (int i = 0; i < CPUStates::kCpuStates_; i++) {
      linestream >> cpu_data[i];
    }
  }
  result = cpu_data[CPUStates::kIdle_] + cpu_data[CPUStates::kIOwait_];
  return result;
}

// TODO: Read and return CPU utilization
vector<string> LinuxParser::CpuUtilization() {
  string line;
  string value;
  vector<string> result;
  std::ifstream filestream(kProcDirectory + kStatFilename);
  if (filestream.is_open()) {
    std::getline(filestream, line);
    std::istringstream linestream(line);

    while (linestream >> value) {
      result.push_back(value);
    }
  }
  return result;
}

// TODO: Read and return the total number of processes
int LinuxParser::TotalProcesses() {
  string process, line;
  int result;
  std::ifstream filestream(kProcDirectory + kStatFilename);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::istringstream linestream(line);
      while (linestream >> process >> result) {
        if (process == "processes") {
          return result;
        }
      }
    }
  }
  return result;
}

// TODO: Read and return the number of running processes
int LinuxParser::RunningProcesses() {
  string process, line;
  int result;
  std::ifstream filestream(kProcDirectory + kStatFilename);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::istringstream linestream(line);
      while (linestream >> process >> result) {
        if (process == "procs_running") {
          return result;
        }
      }
    }
  }
  return result;
}

// TODO: Read and return the command associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Command(int pid) {
  string result = "";
  std::ifstream filestream(kProcDirectory + "/" + std::to_string(pid) +
                           kCmdlineFilename);
  if (filestream.is_open()) {
    std::getline(filestream, result);
  }
  return result;
}

// TODO: Read and return the memory used by a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Ram(int pid) {
  string line;
  string name;
  string result = "";
  std::ifstream filestream(kProcDirectory + "/" + std::to_string(pid) +
                           kStatusFilename);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::replace(line.begin(), line.end(), ':', ' ');
      std::istringstream linestream(line);
      while (linestream >> name >> result) {
        if (name == "VmSize") {
          return result;
        }
      }
    }
  }
  return result;
}

// TODO: Read and return the user ID associated with a process
// REMOVE: [[maybe_unused]] once you define the function
std::string LinuxParser::Uid(int pid) {
  string line;
  string key;
  string result = "";
  std::ifstream filestream(kProcDirectory +  std::to_string(pid) +
                           kStatusFilename);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::istringstream linestream(line);
      while (linestream >> key >> result) {
        if (key == "Uid:") {
          return result;
        }
      }
    }
  }
  return result;
}

// Read and return the user associated with a process
string LinuxParser::User(int pid) {
  // Get the uid from pid status file
  string uid = Uid(pid);
  string line, key, result{};
  std::ifstream filestream(kPasswordPath);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::replace(line.begin(), line.end(), ':', ' ');
      std::replace(line.begin(), line.end(), 'x', ' ');
      std::istringstream linestream(line);
      while (linestream >> result >> key) {
        if (key == uid) {
          return result;
        }
      }
    }
  }
  return result;
}

vector<string> LinuxParser::CpuUtilization(int pid) {
  string line, key;
  vector<string> result{};
  std::ifstream filestream(kProcDirectory + "/" + std::to_string(pid) +
                           kStatFilename);
  if (filestream.is_open()) {
    std::getline(filestream, line);
    std::istringstream linestream(line);
    while (linestream >> key) {
      result.push_back(key);
    }
  }
  return result;
}

// TODO: Read and return the uptime of a process
// REMOVE: [[maybe_unused]] once you define the function
long LinuxParser::UpTime(int pid) {
  string line;
  long uptime{0};
  string result;
  vector<string> statstream{};
  std::ifstream filestream(kProcDirectory + "/" + std::to_string(pid) +
                           kStatFilename);
  if (filestream.is_open()) {
    std::getline(filestream, line);
    std::istringstream linestream(line);
    while (linestream >> line) {
      statstream.push_back(line);
    }
    uptime = stol(statstream.at(kstarttime_)) / sysconf(_SC_CLK_TCK);
  }
  return uptime;
}
