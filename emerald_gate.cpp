/* File: emerald_gate.cpp
 * Author: Michael Huelsman
 * Purpose:
 *  A class definition for the main information controller for a snythetic OS
 *  system.
*/

#include "emerald_gate.hpp"

EmeraldGate *EmeraldGate::instance = 0;

EmeraldGate *EmeraldGate::get_instance(){
  if(instance == 0){
    instance = new EmeraldGate();
  }
  return instance;
}

void EmeraldGate::destroy(){
  if(instance != 0)delete instance;
  instance = 0;
}

bool EmeraldGate::synth_process_exists(int pid){
  return (p_table.count(pid) == 1);
}

SynthProcess EmeraldGate::get_synth_process_data(int pid){
  return p_table[pid];
}

int EmeraldGate::num_procs(){
  return p_table.size();
}

void EmeraldGate::set_scheduler(Scheduler *schedule){
  scheduler = schedule;
}

void EmeraldGate::step(TEST::TestSeries &test_set){
  if(scheduler == 0 || completed)return;
  TEST::ActionType action = test_set.next_action();
  SynthProcess temp;
  ProcSummary summary;
  switch(action){
    case TEST::none:
      run_synth_process_cycle(scheduler->apply_burst());
      break;
    case TEST::done:
      while(num_procs() > 0){
        run_synth_process_cycle(scheduler->apply_burst());
      }
      completed = true;
      break;
    case TEST::interrupt:
      temp = test_set.next_interrupt();
      summary = ProcSummary(&temp, cycle_count);
      p_table[temp.get_pid()] = temp;
      summaries[temp.get_pid()] = summary;
      scheduler->add_synth_process(temp.get_pid());
      pids.push_back(temp.get_pid());
      break;
    case TEST::add:
      temp = test_set.next_synth_process();
      summary = ProcSummary(&temp, cycle_count);
      p_table[temp.get_pid()] = temp;
      summaries[temp.get_pid()] = summary;
      scheduler->add_synth_process(temp.get_pid());
      pids.push_back(temp.get_pid());
      break;
  }
}

bool EmeraldGate::is_done(){
  return completed;
}

void EmeraldGate::generate_summary(ostream &out){
  for(int i = 0;i < pids.size();i++){
    summaries[pids[i]].write_summary(out);
  }
  out << "Total Cycles: " << cycle_count << endl;
  out << "Idle Cycles: " << idle_count << endl;
}

void EmeraldGate::generate_csv_summary(ostream &out){
  out << "PID,Priority,Start,End,Ideal,Idle" << endl;
  for(int i = 0;i < pids.size();i++){
    summaries[pids[i]].write_csv_summary(out);
  }
}

void EmeraldGate::run_synth_process_cycle(int pid){
  cycle_count += 1;
  if(pid != 0 && synth_process_exists(pid)){
    ProcessState current_state = p_table[pid].status();
    if(current_state == READY){
      p_table[pid].run_burst();
      if(p_table[pid].is_done()){
        summaries[pid].final_update(cycle_count);
        p_table.erase(pid);
      }
      return;
    }
    else if(current_state == WAITING){
      summaries[pid].waiting();
    }
  }
  idle_count += 1;
}

EmeraldGate::EmeraldGate(){
  p_table = map<int,SynthProcess>();
  pids = vector<int>();
  summaries = map<int,ProcSummary>();
  scheduler = 0;
  idle_count = 0;
  completed = false;
  cycle_count = 0;
}
