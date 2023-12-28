all: clean compile run

compile: binfilehw.c serialization.c serialization.h
	@echo "-------------------------------------------"
	@echo "Compiling..."
	@gcc -o test binfilehw.c serialization.c

run:
	@echo "-------------------------------------------"
	@echo "Running the tests...."
	@echo "======================================================================="
	@./test
	@echo "======================================================================="
	@echo "Completed tests...."

clean:
	@echo "-------------------------------------------"
	@echo "Cleaning..."
	@rm -f *.o
	@rm -f test