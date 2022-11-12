SRC=src
BUILD=build
BIN=$(BUILD)/bin
OBJ=$(BUILD)/obj
EXECUTABLE_NAME=campus_card_system

SOURCE_FILES=\
	data_types.cc \
	main.cc \
	menu.cc \
	system_functions.cc \
	system_manage.cc \

DATA_FILE_NAMES=\
	campus_card_datas.dat \
	consume_records.dat \
	inpour_records.dat \
	student_datas.dat \

EXECUTABLE_FILES = $(EXECUTABLE_NAME:%=$(BIN)/%)
OBJECT_FILES = $(SOURCE_FILES:%.cc=$(OBJ)/%.o)
DATA_FILES = $(DATA_FILE_NAMES:%=$(BIN)/%)

CXXFLAGS = -I include

build: $(EXECUTABLE_FILES) $(DATA_FILES)

clean:
	rm -rf $(BUILD)

.PHONY: build clean

$(EXECUTABLE_FILES): $(OBJECT_FILES)
	@mkdir -p $(@D)
	@$(LINK.cc) -o $@ $^
	@echo "Build successful!"

$(OBJECT_FILES): $(OBJ)/%.o: $(SRC)/%.cc
	@echo Compiling $<
	@test -d $(@D) || mkdir -p $(@D)
	@$(COMPILE.cc) -c -o $@ $<

$(DATA_FILES): $(BIN)/%.dat:
	@test -d $(@D) || mkdir -p $(@D)
	@test -e $@ || touch $@; echo "Datafile $@ initialized."
