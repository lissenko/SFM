# Author: Tanguy Lissenko

ODIR := obj
SDIR := src
IDIR := include

NAME := SFM
BUILD := $(ODIR)/$(NAME)
SRCS := $(shell find $(SDIR)/ -type f -name '*.cpp')
OBJS := $(patsubst $(SDIR)/%.cpp,$(ODIR)/%.o,$(SRCS))

CXX := g++

CXXFLAGS := -std=c++20 -masm=intel -pthread \
-fopenmp -ggdb3 -Wpedantic -Wall -Wextra -Wconversion -Winline\
-Wsign-conversion -Weffc++ -Wstrict-null-sentinel -Wold-style-cast -Wnoexcept\
-Wctor-dtor-privacy -Woverloaded-virtual -Wsign-promo\
-Wzero-as-null-pointer-constant -Wsuggest-final-types -Wsuggest-final-methods\
-Wsuggest-override

CXXDEBUGFLAGS := -D __DEBUG__ -g

CPPFLAGS := -I$(IDIR) -MMD

LDLIBS := -lncurses

# Pre-build
$(shell mkdir -p $(ODIR))
$(shell mkdir -p $(ODIR)/sfm/file)
$(shell mkdir -p $(ODIR)/sfm/window/info)
$(shell mkdir -p $(ODIR)/sfm/graphic)

all: $(BUILD)

debug: CXXFLAGS += $(CXXDEBUGFLAGS)
debug: $(BUILD)

# Link
$(BUILD): $(OBJS)
	$(CXX) $^ $(LDLIBS) -o $@

-include $(shell find $(ODIR)/ -type f -name '*.d')

# Compilation
$(ODIR)/%.o: $(SDIR)/%.cpp
	$(CXX) $< $(CXXFLAGS) -c $(CPPFLAGS) -o $@

install: $(BUILD)
	mkdir -p ~/.local/bin
	cp $(BUILD) ~/.local/bin/

uninstall:
	rm -f ~/.local/bin/$(NAME)

run: debug
	./$(BUILD)

clean:
	rm -rf $(ODIR)
