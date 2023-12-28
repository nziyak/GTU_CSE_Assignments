all: clean compile run

compile: 8-puzzle.c
	@echo "-------------------------------------------"
	@ulimit -s 16277216
	@echo "your stack size has been changed to 16 MB to avoid segmentation fault."
	@gcc -o test 8-puzzle.c

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