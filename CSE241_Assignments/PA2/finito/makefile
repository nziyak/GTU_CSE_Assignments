all: compileV compileM compileMain link run clean

compileV: # compile SparseVector.cpp and create its object file
	@echo "Compiling SparseVector.cpp..."
	@g++ -c SparseVector.cpp -o SparseVector.o
compileM: # compile SparseVector.cpp and create its object file
	@echo "Compiling SparseMatrix.cpp..."
	@g++ -c SparseMatrix.cpp -o SparseMatrix.o
compileMain: # compile PA2_test.cpp and create its object file
	@echo "Compiling PA2_test.cpp..."
	@g++ -c PA2_test.cpp -o PA2_test.o
link: # link object files and create a program
	@echo "Linking object files..."
	@g++ SparseVector.o SparseMatrix.o PA2_test.o -o program
run: 
	@echo "Running the program..."
	@./program
clean: # clean object files
	@echo "Cleaning object files..."
	@rm -f SparseVector.o SparseMatrix.o PA2_test.o