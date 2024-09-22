#include "gwmenu.h"
int main(int argc, char *argv[]) 
{
	home_dir = getenv("HOME");

	for (int i = 1; i < argc; i++)
	{
		sgcfg = strcmp(argv[i], "--cfg") == 0;
	}

	readconf();
	gtk_init(&argc, &argv);

	create_window();
}