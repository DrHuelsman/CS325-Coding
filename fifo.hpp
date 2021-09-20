/*File: fifo.hpp
 *Author: Michael Huelsman
 *Purpose:
 *  A first in first out cpu scheduler.
*/

#include "scheduler.hpp"
#include <queue>
using namespace std;

#ifndef FIFO_HPP
#define FIFO_HPP

class Fifo : public Scheduler {
public:
  Fifo();
  int apply_burst();
  void add_synth_process(int pid);
protected:
  bool is_done(int pid);
  bool is_interrupt(int pid);
private:
  queue<int> interrupts;
  queue<int> processes;
};

#endif
