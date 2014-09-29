
SRC = $(wildcard *.cpp)

#
# Add $(MAC_OPT) to the compile line for Mac OSX.
MAC_OPT = "-I/opt/X11/include"

run:	Tower
	./Tower

Tower: $(SRC)
	g++ -o Tower $(SRC) -L/usr/X11R6/lib -lX11 -lstdc++ #$(MAC_OPT)
