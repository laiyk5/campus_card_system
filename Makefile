SRC=src
BUILD=build
BIN=$(BUILD)/bin
OBJ=$(BUILD)/obj
EXECUTABLE_NAME=campus_card_system
CXX=clang++

SOURCE_FILES=\
	main.cc \
	menu.cc \
	system_functions.cc \

EXECUTABLE_FILES = $(EXECUTABLE_NAME:%=$(BIN)/%)
OBJECT_FILES = $(SOURCE_FILES:%.cc=$(OBJ)/%.o)

CPPFLAGS = -I include
LDLIBS = -lmysqlcppconn8
CXXFLAGS = -std=c++20

build: $(EXECUTABLE_FILES)

clean:
	rm -rf $(BUILD)

reset_database:
	mysql --user=root --password < sql/reset.sql

.PHONY: build clean reset_database

$(EXECUTABLE_FILES): $(OBJECT_FILES)
	@mkdir -p $(@D)
	$(LINK.cc) $^ $(LDLIBS) -o $@
	@echo "Build successful!"

$(OBJECT_FILES): $(OBJ)/%.o: $(SRC)/%.cc include/*.hh
	@echo Compiling $<
	@test -d $(@D) || mkdir -p $(@D)
	@$(COMPILE.cc) -c -o $@ $<
