#----------------------------#
#	Make File for Graph		 #
#-----Anikett Gauba----------#
#----------------------------#
all: test # runs everything at once

test: test_graph.o
	g++ -o test test_graph.o graph.cpp

test_graph.o:
	g++ -c test_graph.cpp

clean:
	rm -f test usecase *.o *.exe

#For when doin in vscode on Windows:
# del /Q /F test usecase *.o *.exe

#For when on linux & Mac:
# rm -f test usecase *.o *.exe