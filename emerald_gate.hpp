/* File: emerald_gate.hpp
 * Author: Michael Huelsman
 * Purpose:
 *  A class declaration for the main information controller for a snythetic OS
 *  system.
*/

#include "synth_process.hpp"
#include "proc_summary.hpp"
#include "scheduler.hpp"
#include "test_series.hpp"
#include <map>
#include <iostream>
#include <vector>
using namespace std;

#ifndef EMERALD_GATE_HPP
#define EMERALD_GATE_HPP

class EmeraldGate{
public:
  //Singleton Access Methods
  static EmeraldGate *get_instance();
  static void destroy();

  //Queries
  bool synth_process_exists(int pid); //Returns true if the process exists.
  SynthProcess get_synth_process_data(int pid); //Returns the process's information.
  int num_procs(); //Returns the number of process in the process table.

  //Update
  void set_scheduler(Scheduler *schedule);
  void step(TEST::TestSeries &test_set);
  bool is_done();

  //Final Data Collection
  void generate_summary(ostream &out);
  void generate_csv_summary(ostream &out);
protected:
  void run_synth_process_cycle(int pid);
private:
  //Singleton Data
  static EmeraldGate *instance;
  //Constructors
  EmeraldGate();

  map<int,SynthProcess> p_table;
  map<int,ProcSummary> summaries;
  vector<int> pids;
  Scheduler *scheduler;
  int idle_count;
  bool completed;
  int cycle_count;
};

#endif
