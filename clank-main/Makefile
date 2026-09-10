CC = gcc

# Include build dir for generated headers, utils dir for util headers
CFLAGS = -Wall -Wextra -I. -I$(UTILS_DIR) -I$(BUILD_DIR)

# Output configuration
BUILD_DIR = build
TARGET_NAME = clank
TARGET = $(BUILD_DIR)/$(TARGET_NAME)

# Directory definitions
CMD_DIR = commands
UTILS_DIR = utils

# Find all source files
CMD_SRCS   = $(wildcard $(CMD_DIR)/*.c)
UTILS_SRCS = $(wildcard $(UTILS_DIR)/*.c)
UTILS_HDRS = $(wildcard $(UTILS_DIR)/*.h)

# Object files
CMD_OBJS   = $(patsubst $(CMD_DIR)/%.c,   $(BUILD_DIR)/%.o, $(CMD_SRCS))
UTILS_OBJS = $(patsubst $(UTILS_DIR)/%.c, $(BUILD_DIR)/%.o, $(UTILS_SRCS))

# Main source
MAIN_SRC = main.c
MAIN_OBJ = $(BUILD_DIR)/main.o

# Generated files
GEN_HDR   = $(BUILD_DIR)/commands.h
GEN_SRC   = $(BUILD_DIR)/commands_gen.c
GEN_OBJ   = $(BUILD_DIR)/commands_gen.o
UTILS_HDR = $(BUILD_DIR)/utils.h

# Default target
all: begin_msg $(TARGET) post_msg

# Debug target
debug: CFLAGS += -DCLANK_DEBUG -g
debug: begin_debug clean $(TARGET) post_msg

# Link everything together
$(TARGET): $(MAIN_OBJ) $(CMD_OBJS) $(UTILS_OBJS) $(GEN_OBJ) | $(BUILD_DIR)
	@echo "Linking executable..."
	@$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS) -lm

# Create build directory
$(BUILD_DIR):
	@mkdir -p $(BUILD_DIR)

# Compile main.c
$(MAIN_OBJ): $(MAIN_SRC) $(GEN_HDR) $(UTILS_HDR) | $(BUILD_DIR)
	@echo "Compiling main..."
	@$(CC) $(CFLAGS) -c $< -o $@

# Compile command files
$(BUILD_DIR)/%.o: $(CMD_DIR)/%.c | $(BUILD_DIR)
	@echo "Compiling command: $(notdir $<)"
	@$(CC) $(CFLAGS) -c $< -o $@

# Compile utils files
$(BUILD_DIR)/%.o: $(UTILS_DIR)/%.c $(UTILS_HDR) | $(BUILD_DIR)
	@echo "Compiling util: $(notdir $<)"
	@$(CC) $(CFLAGS) -c $< -o $@

# Compile generated command registry
$(GEN_OBJ): $(GEN_SRC) $(GEN_HDR) | $(BUILD_DIR)
	@echo "Compiling generated command registry..."
	@$(CC) $(CFLAGS) -c $< -o $@

# -------------------------------------------------
# COMMANDS GENERATOR
# -------------------------------------------------
$(GEN_HDR) $(GEN_SRC): $(CMD_SRCS) Makefile | $(BUILD_DIR)
	@echo "Generating command definitions..."

	@echo "#ifndef COMMANDS_H" > $(GEN_HDR)
	@echo "#define COMMANDS_H" >> $(GEN_HDR)
	@echo "" >> $(GEN_HDR)
	@echo "typedef struct {" >> $(GEN_HDR)
	@echo "    const char* name;" >> $(GEN_HDR)
	@echo "    int (*execute)(int argc, char* argv[]);" >> $(GEN_HDR)
	@echo "    void (*man)(void);" >> $(GEN_HDR)
	@echo "} Command;" >> $(GEN_HDR)
	@echo "" >> $(GEN_HDR)
	@echo "extern Command commands[];" >> $(GEN_HDR)
	@echo "" >> $(GEN_HDR)

	@for file in $(CMD_SRCS); do \
		name=$$(basename $$file .c); \
		echo "int clank_$$name(int argc, char* argv[]);" >> $(GEN_HDR); \
		echo "void man_$$name(void);" >> $(GEN_HDR); \
	done

	@echo "#endif" >> $(GEN_HDR)

	@echo "#include <stddef.h>" > $(GEN_SRC)
	@echo "#include \"commands.h\"" >> $(GEN_SRC)
	@echo "" >> $(GEN_SRC)
	@echo "Command commands[] = {" >> $(GEN_SRC)

	@for file in $(CMD_SRCS); do \
		name=$$(basename $$file .c); \
		echo "    {\"$$name\", clank_$$name, man_$$name}," >> $(GEN_SRC); \
	done

	@echo "    {NULL, NULL, NULL}" >> $(GEN_SRC)
	@echo "};" >> $(GEN_SRC)

# -------------------------------------------------
# UTILS MEGA-HEADER GENERATOR
# -------------------------------------------------
$(UTILS_HDR): $(UTILS_HDRS) Makefile | $(BUILD_DIR)
	@echo "Generating mega utils header..."
	@echo "#ifndef CLANK_UTILS_H" > $(UTILS_HDR)
	@echo "#define CLANK_UTILS_H" >> $(UTILS_HDR)
	@echo "" >> $(UTILS_HDR)

	@for hdr in $(UTILS_HDRS); do \
		echo "#include \"$(notdir $$hdr)\"" >> $(UTILS_HDR); \
	done

	@echo "" >> $(UTILS_HDR)
	@echo "#endif" >> $(UTILS_HDR)

# -------------------------------------------------
# Messages
# -------------------------------------------------
begin_msg:
	@echo "Beginning build..."

begin_debug:
	@echo "Beginning DEBUG build..."

post_msg:
	@echo "Build complete: $(TARGET)"

clean:
	@echo "Cleaning build directory..."
	@rm -rf $(BUILD_DIR)

.PHONY: all debug clean begin_msg post_msg begin_debug

