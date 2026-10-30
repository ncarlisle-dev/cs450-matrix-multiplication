# files
SRCS := main.c
OBJS := $(patsubst %.c,%.o,$(SRCS))
DEPS := $(patsubst %.c,%.d,$(SRCS))

SRCS_DIR    := src
INCLUDE_DIR := include
BUILD_DIR   := build
DEPS_DIR    := deps
OBJS_DIR    := objs
TARGET      := mat_mult_prog

# compilation stuff
CC := gcc

ifeq ($(DEBUG), true)
	CFLAGS := -Wall -fopenmp -I$(INCLUDE_DIR) -MMD -MP -O0 -g
else
	CFLAGS := -Wall -fopenmp -I$(INCLUDE_DIR) -MMD -MP -O2
endif

LDFLAGS := -fopenmp

# begin directives
SRC_FILES := $(addprefix $(SRCS_DIR)/,$(SRCS))
OBJ_FILES := $(addprefix $(BUILD_DIR)/$(OBJS_DIR)/,$(OBJS))
DEP_FILES := $(addprefix $(BUILD_DIR)/$(DEPS_DIR)/,$(DEPS))

-include $(DEP_FILES)

# compilation
$(BUILD_DIR)/$(TARGET): $(OBJ_FILES)
	@mkdir -p $(BUILD_DIR)
	$(CC) $(LDFLAGS) $(OBJ_FILES) -o $(BUILD_DIR)/$(TARGET)

$(BUILD_DIR)/$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c
	@mkdir -p $(dir $@)
	@mkdir -p $(patsubst $(BUILD_DIR)/$(OBJS_DIR)/%,$(BUILD_DIR)/$(DEPS_DIR)/%,$(dir $@))
	$(CC) $(CFLAGS) -c $< -MF $(patsubst $(SRCS_DIR)/%.c,$(BUILD_DIR)/$(DEPS_DIR)/%.d,$<) -o $@

# helpers
.PHONY: clean run

run:
	./$(BUILD_DIR)/$(TARGET)

clean:
	rm -rf $(BUILD_DIR)
