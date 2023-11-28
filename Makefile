 1 CXX = g++-11 -std=c++20                                                                                                            2 CXXFLAGS = -Wall -g -MMD  # use -MMD to generate dependencies
  3 SOURCES = $(wildcard *.cc)   # list of all .cc files in the current directory
  4 OBJECTS = ${SOURCES:.cc=.o}  # .o files depend upon .cc files with same names
  5 DEPENDS = ${OBJECTS:.o=.d}   # .d file is list of dependencies for corresponding .cc file
  6 EXEC=a4q1
  7
  8 # First target in the makefile is the default target.
  9 $(EXEC): $(OBJECTS)
 10   $(CXX) $(CXXFLAGS) $(OBJECTS) -o $(EXEC)  $(LIBFLAGS)
 11
 12 %.o: %.cc
 13   $(CXX) -c -o $@ $< $(CXXFLAGS) $(LIBFLAGS)
 14
 15 -include ${DEPENDS}
 16
 17 .PHONY: clean tests
 18 clean:
 19   rm  -f $(OBJECTS) $(DEPENDS) $(EXEC)