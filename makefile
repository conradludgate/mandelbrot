IDIR=include
CC=g++
CFLAGS=-I $(IDIR)

ODIR=obj
SDIR=src

LIBS=-lm -lglfw -lGL -ldl

_OBJ = glad.o main.o shaders.o shape.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

$(ODIR)/%.o: src/%.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

mb: $(OBJ)
	g++ -o $@ $^ $(CFLAGS) $(LIBS)

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~ 