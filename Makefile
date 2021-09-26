CXX = g++ -fPIE
CXXFLAGS = -std=c++14 -Wall -MMD -Werror=vla
EXEC = 2048
OBJECTS = basicAI.o main.o window.o board.o client.o
DEPENDS = ${OBJECTS:.o=.d}

${EXEC}: ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC} -lX11

-include ${DEPENDS}

.PHONY: clean

clean:
	rm ${OBJECTS} ${EXEC} ${DEPENDS}


