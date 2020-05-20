TARGET=revgen

SrcDir = native/src/
ObjDir = obj/
BinDir = bin/

CC = gcc
CFlags = -Wall -Werror
LFlags =

Sources := $(wildcard $(SrcDir)/*.c)
Objs := $(Sources:$(SrcDir)%.c=$(ObjDir)%.o)

build: $(Objs)
	@mkdir $(BinDir) -p
	@$(CC) $(Objs) -o -$(BinDir)/$(Target) $(LFlags)
	@echo "Linking "$(Target)" complete"

$(Objs): $(ObjDir)%.o : $(SrcDir)/%.c
	@mkdir $(ObjDir) -p
	@$(CC) -c $(CFlags) $< -o $@
	@echo "Compiled "$<" successfully"

.PHONY: clean
clean:
	@rm -rf $(ObjDir)
	@rm -rf $(BinDir)

