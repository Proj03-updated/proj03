EXE = proj03
SOURCES = main.cpp
OBJECTS := $(SOURCES:%.cpp=%.o)
CXXFLAGS = -std=c++11

$(EXE): $(OBJECTS)
	$(CXX) $^ -o $@

main.o: main.cpp ExprVisitor.h Expr.h Binary.h Uniary.h

clean:
	$(RM) $(EXE) $(OBJECTS)
