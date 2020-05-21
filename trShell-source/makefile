TARGET=trShell

SrcDir = native/src
IncDir = native/include
ObjDir = obj
BinDir = bin

CC = gcc
CFlags = -Wall -Werror -I$(IncDir)
LFlags =

Sources := $(wildcard $(SrcDir)/*.c)
Objs := $(Sources:$(SrcDir)%.c=$(ObjDir)%.o)

build: $(Objs)
	@mkdir $(BinDir) -p
	@$(CC) $(Objs) -o $(BinDir)/$(TARGET) $(LFlags)
	@echo "Linking "$(TARGET)" complete"

$(Objs): $(ObjDir)%.o : $(SrcDir)%.c
	@mkdir $(ObjDir) -p
	@$(CC) -c $(CFlags) $< -o $@
	@echo "Compiled "$<" successfully"

publish: build
	@cp $(BinDir)/$(TARGET) ../$(TARGET)
	@echo "Published "$(TARGET)

.PHONY: clean
clean:
	@rm -rf $(ObjDir)
	@rm -rf $(BinDir)

