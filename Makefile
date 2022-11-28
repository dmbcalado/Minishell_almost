# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dmendonc <dmendonc@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/08/16 20:21:37 by anfreire          #+#    #+#              #
#    Updated: 2022/11/28 15:50:21 by dmendonc         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

SRCS = $(wildcard ./srcs/parsing/*.c) $(wildcard ./gnl/*.c) $(wildcard ./srcs/redirections/*.c) $(wildcard ./srcs/frees/*.c) $(wildcard ./srcs/builtins/*.c) $(wildcard ./srcs/env/*.c) $(wildcard ./srcs/signals/*.c) $(wildcard ./srcs/commands/*.c) $(wildcard ./srcs/*.c) $(wildcard ./srcs/utils/*.c) $(wildcard ./libft/*.c)

OBJS = $(SRCS:.c=.o)

CFLAGS		= -g -Wall -Wextra -Werror -lreadline -ltinfo -fsanitize=address

all	:	$(NAME)


$(NAME)	:	$(OBJS)
		@stty -ctlecho
# 	|stty -ctlecho : silenciar input de ctrl
#	|-->reverter : stty -a
		@gcc -o $(NAME) $(OBJS) $(CFLAGS)
		@echo	""
		@echo	"$$ ./minishell && Object Files Generated"
		@echo	""
		@echo	""
		@echo	""
		@echo  "\e[34m           :::   :::   ::::::::::: ::::    ::: ::::::::::: ::::::::  :::    ::: :::::::::: :::        :::	"
		@echo  "         :+:+: :+:+:      :+:     :+:+:   :+:     :+:    :+:    :+: :+:    :+: :+:        :+:        :+:  "
		@echo  "       +:+ +:+:+ +:+     +:+     :+:+:+  +:+     +:+    +:+        +:+    +:+ +:+        +:+        +:+   "
		@echo  "      +#+  +:+  +#+     +#+     +#+ +:+ +#+     +#+    +#++:++#++ +#++:++#++ +#++:++#   +#+        +#+    "
		@echo  "     +#+       +#+     +#+     +#+  +#+#+#     +#+           +#+ +#+    +#+ +#+        +#+        +#+     "
		@echo  "    #+#       #+#     #+#     #+#   #+#+#     #+#    #+#    #+# #+#    #+# #+#        #+#        #+#      "
		@echo  "   ###       ### ########### ###    #### ########### ########  ###    ### ########## ########## ##########"
		@echo  " "
		@echo  "\e[32mVersion : 1.0.1"
		@echo  " "
		@echo  "\e[36mThis program replicates the behavior of the bash shell. runs commands, redirections and has some builtin commands."
		@echo  "Runs commands that already exist in the operating system (some we built too), by using parallel processing (forks)"
		@echo  "and the redirections run exactly like in the bash hierarchy. You're able to fully check the objectives on this project "
		@echo  "by checking the file subject.pdf."
		@echo  " "
		@echo  "\e[33mSo we hope you enjoy going through this shell half as much as we enjoyed making it for you,"
		@echo  "because we had a ball."
		@echo  " "
		@echo  "\e[32mnow run ./minishell and welcome!"
		@echo  " "
		@echo  "\e[0mWork made by:"
		@echo  "Diogo MBM Calado and Andre Freire, from 42 Lisbon."
		@echo  " "
		@echo  " "
		@echo  " "
		
%.o	:	%.c
	@gcc $(CFLAGS) -c $^ -I./ -o $@
	

clean	:
	@rm -f $(OBJS)
	@echo	""
	@echo	"$$ Object Files Deleted"
	@echo	""
		
fclean	:	clean
	@rm -f $(NAME)
	@echo	""
	@echo	"$$ ./minishell Deleted"
	@echo	""

re			:	fclean all

.PHONY		:	all clean fclean re bonus