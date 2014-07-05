all:

clean:
	rm -f  *.gcda
	rm -f  *.gcno
	rm -f  *.gcov
	rm -f  Integer.log
	rm -f  RunInteger
	rm -f  RunInteger.out
	rm -f  RunInteger.tmp
	rm -f  TestInteger
	rm -f  TestInteger.out
	rm -rf html

config:
	doxygen -g

diff: RunInteger RunInteger.out
	RunInteger > RunInteger.tmp
	diff RunInteger.out RunInteger.tmp

doc: Integer.h
	doxygen Doxyfile

Integer.log:
	git log > Integer.log

RunInteger: Integer.h RunInteger.c++
	g++-4.7 -fprofile-arcs -ftest-coverage -pedantic -std=c++11 -Wall RunInteger.c++ -o RunInteger

RunInteger.out: RunInteger
	-valgrind RunInteger > RunInteger.out
	gcov-4.7 -b RunInteger.c++
	cat         RunInteger.c++.gcov

TestInteger: Integer.h TestInteger.c++
	g++-4.7 -fprofile-arcs -ftest-coverage -pedantic -std=c++11 -Wall TestInteger.c++ -o TestInteger -lgtest -lgtest_main -lpthread

TestInteger.out: TestInteger
	-valgrind TestInteger
	gcov-4.7 -b TestInteger.c++
	cat         TestInteger.c++.gcov
