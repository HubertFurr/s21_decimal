# Дополнительные библиотеки не для Mac, по умолчанию оставляем пустым, чтобы не портить сборку на Mac
LIBS_ADDITIONAL = 
# Команда для открытия файла отчета о покрытии по умполчанию
CMD_OPEN = open

# Определяем ОС
ifeq ($(OS), Windows_NT)
    detected_OS := Windows
else
    detected_OS := $(shell uname -s)
endif
# Настраиваем переменные в зависимости от ОС
ifeq ($(detected_OS), Linux)
	detected_Linux := $(shell cat /etc/issue | sed -n '1p' | awk '{print $$1}')
	# Значение по умолчанию для любых версий Linux
	LIBS_ADDITIONAL = -lm -pthread -lsubunit -lrt
	ifeq ($(detected_Linux), Arch)
	LIBS_ADDITIONAL = -lm
	CMD_OPEN = xdg-open
	endif

	ifeq ($(detected_Linux), Ubuntu)
	LIBS_ADDITIONAL = -lm -pthread -lsubunit -lrt
	CMD_OPEN = xdg-open
	endif
	
	ifeq ($(detected_Linux), Debian)
	LIBS_ADDITIONAL = -lm -pthread -lsubunit -lrt
	CMD_OPEN = xdg-open
	endif
endif

