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
SRCS = $(wildcard $(SRCDIR)/*)
OBJS = $(SRCS:$(SRCDIR)/%.cpp=%.o)
EXE  = mb

#
# Release build settings
#
RELDIR = build
RELOBJS = $(addprefix $(RELDIR)/, $(OBJS))
RELCXXFLAGS = -O3 -DNDEBUG

.PHONY: all clean debug prep release remake

# Default build
all: prep release

#
# Release rules
#
release: $(EXE)

$(EXE): $(RELOBJS)
	$(CXX) $(CXXFLAGS) $(RELCXXFLAGS) $(LIBS) -o $(EXE) $^

$(RELDIR)/%.o: $(SRCDIR)/%.cpp
	$(CXX) -c $(CXXFLAGS) $(RELCXXFLAGS) $(LIBS) -o $@ $<

#
# Other rules
#
prep:
	@mkdir -p $(RELDIR)

remake: clean all

clean:
	rm -f $(RELOBJS)