program:directory_ops.o dirent.o logger.o main.o permission.o file_operaiton.o
	g++ ./lib/directory_ops.o ./lib/dirent.o ./lib/logger.o ./lib/main.o ./lib/permission.o ./lib/file_operation.o -o ./bin/program
directory_ops.o:
	g++ -I "./include" -c ./src/directory_ops.c -o ./lib/directory_ops.o
dirent.o:
	g++ -I "./include" -c ./src/dirent.c -o ./lib/dirent.o
logger.o:
	g++ -I "./include" -c ./src/logger.c -o ./lib/logger.o
permission.o:
	g++ -I "./include" -c ./src/permission.c -o ./lib/permission.o
file_operaiton.o:
	g++ -I "./include" -c ./src/file_operation.c -o ./lib/file_operation.o
main.o:
	g++ -I "./include" -c ./src/main.c -o ./lib/main.o






