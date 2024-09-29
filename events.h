void on_sidebarbutton_clicker(GtkWidget *widget, gpointer data)
{
	gint button_id = GPOINTER_TO_INT(data);
	gchar *scontext = "";
	gint isxdgfolder = 1;

	switch (button_id)
	{
		case 0:
			scontext = "Menu";
			isxdgfolder = 0;
			break;
		case 1:
			scontext = usercmd;
			isxdgfolder = 0;
			break;
		case 2:
			scontext = "DOCUMENTS";
			break;
		case 3:
			scontext = "DOWNLOAD";
			break;
		case 4:
			scontext = "MUSIC";
			break;
		case 5:
			scontext = "PICTURES";
			break;
		case 6:
			scontext = "VIDEOS";
			break;
		case 7:
			scontext = settingscmd;
			isxdgfolder = 0;
			break;
		default:
			scontext = "Unknown";
			break;
	}

	if (isxdgfolder)
	{
		gchar command[512];
		snprintf(command, sizeof(command), "xdg-open $(xdg-user-dir %s)", scontext);
		execute_command(widget, command);
	}
	else
	{
		execute_command(widget, scontext);
	}
}