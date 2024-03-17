CC				= g++ -std=c++11
CFLAGS			= -O2 -Wall
# OBJ_FILEを検索するパス
VPATH			= src:src/image:src/converter:src/utils
# オブジェクトファイルや実行ファイルを格納するディレクトリ
BUILD_DIR		= build
# オブジェクトファイルを格納するディレクトリ
OBJ_DIR			= $(BUILD_DIR)/objs
# コンパイルするオブジェクトファイル
OBJ_FILE		= main.o ImageData.o RGB.o ImageBase.o BMP.o PNG.o ImageFactory.o Converter.o Utils.o
# リンク時に渡すためのオブジェクトファイルのパス
OBJS			= $(OBJ_FILE:%.o=$(OBJ_DIR)/%.o)
# オブジェクトファイルに対応するcppファイル
SRCS			= $(OBJ_FILE:%.o=%.cpp)
# 生成する実行ファイル
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
