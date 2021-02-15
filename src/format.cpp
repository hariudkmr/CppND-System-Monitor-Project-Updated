#include "format.h"

#include <string>

using std::string;

#define SECONDS_IN_MINUTE 60
#define SECONDS_IN_HOUR 3600

// TODO: Complete this helper function
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

  return std::to_string(phours) + ":" + std::to_string(pminutes) + ":" +
         std::to_string(pseconds);
}