DIR_CLIENT	=	ft_client/
DIR_SERVER	=	ft_server/
DIR_BONUS	=	bonus/

NAME_CLIENT = client
NAME_SERVER = server

CLIENT = $(addprefix ../, $(NAME_CLIENT))
SERVER = $(addprefix ../, $(NAME_SERVER))

.PHONY: all
all:
	$(MAKE) -C $(DIR_CLIENT) all NAME=$(CLIENT)
	$(MAKE) -C $(DIR_SERVER) all NAME=$(SERVER)

$(NAME):
	$(MAKE) -C $(DIR_CLIENT) all NAME=$(CLIENT)
	$(MAKE) -C $(DIR_SERVER) all NAME=$(SERVER)

.PHONY: clean
clean:
	$(MAKE) -C $(DIR_CLIENT) clean
	$(MAKE) -C $(DIR_SERVER) clean

.PHONY: fclean
fclean:
	$(MAKE) -C $(DIR_CLIENT) fclean NAME=$(CLIENT)
	$(MAKE) -C $(DIR_SERVER) fclean NAME=$(SERVER)

.PHONY: re
re:
	$(MAKE) -C $(DIR_CLIENT) re NAME=$(CLIENT)
	$(MAKE) -C $(DIR_SERVER) re NAME=$(SERVER)

.PHONY: bonus
bonus:
	$(MAKE) all
