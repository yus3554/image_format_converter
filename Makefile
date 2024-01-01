CC				= g++ -std=c++11
CFLAGS			= -O2 -Wall
VPATH			= src:src/image:src/converter
BUILD_DIR		= build
OBJ_DIR			= $(BUILD_DIR)/objs
OBJ_FILE		= main.o ImageBase.o BMP.o PNG.o ImageFactory.o Converter.o
OBJS			= $(OBJ_FILE:%.o=$(OBJ_DIR)/%.o)
SRCS			= $(OBJ_FILE:%.o=%.cpp)
PROGRAM			= $(BUILD_DIR)/image_format_converter

.PHONY:			all
all:			$(PROGRAM)

$(PROGRAM):		$(OBJ_FILE)
				$(CC) $(OBJS) -o $(PROGRAM)

SUFFIXES:		.cpp .o
.cpp.o:
				mkdir -p $(OBJ_DIR)
				$(CC) -c $< -o $(OBJ_DIR)/$@

.PHONY:			clean
clean:;			rm -f $(OBJS) *~ $(PROGRAM)
