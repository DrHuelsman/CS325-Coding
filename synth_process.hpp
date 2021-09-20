/* File: process.hpp
 * Author: Michael Huelsman
 * Purpose:
 *  A class declaration for dealing with a simulated process.
*/

#ifndef PROCESS_HPP
#define PROCESS_HPP

enum ProcessState{
  WAITING,
  READY,
};

class SynthProcess{
public:
  // Constructors and assignment operator.
  SynthProcess();
  SynthProcess(int exec_time, int priority);
  SynthProcess(const SynthProcess &copy);
  SynthProcess &operator=(const SynthProcess &copy);

  //Queries
  int get_pid(); //Returns the PID of the process.
  int get_length(); //Returns the projected time to completion of the process.
  int get_exec(); //Returns the exec time of the process;
  bool is_done(); //Returns true if the process is completed.
  int get_priority(); //Returns the priority of the process.
  ProcessState status(); //Returns the process status.

  //Action
  void run_burst(); //Runs the process for a CPU burst.
protected:
private:
  static int nextID;
  int priority;
  int pid;
  int exec_time;
  int projected_time;
  int cycles_used;
};

#endif
