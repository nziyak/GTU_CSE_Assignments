#compiler
CXX = g++

#compiler flags
CXXFLAGS = -std=c++11

#headers
HEADERS = Constants.h Field.h Entry.h Command.h Table.h

#source fie
SOURCES = main.cpp Table.cpp

# Nesne dosyaları
OBJECTS = main.o Table.o

# Çıktı dosyasının adı
EXEC = program

# Varsayılan hedef
all: $(EXEC)

#create object files
%.o: %.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) -c $< -o $@

#create executable by linking object files
$(EXEC): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $(EXEC) $(OBJECTS)

#clean target
clean:
	rm -f $(OBJECTS) $(EXEC)

