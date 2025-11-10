CXX = g++
CXXFLAGS = -std=c++17 -I. -O2

SOURCES = main.cpp \
          storage/storage.cpp \
          structures/array.cpp \
          structures/stack.cpp \
          structures/set.cpp \
          structures/lfu_cache.cpp \
          utils/set_cmd.cpp \
          utils/menu.cpp \
          tasks/task1_logic.cpp \
          tasks/task2_set_interactive.cpp \
          tasks/task3_partition.cpp \
          tasks/task4_subarray.cpp \
          tasks/task5_huffman.cpp \
          tasks/task6_hash_test.cpp \
          tasks/task7_lfu_interactive.cpp

OBJECTS = $(SOURCES:.cpp=.o)

dbms: $(OBJECTS)
	$(CXX) $(OBJECTS) -o dbms

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJECTS) dbms

.PHONY: clean