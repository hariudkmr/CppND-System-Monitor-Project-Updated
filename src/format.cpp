#include "format.h"

#include <string>

using std::string;

#define SECONDS_IN_MINUTE 60
#define SECONDS_IN_HOUR 3600

// TODO: Complete this helper function
string AppendZero(const long number) {
  if (number < 10)
    return "0" + std::to_string(number);
  else
    return std::to_string(number);
}

// INPUT: Long int measuring seconds
// OUTPUT: HH:MM:SS
// REMOVE: [[maybe_unused]] once you define the function
string Format::ElapsedTime(long seconds) {
  int phours{0};
  int pminutes{0};
  int pseconds{0};

  phours = seconds / SECONDS_IN_HOUR;
  pminutes = (seconds % SECONDS_IN_HOUR) / SECONDS_IN_MINUTE;
  pseconds = seconds % SECONDS_IN_MINUTE;

  return AppendZero(phours) + ":" + AppendZero(pminutes) + ":" +
         AppendZero(pseconds);
}