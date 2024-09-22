#ifndef DEBUG_H
# define DEBUG_H

/*		Debug - start		*/
# define RED "\033[0;31m"
# define GREEN "\033[0;32m"
# define YELLOW "\033[0;33m"
# define BLUE "\033[0;34m"
# define MAGENTA "\033[0;35m"
# define CYAN "\033[0;36m"
# define UKN "\033[1;30m"
# define WHITE "\033[1;97m"
# define RESET "\033[0m"

# define TRUE GREEN"true"RESET
# define FALSE RED"false"RESET
/*		Debug - end		*/


/*		TO BE REMOVED			*/
void			print_content(void *content);
void			display_token(void *content);
void			leaks_func(void);
void			display_command(void *content);

#endif