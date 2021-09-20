/*File: test_series.cpp
 *Author: Michael Huelsman
 *Purpose:
 * A class for handling a series of test data and sending sequential information
 * to the EmeraldGate data manager.
 * NOTES:
 * In the file:
 *  1 <int> means wait for <int> cycles before putting anything new in the
 *    table.
 *  2 <int1> <int2> means add a process taking <int1> time with <int2> priority.
 *  3 <int> means add an interrupt taking <int> time.
*/

#include "test_series.hpp"
#include <fstream>
using namespace TEST;


TestSeries::TestSeries(string filename){
  int type, temp, temp2;
  actions = queue<ActionType>();
  waitTimers = queue<int>();
  processes = queue<SynthProcess>();
  interrupts = queue<SynthProcess>();
  ifstream fin(filename);
  SynthProcess proc;
  if(fin.is_open()){
    while(fin >> type){
      if(type == 0)break;
      else if(type == 1){
        actions.push(none);
        fin >> temp;
        waitTimers.push(temp);
      }
      else if(type == 2){
        actions.push(add);
        fin >> temp;
        fin >> temp2;
        proc = SynthProcess(temp,temp2);
        processes.push(proc);
      }
      else if(type == 3){
        actions.push(interrupt);
        fin >> temp;
        proc = SynthProcess(temp,0);
        interrupts.push(proc);
      }
    }
  }
  fin.close();
  actions.push(done);
  waiting = false;
  waitTimer = 0;
}

TestSeries::TestSeries(const TestSeries &copy){
  waiting = copy.waiting;
  waitTimer = copy.waitTimer;
  actions = copy.actions;
  waitTimers = copy.waitTimers;
  processes = copy.processes;
  interrupts = copy.interrupts;
}

TestSeries &TestSeries::operator=(const TestSeries &copy){
  waiting = copy.waiting;
  waitTimer = copy.waitTimer;
  actions = copy.actions;
  waitTimers = copy.waitTimers;
  processes = copy.processes;
  interrupts = copy.interrupts;
  return *this;
}

ActionType TestSeries::next_action(){
  if(!waiting){
    ActionType result = actions.front();
    actions.pop();
    if(result == none){
      waiting = true;
      waitTimer = waitTimers.front();
      waitTimers.pop();
    }
    return result;
  }
  else{
    waitTimer -= 1;
    if(waitTimer <= 0){
      waiting = false;
    }
  }
  return none;
}

SynthProcess TestSeries::next_synth_process(){
  SynthProcess temp = processes.front();
  processes.pop();
  return temp;
}

SynthProcess TestSeries::next_interrupt(){
  SynthProcess temp = interrupts.front();
  interrupts.pop();
  return temp;
}
