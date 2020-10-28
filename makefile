#
# Compiler flags
#
CXX = g++
CXXFLAGS = -std=c++1z -I include
LIBS = -lm -lglfw -lGL -ldl

#
# Project files
#
SRCDIR = src
SRCS = $(wildcard $(SRCDIR)/*.cpp)
OBJS = $(SRCS:$(SRCDIR)/%.cpp=%.o)
EXE  = mb

#
# Release build settings
#
RELDIR = build
RELOBJS = $(addprefix $(RELDIR)/, $(OBJS))
RELCXXFLAGS = -O3 -DNDEBUG

.PHONY: all clean debug prep release remake glad

# Default build
all: prep release

#
# Release rules
#
release: $(EXE)

$(EXE): $(RELDIR)/glad.o $(RELOBJS)
	$(CXX) $(CXXFLAGS) $(RELCXXFLAGS) $(LIBS) -o $(EXE) $^

$(RELDIR)/%.o: $(SRCDIR)/%.cpp
	$(CXX) -c $(CXXFLAGS) $(RELCXXFLAGS) $(LIBS) -o $@ $<

src/glad.c:
	glad --profile="compatibility" --api="gl=3.3" --generator="c" --spec="gl" --out-path="."

$(RELDIR)/glad.o: src/glad.c
	$(CXX) -c $(CXXFLAGS) $(RELCXXFLAGS) $(LIBS) -o $@ $<

#
# Other rules
#
prep:
	@mkdir -p $(RELDIR)

remake: clean all

clean:
	rm -f $(RELOBJS)