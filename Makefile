.PHONY: test clean mutants coverage main analyze

cxx = g++
cxxflags = -fprofile-arcs -ftest-coverage
ldflags = -lgcov -ldeepstate

src = doubly_linked_list.cpp doubly_linked_list_test.cpp

target = main

main:	
	g++ $(cxxflags) $(src) -o main $(ldflags)

test:
	@echo "Running tests..."
	make clean
	rm -rf failures
	mkdir failures
	g++ doubly_linked_list.cpp doubly_linked_list_test.cpp -ldeepstate
	./a.out --fuzz  --timeout 10 --output_test_dir=failures -vv

mutants:
	@echo "Running mutation tests..."
	make clean
	rm -rf mutants
	mkdir mutants
	mutate doubly_linked_list.cpp --mutantDir mutants --cmd "g++ doubly_linked_list.cpp -c"
	make analyze

analyze:
	@echo "Analyzing mutation tests..."
	analyze_mutants doubly_linked_list.cpp --mutantDir mutants "g++ doubly_linked_list.cpp doubly_linked_list_test.cpp -ldeepstate && ./a.out --fuzz --timeout 1" --timeout 5

coverage:
	@echo "Running coverage tests..."
	make clean
	rm -rf coverage
	mkdir coverage
	g++ -O1 -fprofile-arcs -ftest-coverage doubly_linked_list_test.cpp doubly_linked_list.cpp -ldeepstate -lgcov
	./a.out --fuzz --timeout 10 --output_test_dir=coverage -vv
	lcov --capture --directory . --output-file coverage.info
	lcov --remove coverage.info '/usr/include/*' '/usr/local/include/*'  -o coverage.info
	

clean:
	rm -rf a.out *.gcda *.gcno *.info *.backup.* *.o