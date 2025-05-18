#include "gertru.h"

void	handler(int signal)
{
	unsigned char	c_signal;

	c_signal = 130;
	if (signal == SIGINT)
	{
		rl_on_new_line();
		rl_replace_line("", 1);
		ioctl(STDIN_FILENO, TIOCSTI, "\n");
		g_exit_status = g_exit_status & 0;
        g_exit_status = g_exit_status | c_signal;
	}
}
	// else if (signal == SIGQUIT)
	// {
	// 	rl_on_new_line();
	// 	rl_replace_line("", 1);
	// 	ioctl(STDIN_FILENO, TIOCSTI, "\n");
	// 	g_exit_status = 131;
	// }
// 	else if (signal == SIGTERM)
	// {
	// 	rl_on_new_line();
	// 	rl_replace_line("", 1);
	// 	ioctl(STDIN_FILENO, TIOCSTI, "\n");
	// 	g_exit_status = 143;
	// }
//}