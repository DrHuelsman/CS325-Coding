/* File: proc_summary.hpp
 * Author: Michael Huelsman
 * Purpose:
 *  A class definition for holding information about process run history.
*/

#include "proc_summary.hpp"
using namespace std;

ProcSummary::ProcSummary(){
  pid = -1;
  priority = -1;
  start_time = -1;
  end_time = -1;
  idle_time = -1;
  min_time = -1;
  wait_cycles = -1;
}

ProcSummary::ProcSummary(SynthProcess *proc, int cycle){
  pid = proc->get_pid();
  priority = proc->get_priority();
  start_time = cycle;
  end_time = -1;
  idle_time = -1;
  min_time = proc->get_exec();
  wait_cycles = 0;
}

ProcSummary::ProcSummary(const ProcSummary &copy){
  pid = copy.pid;
  priority = copy.priority;
  start_time = copy.start_time;
  end_time = copy.end_time;
  idle_time = copy.idle_time;
  min_time = copy.min_time;
  wait_cycles = copy.wait_cycles;
}

ProcSummary &ProcSummary::operator=(const ProcSummary &copy){
  pid = copy.pid;
  priority = copy.priority;
  start_time = copy.start_time;
  end_time = copy.end_time;
  idle_time = copy.idle_time;
  min_time = copy.min_time;
  wait_cycles = copy.wait_cycles;
  return *this;
}

void ProcSummary::waiting(){
  wait_cycles += 1;
}

void ProcSummary::final_update(int cycle){
  end_time = cycle;
  idle_time = (end_time-start_time)-min_time;
}

void ProcSummary::write_summary(ostream &out){
  out << "===============" << endl;
  out << "PID:" << pid << endl;
  out << "Priority:" << priority << endl;
  out << "---------------" << endl;
  out << "Start:" << start_time << endl;
  out << "Completed:" << end_time << endl;
  out << "Wall Cycles:" << end_time-start_time << endl;
  out << "CPU Cylces:" << min_time << endl;
  out << "Idle Cycles:" << idle_time << endl;
  out << "===============" <<endl;
}

void ProcSummary::write_csv_summary(ostream &out){
  out << pid << "," << priority << ",";
  out << start_time << "," << end_time << ",";
  out << min_time << "," << idle_time <<endl;
}
