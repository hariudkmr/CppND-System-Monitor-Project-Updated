#ifndef PROCESSOR_H
#define PROCESSOR_H

class Processor {
 public:
  float Utilization();  // TODO: See src/processor.cpp
  long oldidletime{0};
  long oldcputotal{0};

  // TODO: Declare any necessary private members
 private:
  int cpu_total;
  int no_cpus;
};

#endif