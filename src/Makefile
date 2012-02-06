CXX := g++
EXEC := zombie
#DEBUG := -O2
DEBUG := -g

OBJDIR := obj

OBJLIST := Object.o SpatialHash.o Bullet.o Entity.o Enemy.o Player.o Title.o \
					 Particle.o Peak.o Resources.o EffectSystem.o Collision.o Animation.o Animated.o Boss.o Main.o 

OBJS := $(addprefix $(OBJDIR)/,$(OBJLIST))

CXXFLAGS := -Wall $(DEBUG) -I$(SFML_INC_DIR)
LDFLAGS := -Wall $(DEBUG) -L$(SFML_LIB_DIR) -lsfml-audio -lsfml-graphics -lsfml-window -lsfml-system -I$(SFML_INC_DIR)

SHELL := /bin/sh

.SUFFIXES: 
.SUFFIXES: .cpp .h .o

.PHONY: all clean ctags
all : $(EXEC)

clean:
	rm -f $(OBJS)
	rm -f $(EXEC)

ctags:
	ctags --extra=+q --c++-kinds=+cdefgmnpstuvx $(shell find -L $(SFML_INC_DIR) . -name '*.[ch]*')

#OBJS depend on OBJDIR only on the first object .o
$(OBJS): | $(OBJDIR)

$(OBJDIR):
	mkdir $(OBJDIR) 

$(EXEC) : $(OBJS)
	$(CXX) $^ -o $(EXEC) $(LDFLAGS)

$(OBJDIR)/%.o : %.cpp
	$(CXX) -c $< -o $@ $(CXXFLAGS)
