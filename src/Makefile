CXX := g++
EXEC := zombie
DEBUG := -O2
#DEBUG := -g

OBJDIR := obj

OBJLIST := Object.o SpatialHash.o Bullet.o Entity.o Enemy.o Player.o Main.o 

OBJS := $(addprefix $(OBJDIR)/,$(OBJLIST))

CXXFLAGS = -Wall $(DEBUG) -L$(SFML_LIB_DIR) -lsfml-audio -lsfml-graphics -lsfml-window -lsfml-system -I$(SFML_INC_DIR) -I../include

SHELL = /bin/sh

.SUFFIXES: 
.SUFFIXES: .cpp .h .o

.PHONY: all clean
all : $(EXEC)

clean:
	rm -f $(OBJS)
	rm -f $(EXEC)

#OBJS depend on OBJDIR only on the first object .o
$(OBJS): | $(OBJDIR)

$(OBJDIR):
	mkdir $(OBJDIR) 

$(EXEC) : $(OBJS)
	$(CXX) $^ -o $(EXEC) $(CXXFLAGS)

$(OBJDIR)/%.o : %.cpp
	$(CXX) -c $< -o $@ $(CXXFLAGS)
