NAME			=	server

SRCS			=	server.c \
					utils.c

DIR_INCS		=	./
DIR_BUILD		=	.build/
OBJS			=	$(patsubst %.c, $(DIR_BUILD)%.o, $(SRCS))
DEPS			=	$(patsubst %.c, $(DIR_BUILD)%.d, $(SRCS))
DEPS_FLAGS		=	-MMD -MP
CFLAGS			=	-Wall -Wextra -Werror
RM				=	rm -rf

DIR_LIBFT		=	../libft/
NAME_LIBFT		=	libft.a
LIBFT			=	$(addprefix $(DIR_LIBFT), $(NAME_LIBFT))

.PHONY: all
all: $(NAME)

$(NAME): $(LIBFT) $(OBJS)
		$(CC) $(CFLAGS) -o $(NAME) $(OBJS) -L $(DIR_LIBFT) -lft

$(LIBFT): FORCE
	$(MAKE) -C $(DIR_LIBFT) NAME=$(NAME_LIBFT)

.PHONY: clean
clean:
		$(MAKE) -C $(DIR_LIBFT) clean
		$(RM) $(DIR_BUILD)

.PHONY: fclean
fclean: clean
		$(MAKE) -C $(DIR_LIBFT) fclean NAME=$(NAME_LIBFT)
		rm -f $(NAME)

.PHONY: re
re: fclean
	$(MAKE) all

-include $(DEPS)

$(DIR_BUILD)%.o: %.c
		mkdir -p $(shell dirname $@)
		$(CC) $(CFLAGS) $(DEPS_FLAGS) -I $(DIR_INCS) -c $< -o $@

.PHONY: FORCE
FORCE:
