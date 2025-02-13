.PHONY: all install uninstall clean dvi dist test gcov_report

PROGRAM_NAME := tetris

#Компилятор и флаги
CC := gcc
CFLAGS := -Wall -Wextra -Werror -std=c11 -Wpedantic

#C-файлы
BACKEND_FILES := brick_game/tetris/*.c
FRONTEND_FILES := gui/cli/*.c
FSM_FILES := fsm_matrix/*.c

#Директории с файлами игры
BACKEND_DIR := brick_game/tetris/
FRONTEND_DIR := gui/cli/
FSM_DIR := fsm_matrix/

#Создаваемые дополнительные директории
INSTALL_DIR := game/
DIST_DIR := dist
TEST_DIR := tests
OBJECTS_DIR := obj_files/
GAME_DIR := game_info
GCOV_DIR := gcov_report
DOXY_DIR := doxygen_folder

HIGHSCORE := $(GAME_DIR)/highscore_list.txt

CLANG := clang-format
STYLE := -style=Google

KERNEL = $(shell uname -s)

#Подключаемые библиотеки для Darwin/Ubuntu
ifeq ($(KERNEL), Linux)
	LIBS := -lcheck -lsubunit -lm
endif

ifeq ($(KERNEL), Darwin)
	LIBS := -lcheck
endif

all: install

$(PROGRAM_NAME).o:
	$(CC) $(CFLAGS) -c $(BACKEND_FILES) $(FRONTEND_FILES) $(FSM_FILES) 
	mkdir $(OBJECTS_DIR)
	mv *.o $(OBJECTS_DIR)

$(PROGRAM_NAME).a: clean $(PROGRAM_NAME).o 
	ar rcs $(PROGRAM_NAME).a $(OBJECTS_DIR)*.o
	ranlib $(PROGRAM_NAME).a

#Установка программы
install: uninstall $(PROGRAM_NAME).a
	mkdir $(GAME_DIR)
	touch $(HIGHSCORE)
	echo "0" >> $(HIGHSCORE)
	$(CC) $(CFLAGS) -c $(PROGRAM_NAME).c
	mv *.o $(OBJECTS_DIR)
	$(CC) $(CFLAGS) -o $(PROGRAM_NAME) $(OBJECTS_DIR)*.o -L. $(PROGRAM_NAME).a -lm -lncurses
	mkdir $(INSTALL_DIR)
	mv $(PROGRAM_NAME) $(INSTALL_DIR)

#Удаление программы (удаление производных install)
uninstall:
	rm -rf $(OBJECTS_DIR) $(PROGRAM_NAME).a $(GAME_DIR) $(INSTALL_DIR)

#Удаление производных всех целей
clean: uninstall
	rm -rf *.a $(PROGRAM_NAME) $(DIST_DIR) *.o $(DOXY_DIR) $(GCOV_DIR) *.gcno *gcda *.gcov testout

#Создание документации с помощью doxygen
dvi:
	mkdir -p $(DOXY_DIR)
	doxygen
	open $(DOXY_DIR)/html/index.html

#Создание дистрибутива игры
dist: clean $(PROGRAM_NAME).a
	mkdir -p $(DIST_DIR)
	tar -cf $(DIST_DIR)/$(PROGRAM_NAME)-1.0.tar $(PROGRAM_NAME).a $(OBJECTS_DIR)

#Тестирование кода
test: clean install
	$(CC) $(CFLAGS) --coverage $(BACKEND_FILES) $(TEST_DIR)/*.c -o testout $(LIBS)
	./testout

#Отчёт о покрытии кода
gcov_report: test
	mkdir $(GCOV_DIR)
	gcovr -r. --html --html-details -o $(GCOV_DIR)/index.html -e tests 
	rm -rf *.gcno *gcda *.gcov
	open $(GCOV_DIR)/index.html

#Запуск игры
play:
	./$(INSTALL_DIR)$(PROGRAM_NAME)

#Переустановка и запуск игры
go:	uninstall install play

#Проверки
clang:
	$(CLANG) $(STYLE) -n *.c $(FRONTEND_DIR)*.* $(BACKEND_DIR)*.* $(FSM_DIR)*.* $(TEST_DIR)/*.*

style:
	$(CLANG) $(STYLE) -i *.c $(FRONTEND_DIR)*.* $(BACKEND_DIR)*.* $(FSM_DIR)*.* $(TEST_DIR)/*.*

cppcheck:
	cppcheck $(FRONTEND_FILES) $(BACKEND_FILES) $(FSM_FILES) $(TEST_DIR)/*.c *.c 

valgrind: test
	valgrind --tool=memcheck --leak-check=yes --leak-check=full --show-leak-kinds=all ./testout