CC = gcc
CFLAGS = -Wall -Werror -Wextra
C11 = -pedantic -std=c11
OS = $(shell uname -s)
REPORT = gcov_report
PROJECT_NAME = 3DViewer

all: clean install open

install: 
	cd $(PROJECT_NAME) && qmake && make && make clean && rm Makefile && cd ..
	mkdir build && mv $(PROJECT_NAME)/$(PROJECT_NAME).app build

uninstall:
	rm -rf build

open:
ifeq ($(OS), Darwin)
	cd build && open $(PROJECT_NAME).app
else
	cd build && xdg-open $(PROJECT_NAME).app
endif

clean:
	@rm -rf build \
	*.o \
	*.out \
	*.gcno \
	*.gcda \
	report

test: clean
ifeq ($(OS), Darwin)
	$(CC) $(CFLAGS) -fsanitize=address -lcheck test.c s21*.c -o test.out && ./test.out
else 
	$(CC) $(CFLAGS) -lrt -lpthread -lm -lsubunit -fsanitize=address -lcheck test.c s21*.c -o test.out && ./test.out
endif

gcov_report:
ifeq ($(OS), Darwin)
	$(CC) -fprofile-arcs -ftest-coverage test.c s21*.c -lcheck -o $(REPORT)
else
	$(CC) $(CFLAGS) -lrt -lpthread -lm -lsubunit -fsanitize=address -lcheck test.c s21*.c -o test.out && ./test.out
endif
	./$(REPORT)
	lcov -t report -o $(REPORT).info -c -d .
	genhtml -o report $(REPORT).info
	open ./report/index.html
	rm -rf *.gcno *.gcda $(REPORT).*
	rm $(REPORT)
	rm -rf *.dSYM

dist:
	rm -rf ../$(PROJECT_NAME)_archive/
	rm -rf $(PROJECT_NAME)_archive/
	mkdir $(PROJECT_NAME)_archive/
	mkdir $(PROJECT_NAME)_archive/src
	cp build/$(PROJECT_NAME).app/Contents/MacOS/$(PROJECT_NAME) $(PROJECT_NAME)_archive/src/
	tar cvzf $(PROJECT_NAME)_archive.tgz $(PROJECT_NAME)_archive

dvi:
	open README_DVI.md

leaks: test
ifeq ($(OS), Darwin)
	CK_FORK=no leaks --atExit -- ./test.out
else
	valgrind  --leak-check=full ./test.out
endif

style:
	cp ../materials/linters/.clang-format ./
	clang-format -n -i *.c *.h
	rm -rf .clang-format
