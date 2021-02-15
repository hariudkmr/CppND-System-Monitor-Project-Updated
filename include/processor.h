#ifndef PROCESSOR_H
#define PROCESSOR_H

class Processor {
 public:
  float Utilization();  // TODO: See src/processor.cpp

  // TODO: Declare any necessary private members
 private:
  int cpu_total;
  int no_cpus;
  float oldidletime{0};
  float oldcputotal{0};
};

#endif