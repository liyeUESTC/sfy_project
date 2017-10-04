DIR_OBJ = obj
DIR = ..
DIR_BIN=bin
$(DIR_BIN)/server.a:$(DIR_OBJ)/server_main.o $(DIR_OBJ)/writenReadn.o
	g++ -o bin/server.a obj/server_main.o obj/writenReadn.o
$(DIR_OBJ)/server_main.o:server_main.c $(DIR)/writenReadn.c $(DIR)/writenReadn.h
	g++ -c server_main.c -o obj/server_main.o 
$(DIR_OBJ)/writenReadn.o:$(DIR)/writenReadn.c $(DIR)/writenReadn.h
	g++ -c ../writenReadn.c -o obj/writenReadn.o
