# To compile tests type in terminal "make <logic / gui / both>", depends on what you want
# To compile main game type "make game"
# To execute compiled thingy, type "./name" in terminal
# If you use test_both or game, only one should have main() function
CC=gcc

# Make for actual game
# Don't know, don't ask and don't touch, unless it doesn't work
INCLUDE_DIR = include
CFLAGS = -I$(INCLUDE_DIR)
OBJECT_DIR = obj
SOURCE_DIR = src

_DEPS = file_operation.h game_logic.h gui.h
DEPS = $(patsubst %,$(INCLUDE_DIR)/%,$(_DEPS))

$(OBJECT_DIR):
	mkdir -p $(OBJECT_DIR)

_OBJ = file_operation.o game_logic.o gui.o main.o
OBJ = $(patsubst %,$(OBJECT_DIR)/%,$(_OBJ))

$(OBJECT_DIR)/%.o: $(SOURCE_DIR)/%.c $(DEPS) | $(OBJECT_DIR)
	$(CC) -c -o $@ $< $(CFLAGS)

game: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

# Make for tests
TEST_CFLAGS=-I.
TEST_DEPS = tests/testing.h

logic: tests/test_logic.c $(TEST_DEPS)
	$(CC) -o $@ tests/test_logic.c

gui: tests/test_gui.c $(TEST_DEPS)
	$(CC) -o $@ tests/test_gui.c

both: tests/test_gui.c tests/test_logic.c $(TEST_DEPS)
	$(CC) -o $@ $^ $(TEST_CFLAGS)

# Cleaning up files
.PHONY: clean
clean:
	make clean_compiled
	make clean_test
	make clean_game
clean_test:
	rm -f tests/*.o
clean_game:
	rm -f $(OBJECT_DIR)/*.o
clean_compiled:
	rm -f logic gui both game