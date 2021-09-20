/* File: proc_summary.hpp
 * Author: Michael Huelsman
 * Purpose:
 *  A class declaration for holding information about process run history.
*/

#include <iostream>
#include "synth_process.hpp"

#ifndef PROC_SUMMARY_HPP
#define PROC_SUMMARY_HPP

class ProcSummary{
public:
  ProcSummary();
  ProcSummary(SynthProcess *proc, int cycle);
  ProcSummary(const ProcSummary &copy);
  ProcSummary &operator=(const ProcSummary &copy);

  void waiting();
  void final_update(int cycle);
  void write_summary(std::ostream &out);
  void write_csv_summary(std::ostream &out);
protected:
private:
  int pid;
  int priority;
  int start_time;
  int end_time;
  int idle_time;
  int min_time;
  int wait_cycles;
};

#endif
