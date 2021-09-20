/*File: main.cpp
 *Author: Michael Huelsman
 *Purpose:
 *  Run a test bed for the CPU scheduler project.
 */

#include "emerald_gate.hpp"
#include "test_series.hpp"
#include "fifo.hpp"
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <time.h>
using namespace std;

using namespace TEST;

int main(int argc, char **argv){
  srand(time(NULL));
  if(argc != 2){
    cerr << "Error: Incorrect number of arguments." <<endl;
    return 1;
  }
  Fifo scheduler = Fifo();
  EmeraldGate::get_instance()->set_scheduler(&scheduler);
  TestSeries tests = TestSeries(argv[1]);
  while(!EmeraldGate::get_instance()->is_done()){
    EmeraldGate::get_instance()->step(tests);
  }
  EmeraldGate::get_instance()->generate_summary(cout);
  ofstream fout;
  fout.open("run_results.csv");
  EmeraldGate::get_instance()->generate_csv_summary(fout);
  EmeraldGate::destroy();
  return 0;
}
