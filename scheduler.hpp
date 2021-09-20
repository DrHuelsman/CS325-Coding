/*File: scheduler.hpp
 *Author: Michael Huelsman
 *Purpose:
 *  A pure virtual class for a cpu scheduler.
*/

#ifndef SCHEDULER_HPP
#define SCHEDULER_HPP

class Scheduler{
public:
  // Precond:
  //  None.
  // Postcond:
  //  Returns the next process to run a burst on.
  virtual int apply_burst() = 0;

  // Precond:
  //  pid is the process ID of a process in the current process list of
  //    the EmeraldGate.
  virtual void add_synth_process(int pid) = 0;
protected:
private:
};

#endif
