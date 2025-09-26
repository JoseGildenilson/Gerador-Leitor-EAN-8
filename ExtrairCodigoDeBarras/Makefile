# Compilador e flags
CC = gcc
CFLAGS = -Wall -Wextra -Iinclude -g

# Pastas
SRC_DIR = src
OBJ_DIR = obj
BUILD_DIR = build

# Arquivos
SRC_FILES = $(wildcard $(SRC_DIR)/*.c)
OBJ_FILES = $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRC_FILES))
EXECUTABLE = $(BUILD_DIR)/ean8_leitor

# Regras
all: $(BUILD_DIR) $(OBJ_DIR) $(EXECUTABLE)

# Linkagem do executável
$(EXECUTABLE): $(OBJ_FILES)
	$(CC) $(CFLAGS) $^ -o $@

# Compilação dos .c para .o
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

# Criação das pastas
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

# Limpeza
clean:
	rm -rf $(OBJ_DIR)/*.o $(EXECUTABLE)

.PHONY: all clean
