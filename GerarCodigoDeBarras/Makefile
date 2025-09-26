CC = gcc
CFLAGS = -Wall -Iinclude
SRC_DIR = src
OBJ_DIR = obj
BUILD_DIR = build

TARGET = $(BUILD_DIR)/ean8-generator
SRCS = $(SRC_DIR)/main.c $(SRC_DIR)/ean8.c
OBJS = $(OBJ_DIR)/main.o $(OBJ_DIR)/ean8.o

all: $(TARGET)

# regra para linkar o executável final
$(TARGET): $(OBJS)
	@mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) -o $@ $^

# regra genérica para compilar os .c em .o dentro de obj/
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# limpeza
clean:
	rm -rf $(OBJ_DIR)/*.o $(TARGET)

# limpeza total (inclusive binários)
distclean: clean
	rm -rf $(BUILD_DIR)

.PHONY: all clean distclean
