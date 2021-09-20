/* File: process.cpp
 * Author: Michael Huelsman
 * Purpose:
 *  A class definition for dealing with a simulated process.
*/

#include <cstdlib>
#include "synth_process.hpp"

int SynthProcess::nextID = 1;

SynthProcess::SynthProcess(){
  exec_time = 0;
  projected_time = 0;
  pid = -1;
  cycles_used = 0;
  priority = -1;
}

SynthProcess::SynthProcess(int exec_time, int priority){
  this->exec_time = exec_time;
  this->priority = priority;
  projected_time = exec_time+((rand()%10)-5);
  if(projected_time <= 0)projected_time = exec_time;
  pid = nextID++;
  cycles_used = 0;
}

SynthProcess::SynthProcess(const SynthProcess &copy){
  exec_time = copy.exec_time;
  priority = copy.priority;
  projected_time = copy.projected_time;
  pid = copy.pid;
  cycles_used = copy.cycles_used;
}

SynthProcess &SynthProcess::operator=(const SynthProcess &copy){
  exec_time = copy.exec_time;
  priority = copy.priority;
  projected_time = copy.projected_time;
  pid = copy.pid;
  cycles_used = copy.cycles_used;
  return *this;
}

int SynthProcess::get_pid(){
  return pid;
}

int SynthProcess::get_length(){
  if((projected_time - cycles_used) <= 0)return 1+(rand()%5);
  return (projected_time - cycles_used);
}

int SynthProcess::get_exec(){
  return exec_time;
}

bool SynthProcess::is_done(){
  return (cycles_used >= exec_time);
}

int SynthProcess::get_priority(){
  return priority;
}

ProcessState SynthProcess::status(){
  return READY;
}

void SynthProcess::run_burst(){
  cycles_used += 1;
}
