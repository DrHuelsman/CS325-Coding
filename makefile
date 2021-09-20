OFILES = synth_process.o test_series.o emerald_gate.o fifo.o proc_summary.o

all: $(OFILES)
	 g++ main.cpp $(OFILES) -o schedule

clean:
	rm *.o

synth_process.o: synth_process.hpp synth_process.cpp
	g++ -c synth_process.cpp

proc_summary.o: synth_process.hpp proc_summary.hpp proc_summary.cpp
	g++ -c proc_summary.cpp

test_series.o: test_series.hpp test_series.cpp
	g++ -c test_series.cpp

emerald_gate.o: emerald_gate.hpp emerald_gate.cpp synth_process.hpp scheduler.hpp proc_summary.hpp
	g++ -c emerald_gate.cpp

fifo.o: fifo.hpp fifo.cpp scheduler.hpp emerald_gate.hpp
	g++ -c fifo.cpp
