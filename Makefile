##
## EPITECH PROJECT, 2018
## Plazza
## File description:
## Makefile
##

NAME		=	plazza
CC			=	g++ -o
RM			=	@rm -f

SRCDIR		=	src
OBJDIR		=	build

LIST		=	main_cli	\
				plazza		\
				threadz		\
				slave		\
				slavePool	\
				threadzPool

LIST_UI		=	main_gui	\
				GuiManager

SORTED_UI	=	(sort $(LIST_UI))
SORTED		=	$(sort $(LIST))

OBJS_UI		=	$(SORTED_UI:%=$(OBJDIR)/%.o)
OBJS		=	$(SORTED:%=$(OBJDIR)/%.o)

CPPFLAGS 	=	-I./src
CPPFLAGS 	+=	-W -Wall -Wextra -g -std=c++11 -std=gnu++11
LDFLAGS		=	-L./lib/ -lpthread -I./src

all: 	 $(NAME)

ui:	$(NAME_UI)

$(NAME_UI):	$(OBJS_UI)
		@$(CC) $(NAME) $(OBJS_UI) $(LDFLAGS) -lsfml-graphics
		@printf "[\033[0;36mbuilt\033[0m] % 32s\n" $(NAME) | tr ' ' '.'

$(NAME): $(OBJS)
	@$(CC) $(NAME) $(OBJS) $(LDFLAGS)
	@printf "[\033[0;36mbuilt\033[0m] % 32s\n" $(NAME) | tr ' ' '.'

$(OBJS):	$(OBJDIR)

$(OBJS_UI):	$(OBJDIR_UI)

$(OBJDIR_UI):
	@mkdir -p $(OBJDIR_UI)

$(OBJDIR):
	@mkdir -p $(OBJDIR)

$(OBJDIR)/%.o:	$(SRCDIR)/%.cpp
	@$(CC) $(CPPFLAGS) -c -o $@ $<
	@printf "[\033[33;1mcompile\033[0m] % 30s\n" $@ | tr ' ' '.'

$(OBJDIR_UI)/%.o:	$(SRCDIR_UI)/%.cpp
	@$(CC) $(CPPFLAGS) -c -o $@ $<
	@printf "[\033[33;1mcompile\033[0m] % 30s\n" $@ | tr ' ' '.'

clean:
	$(RM) $(OBJS)
	@rm -rf $(OBJDIR) $(OBJDIR_UI)
	@printf "[\033[0;31mdeleted\033[0m] % 30s\n" $(OBJS) | tr ' ' '.'

fclean: clean
	$(RM) $(NAME)
	@printf "[\033[0;31mdeleted\033[0m] % 30s\n" $(NAME) | tr ' ' '.'

re: fclean all

.PHONY: all clean fclean re
