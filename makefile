CC = gcc
OBJDIR = ./object_file

all: dir exe main connect window battle reposition

dir: ./object_file

./object_file:
	mkdir ./object_file

exe: main connect window battle reposition
	$(CC) -o SeaBattle $(OBJDIR)/main.o $(OBJDIR)/connect.o $(OBJDIR)/window.o $(OBJDIR)/waitClick.o $(OBJDIR)/battle.o $(OBJDIR)/reposition.o -lncurses

main:
	$(CC) -c main.c -o $(OBJDIR)/main.o -I./

connect:
	$(CC) -c connect.c -o $(OBJDIR)/connect.o -I./

window:
	$(CC) -c window.c -o $(OBJDIR)/window.o -I./
	$(CC) -c waitClick.c -o $(OBJDIR)/waitClick.o -I./

battle:
	$(CC) -c battle.c -o $(OBJDIR)/battle.o -I./

reposition:
	$(CC) -c reposition.c -o $(OBJDIR)/reposition.o -I./

clean:
	rm -rf ./object_file
	rm SeaBattle
