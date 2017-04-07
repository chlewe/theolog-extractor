CC      := gcc
EXE     := theologExtractor
SOURCES := theologExtractor.c
C_FLAGS += --std=c99 -Wall -Wextra -Wpedantic -Werror -Og

all: $(EXE)

$(EXE): $(SOURCES)
	$(CC) -o $(EXE) $(C_FLAGS) $(SOURCES) $(LD_FLAGS)

clean:
	rm -f $(EXE)
