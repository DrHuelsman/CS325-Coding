/*File: test_series.hpp
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

#ifndef TEST_SERIES_HPP
#define TEST_SERIES_HPP

#include "synth_process.hpp"
#include <string>
#include <queue>
using namespace std;

namespace TEST{
  enum ActionType{
    done,
    none,
    add,
    interrupt
  };

  class TestSeries{
  public:
    //Constructors and operators.
    TestSeries(string filename);
    TestSeries(const TestSeries &copy);
    TestSeries &operator=(const TestSeries &copy);

    //Queries
    ActionType next_action(); //Returns the next action in the queue.
    SynthProcess next_synth_process(); //Returns the next process in the queue.
    SynthProcess next_interrupt(); //Returns the next interrupt in the queue.
  protected:
  private:
    bool waiting;
    int waitTimer;
    queue<ActionType> actions;
    queue<int> waitTimers;
    queue<SynthProcess> processes;
    queue<SynthProcess> interrupts;
  };
}

#endif
