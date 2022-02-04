all: compile

compile: remman.c
	@gcc remman.c -o remman

run: remman
	@./remman

clean:
	@rm remman
