CC = gcc
CFLAGS = -g -std=gnu89 \
	-Wall -Wshadow -Wcast-align -Wpointer-arith \
	-Wwrite-strings -Wundef -Wredundant-decls -Wextra -Wno-sign-compare \
	-Wformat-security -Wno-pointer-sign -Werror-implicit-function-declaration \
	-Wno-unused-parameter
OBJDIR = ./obj/

HDR = $(wildcard *.h)

# common files (usually required by all modules)
SRC_CMN = util.c
OBJ_CMN	= $(SRC_CMN:%.c=$(OBJDIR)%.o)

# get .o's for the caller and concats with common .o's
getobjs = $(OBJ_CMN) $(1:%.c=$(OBJDIR)%.o)

# singly linked list
SRC_SLL = sll.c
OBJ_SLL = $(call getobjs, $(SRC_SLL))

# hash table (chaining)
SRC_HASH = hash.c $(SRC_SLL)
OBJ_HASH = $(call getobjs, $(SRC_HASH))

# stack
SRC_STACK = stack.c $(SRC_SLL)
OBJ_STACK = $(call getobjs, $(SRC_STACK))

# queue
SRC_QUEUE = queue.c $(SRC_SLL)
OBJ_QUEUE = $(call getobjs, $(SRC_QUEUE))

# tpool (thread pool)
SRC_TPOOL = tpool.c $(SRC_QUEUE)
OBJ_TPOOL = $(call getobjs, $(SRC_TPOOL))

# test
SRC_TEST = test.c $(SRC_TPOOL)
OBJ_TEST = $(call getobjs, $(SRC_TEST))

# extra, TODO
SRC_EXTRA = lcs.c
OBJ_EXTRA = $(call getobjs, $(SRC_EXTRA))


cmd_cc = $(CC) $(CFLAGS) $(1) $^ -o $@

.phony: all
all: test 

extra: $(OBJ_EXTRA)
	$(call cmd_cc)

tpool:	$(OBJ_TPOOL)
	$(call cmd_cc, -lpthread)

sll	:	$(OBJ_SLL)
	$(call cmd_cc)

stack : $(OBJ_STACK)
	$(call cmd_cc)

hash : $(OBJ_HASH)
	$(call cmd_cc)

queue : $(OBJ_QUEUE)
	$(call cmd_cc)

test : $(OBJ_TEST)
	$(call cmd_cc, -lpthread)


$(OBJDIR)%.o : %.c
	@[[ -d $(OBJDIR) ]] || mkdir $(OBJDIR)
	$(CC) $(CFLAGS) -MMD -c $< -o $@

-include $(OBJDIR)/*.d
