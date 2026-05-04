CXX := g++
CXXFLAGS ?= -g -std=c++17 -MMD -MP
SHELL := cmd.exe
.SHELLFLAGS := /c

OUT ?= raytracer.exe
BUILD ?= build/testbench.cpp
OBJDIR ?= obj

SRC = raytracer.cpp \
	$(wildcard world/*.cpp) \
	$(wildcard utilities/*.cpp) \
	$(wildcard geometry/*.cpp) \
	$(wildcard acceleration/*.cpp) \
	$(wildcard lights/*.cpp) \
	$(wildcard tracers/*.cpp) \
	$(wildcard cameras/*.cpp) \
	$(wildcard image/*.cpp) \
	$(wildcard samplers/*.cpp) \
	$(wildcard materials/BRDF/*.cpp) \
	$(wildcard materials/*.cpp) \
	$(BUILD)

OBJ = $(addprefix $(OBJDIR)/,$(subst /,_,$(SRC:.cpp=.o)))
DEPS = $(OBJ:.o=.d)

.PHONY: all clean run

all: $(OUT)

$(OBJDIR):
	if not exist "$(OBJDIR)" mkdir "$(OBJDIR)"

$(OUT): $(OBJ)
	$(CXX) $(CXXFLAGS) $^ -o $@

define compile_template
$(OBJDIR)/$(subst /,_,$(basename $(1))).o: $(1) | $(OBJDIR)
	$(CXX) $(CXXFLAGS) -c $$< -o $$@
endef

$(foreach src,$(SRC),$(eval $(call compile_template,$(src))))

-include $(DEPS)

run: $(OUT)
	$(OUT)

clean:
	if exist "$(OUT)" del /f /q "$(OUT)"
	if exist "$(OBJDIR)" rmdir /s /q "$(OBJDIR)"