# Набор цветов для красивостей
GREEN   =   \033[0;32m
RED		=   \033[0;31m
RESET	=   \033[0m

# Компилятор / Линковщик
CC=gcc

# Пути до используемых папок
OBJ_DIR = obj
GCOV_OBJ_DIR = obj/gcov
TESTS_OBJ_DIR = obj/tests
TEST_DIR = tests
MODULES_DIR = s21_decimal
REPORT_DIR = report

#Цель и название исполняемого файла для тестов
TEST_EXE = test
#Цель и название исполняемого файла для отчета о покрытии
GCOV_EXE = gcov_report

# Имя статичной библиотеки со всеми модулями проекта
MODULES_STATIC_LIBRARY = s21_decimal.a
# Она же, но с флагами для отчета покрытия
MODULES_STATIC_LIBRARY_GCOV = s21_decimal_gcov.a

# Дефолтное значение 1 если не задано с консоли
# Задаем так: make test MODE=4
MODE?=1
ifeq ($(MODE), 2)
	# Собираем с fsanitizer
	LFLAGS=-g -fsanitize=leak -fsanitize=address -fsanitize=undefined -fsanitize=unreachable -fno-sanitize-recover \
	-fstack-protector -fanalyzer
	CFLAGS_TESTS=-Wall -Werror -Wextra -c -g -fsanitize=leak -fsanitize=address -fsanitize=undefined -fsanitize=unreachable \
	-fno-sanitize-recover -fstack-protector
	CFLAGS += $(CFLAGS_TESTS) -fanalyzer
else 
	ifeq ($(MODE), 3)
		# Собираем с отладочной информацией для valgrind
		LFLAGS=-g
		CFLAGS=-Wall -Werror -Wextra -c -g
		CFLAGS_TESTS = $(CFLAGS)
	else 
		ifeq ($(MODE), 4)
			# Собираем со всеми флагами проверок и пишем идеальный код
			LFLAGS=-g -fsanitize=address -fsanitize=undefined -fno-sanitize-recover -fstack-protector -fanalyzer
			CFLAGS=-Wall -Werror -Wextra -c -g -O2 -pedantic -std=c11 -Wshadow -Wlogical-op -Wshift-overflow=2 \
			-Wduplicated-cond -Wcast-align -Wfloat-equal -Wconversion -Wcast-qual -D_GLIBCXX_DEBUG \
			-D_GLIBCXX_DEBUG_PEDANTIC -D_FORTIFY_SOURCE=2 -fsanitize=address -fsanitize=undefined \
			-fno-sanitize-recover -fstack-protector -fanalyzer
			CFLAGS_TESTS = $(CFLAGS)
		else
			# Стандартный режим
			LFLAGS= 
			CFLAGS=-Wall -Werror -Wextra -c -std=c11 -pedantic
			CFLAGS_TESTS = $(CFLAGS)
		endif
	endif
endif

# Флаги для lcov
GCOV_FLAGS =-fprofile-arcs -ftest-coverage

# Дополнительные библиотеки для линковки
LIBS = -lcheck $(LIBS_ADDITIONAL)

# Дополнительные библиотеки для линковки c отчетом о покрытии
LIBS_GCOV = $(LIBS) -lgcov

# Заполняем переменные со списком директорий, исходных и исполняемых файлов
ALL_MODULES_DIRS = $(shell find $(MODULES_DIR) -type d)
ALL_MODULES_C = $(notdir $(shell find $(ALL_MODULES_DIRS) -maxdepth 1 -name "*.c"))
ALL_MODULES_H = $(shell find $(ALL_MODULES_DIRS) -maxdepth 1 -name "*.h")
MAIN_H = $(shell find . -maxdepth 1 -name "*.h")
ALL_H = $(ALL_MODULES_H) $(MAIN_H)
ALL_MODULES_O = $(ALL_MODULES_C:%.c=%.o)

ALL_TESTS_DIRS = $(shell find $(TEST_DIR) -type d)
ALL_TESTS_C = $(notdir $(shell find $(ALL_TESTS_DIRS) -maxdepth 1 -name "*.c"))
ALL_TESTS_H = $(shell find $(ALL_TESTS_DIRS) -maxdepth 1 -name "*.h")
ALL_TESTS_O = $(addprefix $(TESTS_OBJ_DIR)/, $(notdir $(ALL_TESTS_C:%.c=%.o)))

ALL_MODULES_GCOV_O = $(addprefix $(GCOV_OBJ_DIR)/, $(notdir $(ALL_MODULES_C:.c=.o)))

# Набор всех файлов для cpplint / cppcheck
ALL_C_H_FILES = $(shell find . -type f | grep "\.(c|h)$$" -E)

# Указываем список каталогов, в которых make выполняет поиск
vpath %.c $(ALL_MODULES_DIRS) : $(ALL_TESTS_DIRS)
vpath %.o $(OBJ_DIR)

# Далее идут все цели
all: $(TEST_EXE) $(GCOV_EXE)

$(TEST_EXE): $(OBJ_DIR) $(TESTS_OBJ_DIR) $(MODULES_STATIC_LIBRARY) $(ALL_TESTS_O)
	@$(CC) $(LFLAGS) $(ALL_TESTS_O) $(MODULES_STATIC_LIBRARY) $(LIBS) -o $(TEST_EXE)
	@echo "\n-------------------------------------------------------------------------------------------------\n"
	@./$(TEST_EXE)

$(GCOV_EXE): $(GCOV_OBJ_DIR) $(TESTS_OBJ_DIR) $(REPORT_DIR) $(MODULES_STATIC_LIBRARY_GCOV) $(ALL_TESTS_O) $(ALL_H) $(ALL_TESTS_H)
	@$(CC) $(LFLAGS) $(ALL_TESTS_O) $(MODULES_STATIC_LIBRARY_GCOV) $(LIBS_GCOV) -o ./$(GCOV_EXE)
	@echo "\n-------------------------------------------------------------------------------------------------\n"
	@./$(GCOV_EXE)
	@gcov -o $(GCOV_OBJ_DIR) $(ALL_MODULES_C)
	@lcov -b ./ -d $(GCOV_OBJ_DIR) --gcov-tool /usr/bin/gcov -c -o output.info
	@genhtml -o $(REPORT_DIR) output.info
	@rm *.c.gcov output.info
	$(CMD_OPEN) $(REPORT_DIR)/index.html

$(MODULES_STATIC_LIBRARY): $(OBJ_DIR) $(TESTS_OBJ_DIR) $(ALL_MODULES_O) $(ALL_H)
	@echo "$(GREEN)*$(RESET)\c"
	@ar rc $(MODULES_STATIC_LIBRARY) $(addprefix $(OBJ_DIR)/, $(ALL_MODULES_O))
	@ranlib $(MODULES_STATIC_LIBRARY)

$(MODULES_STATIC_LIBRARY_GCOV): $(GCOV_OBJ_DIR) $(TESTS_OBJ_DIR) $(ALL_MODULES_GCOV_O) $(ALL_H)
	@echo "$(GREEN)*$(RESET)\c"
	@ar rc $(MODULES_STATIC_LIBRARY_GCOV) $(ALL_MODULES_GCOV_O)
	@ranlib $(MODULES_STATIC_LIBRARY_GCOV)

%.o: %.c $(ALL_H) $(ALL_TESTS_H)
	@echo "$(GREEN)*$(RESET)\c"
	@$(CC) $(CFLAGS) -o $(addprefix $(OBJ_DIR)/, $@) $<

$(GCOV_OBJ_DIR)/%.o : %.c $(ALL_H) $(ALL_TESTS_H)
	@echo "$(GREEN)*$(RESET)\c"
	@$(CC) $(CFLAGS) $(GCOV_FLAGS) -o $@ $<

$(TESTS_OBJ_DIR)/%.o : %.c $(ALL_H) $(ALL_TESTS_H)
	@echo "$(GREEN)*$(RESET)\c"
	@$(CC) $(CFLAGS_TESTS) -o $@ $<

$(REPORT_DIR):
	@mkdir -p $(REPORT_DIR)
	@echo "folder: $(GREEN)$(REPORT_DIR) was created$(RESET)"
$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)
	@echo "folder: $(GREEN)$(OBJ_DIR) was created$(RESET)"
$(GCOV_OBJ_DIR):
	@mkdir -p $(GCOV_OBJ_DIR)
	@echo "folder: $(GREEN)$(GCOV_OBJ_DIR) was created$(RESET)"
$(TESTS_OBJ_DIR):
	@mkdir -p $(TESTS_OBJ_DIR)
	@echo "folder: $(GREEN)$(TESTS_OBJ_DIR) was created$(RESET)"

clean:
	rm -rf $(OBJ_DIR)
	rm -rf $(REPORT_DIR)
	rm -f *.a *.o
	rm -f *.c.gcov *.gcno *.gcov *.gcda output.info
	rm -f ./$(GCOV_EXE) ./$(TEST_EXE)

rebuild: clean all

cpplint: 
	python3 ../materials/linters/cpplint.py --extensions=c $(ALL_C_H_FILES)
cppcheck:
	cppcheck --enable=all --suppress=missingIncludeSystem $(ALL_C_H_FILES)
leaks:
	leaks --atExit -- ./$(TEST_EXE)
valgrind:
	valgrind --trace-children=yes --track-fds=yes --track-origins=yes --leak-check=full --show-leak-kinds=all -s ./$(TEST_EXE)

.PHONY: all clean rebuild cpplint cppcheck leaks valgrind
