# Basic definitions
NAME := OsuBot

SRC_PATH := source
OBJ_PATH := .bin


# Compiler
CC := g++
CCFLAGS := -std=c++11 -Wall -Werror -Wextra


# Commands
RM := rm -f
RMDIR := rm -Rdf
MKDIR := mkdir -p


# Source files
SRC_NAME :=	main.cpp
SRC_NAME +=	Parser/OsuKey.cpp \
			Parser/OsuParser.cpp


SRC := $(addprefix $(SRC_PATH)/, $(SRC_NAME))
OBJ := $(addprefix $(OBJ_PATH)/, $(SRC_NAME:.cpp=.o))

OBJ_DIRS := $(sort $(dir $(OBJ)))

# Rules
all: $(NAME)

$(NAME): $(OBJ_DIRS) $(OBJ)
	$(CC) -o $@ $(OBJ)

$(OBJ_DIRS):
	@$(MKDIR) $@

$(OBJ_PATH)/%.o: $(addprefix $(SRC_PATH)/, %.cpp)
	$(CC) $(CCFLAGS) -MMD -MF $(<:.cpp=.d) -c $< -o $@


# Prerequisites files
DEP_FILES = $(SRC:%.cpp=%.d)
-include $(DEP_FILES)


clean:
	$(RM) $(OBJ)
	$(RM) $(DEP_FILES)
	$(RMDIR) $(OBJ_DIRS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re test