/*File: fifo.cpp
 *Author: Michael Huelsman
 *Purpose:
 *  A first in first out cpu scheduler.
*/

#include "fifo.hpp"
#include "emerald_gate.hpp"

Fifo::Fifo(){
  interrupts = queue<int>();
  processes = queue<int>();
}

int Fifo::apply_burst(){
  if(!interrupts.empty()){
    while(!interrupts.empty() && is_done(interrupts.front())){
      interrupts.pop();
    }
    if(!interrupts.empty()){
      return interrupts.front();
    }
  }
  else if(!processes.empty()){
    while(!processes.empty() && is_done(processes.front())){
      processes.pop();
    }
    if(!processes.empty()){
      return processes.front();
    }
  }
  return 0;
}

void Fifo::add_synth_process(int pid){
  if(is_interrupt(pid)){
    interrupts.push(pid);
  }
  else{
    processes.push(pid);
  }
}

bool Fifo::is_done(int pid){
  return !EmeraldGate::get_instance()->synth_process_exists(pid);
}

bool Fifo::is_interrupt(int pid){
  return (EmeraldGate::get_instance()->get_synth_process_data(pid).get_priority() == 0);
}
