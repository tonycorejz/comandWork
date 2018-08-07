CC = gcc
OBJDIR = ./object_file

all: dir exe

dir: ./object_file

./object_file:
	mkdir ./object_file

exe: $(OBJDIR)/main.o $(OBJDIR)/connect.o $(OBJDIR)/window.o $(OBJDIR)/waitClick.o $(OBJDIR)/battle.o $(OBJDIR)/reposition.o
	$(CC) -o SeaBattle $(OBJDIR)/main.o $(OBJDIR)/connect.o $(OBJDIR)/window.o $(OBJDIR)/waitClick.o $(OBJDIR)/battle.o $(OBJDIR)/reposition.o -lncurses

$(OBJDIR)/main.o: main.c
	$(CC) -c main.c -o $(OBJDIR)/main.o -I./

$(OBJDIR)/connect.o: connect.c
	$(CC) -c connect.c -o $(OBJDIR)/connect.o -I./

$(OBJDIR)/window.o: window.c
	$(CC) -c window.c -o $(OBJDIR)/window.o -I./

$(OBJDIR)/waitClick.o: waitClick.c
	$(CC) -c waitClick.c -o $(OBJDIR)/waitClick.o -I./

$(OBJDIR)/battle.o: battle.c
	$(CC) -c battle.c -o $(OBJDIR)/battle.o -I./

$(OBJDIR)/reposition.o: reposition.c
	$(CC) -c reposition.c -o $(OBJDIR)/reposition.o -I./

clean:
	rm -rf ./object_file
	rm SeaBattle
