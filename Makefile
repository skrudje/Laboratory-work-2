CXX = g++
CXXFLAGS = -std=c++17 -I. -O2

SOURCES = main.cpp \
          storage/storage.cpp \
          structures/array.cpp \
          structures/stack.cpp \
          structures/set.cpp \
          structures/lfu_cache.cpp \
          structures/hash_table_double.cpp \
          structures/hash_table_kuku.cpp \
          utils/set_cmd.cpp \
          utils/menu.cpp \
          tasks/task1_logic.cpp \
          tasks/task2_set.cpp \
          tasks/task3_partition.cpp \
          tasks/task4_subarray.cpp \
          tasks/task5_huffman.cpp \
          tasks/task61_double_kuku.cpp \
          tasks/task62_restructure.cpp \
          tasks/task7_lfu.cpp

OBJECTS = $(SOURCES:.cpp=.o)

dbms: $(OBJECTS)
	$(CXX) $(OBJECTS) -o dbms

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJECTS) dbms

.PHONY: clean