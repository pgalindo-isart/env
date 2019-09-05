CFLAGS=-Wall -O0 -g -MMD -Iinclude

GAME=breakout

# Disable implicit rules and variables
MAKEFLAGS+=--no-builtin-rules --no-builtin-variables

.PHONY: all clean run tags

all: $(GAME)

# --------------------------------------------- 
# ----------------- GAME ---------------------- 
$(GAME): private LDLIBS+=-lmingw32 -lSDL2main -lSDL2

GAME_OBJS=src/main.o src/game.o src/utils.o src/localization.o \
		  src/font.o src/texture.o src/breakout_logic.o

$(GAME): $(GAME_OBJS)
	$(CC) -o $@ $(LDFLAGS) $^ $(LDLIBS)

# Order-only rule (|) so if src/loc.inc is missing
# it will be generated before everything
$(GAME_OBJS): | src/loc.inc

run: $(GAME)
	./$(GAME)
# --------------------------------------------- 
# ------------- LOCALIZATION TOOL ------------- 
src/loc.inc: loc_gen $(wildcard assets/loc_*.txt)
	./$^ | sort | uniq > $@ 

LOC_OBJS=src/loc_gen.o

loc_gen: $(LOC_OBJS)
	$(CC) -o $@ $(LDFLAGS) $^ $(LDLIBS)
# --------------------------------------------- 

# Include generated dependency files
-include $(GAME_OBJS:.o=.d) $(LOC_OBJS:.o=.d)

# Default rule to build object files
%.o: %.c
	$(CC) -o $@ -c $< $(CFLAGS)

clean:
	rm -rf $(GAME) $(GAME_OBJS) $(GAME_OBJS:.o=.d)
	rm -rf loc_gen src/loc.inc $(LOC_OBJS) $(LOC_OBJS:.o=.d)

tags:
	ctags -R .
