all: compileM compileS compileC compileManagement link run clean

compileM:
	@echo "Compiling main.cpp..."
	@g++ -c main.cpp -o main.o
compileS: 
	@echo "Compiling Student.cpp..."
	@g++ -c Student.cpp -o Student.o
compileC: 
	@echo "Compiling Course.cpp..."
	@g++ -c Course.cpp -o Course.o
compileManagement: 
	@echo "Compiling SchoolManagementSystem.cpp.."
	@g++ -c SchoolManagementSystem.cpp -o SchoolManagementSystem.o
link: # link object files and create a program
	@echo "Linking object files..."
	@g++ main.o Student.o Course.o SchoolManagementSystem.o -o program
run: 
	@echo "Running the program..."
	@./program
clean: # clean object files
	@echo "Cleaning object files..."
	@rm -f main.o Student.o Course.o SchoolManagementSystem.o