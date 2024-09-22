void exit_window();

void updateconf(GtkButton *button, gpointer user_data) 
{
	int reset = GPOINTER_TO_INT(user_data);

	FILE *fp = fopen(config_file_path, "w+");
	if (fp == NULL)
	{
		perror("Failed to open config file");
		exit(EXIT_FAILURE);
	}

	if (reset)
	{
	dialog = gtk_message_dialog_new(NULL, GTK_DIALOG_MODAL, GTK_MESSAGE_QUESTION, GTK_BUTTONS_OK_CANCEL, "Are you sure you want to restore SGLauncher settings as default?");
		gtk_window_set_position(GTK_WINDOW(dialog), GTK_WIN_POS_CENTER);
		gtk_window_set_title(GTK_WINDOW(dialog), "Confirmation");
		gtk_dialog_set_default_response(GTK_DIALOG(dialog), GTK_RESPONSE_OK);
		gint result = gtk_dialog_run(GTK_DIALOG(dialog));
		if (result == GTK_RESPONSE_OK)
		{
			fprintf(fp, "[GWMenu Configuration File]\n");
			fprintf(fp, "iconsize=16\n");
			fprintf(fp, "showuser=1\n");
			fprintf(fp, "showsettings=1\n");
			fprintf(fp, "showmusic=1\n");
			fprintf(fp, "showdoc=1\n");
			fprintf(fp, "showdwn=1\n");
			fprintf(fp, "showimg=1\n");
			fprintf(fp, "showvid=1\n");
			fprintf(fp, "showsession=1\n");
			fprintf(fp, "showsessionpwroff=1\n");
			fprintf(fp, "showsessionreboot=1\n");
			fprintf(fp, "showsessionhibernate=1\n");
			fprintf(fp, "showsessionsuspend=1\n");
			fprintf(fp, "showsessionlogout=1\n");
			fprintf(fp, "showsessionlockscreen=1\n");
			fprintf(fp, "pwroffcmd=systemctl poweroff\n");
			fprintf(fp, "rebootcmd=systemctl reboot\n");
			fprintf(fp, "hibernatecmd=systemctl hibernate\n");
			fprintf(fp, "suspendcmd=systemctl suspend\n");
			fprintf(fp, "logoutcmd=systemctl terminate-user $USER\n");
			fprintf(fp, "lockscreencmd=xset s activate\n");
			fprintf(fp, "settingscmd=sgsettings\n");
			fprintf(fp, "usercmd=sgusers\n");
			fprintf(fp, "defheight=333\n");
			fprintf(fp, "showcalc=1\n");
			fprintf(fp, "showscientific=0\n");
			//fprintf(fp, "exitwhenunfocused=1\n");
		}
		else
		{
			printf("Operation cancelled.\n");
		}
		gtk_widget_destroy(dialog);
	}
	else
	{
		iconsize = atoi(gtk_entry_get_text(GTK_ENTRY(giconsize)));
		defheight = atoi(gtk_entry_get_text(GTK_ENTRY(gdefheight)));
		showuser = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(gshowuser));
		showmusic = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(gshowmusic));
		showsettings = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(gshowsettings));
		showdoc = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(gshowdoc));
		showimg = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(gshowimg));
		showvid = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(gshowvid));
		showsession = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(gshowsession));
			showsessionpwroff = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(gshowsessionpwroff));
			showsessionreboot = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(gshowsessionreboot));
			showsessionhibernate = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(gshowsessionhibernate));
			showsessionsuspend = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(gshowsessionsuspend));
			showsessionlogout = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(gshowsessionlogout));
			showsessionlockscreen = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(gshowsessionlockscreen));

		strncpy(pwroffcmd, gtk_entry_get_text(GTK_ENTRY(gpwroffcmd)), sizeof(pwroffcmd) - 1);
		strncpy(rebootcmd, gtk_entry_get_text(GTK_ENTRY(grebootcmd)), sizeof(rebootcmd) - 1);
		strncpy(hibernatecmd, gtk_entry_get_text(GTK_ENTRY(ghibernatecmd)), sizeof(hibernatecmd) - 1);
		strncpy(suspendcmd, gtk_entry_get_text(GTK_ENTRY(gsuspendcmd)), sizeof(suspendcmd) - 1);
		strncpy(logoutcmd, gtk_entry_get_text(GTK_ENTRY(glogoutcmd)), sizeof(logoutcmd) - 1);
		strncpy(lockscreencmd, gtk_entry_get_text(GTK_ENTRY(glockscreencmd)), sizeof(glockscreencmd) - 1);
		strncpy(settingscmd, gtk_entry_get_text(GTK_ENTRY(gsettingscmd)), sizeof(settingscmd) - 1);
		strncpy(usercmd, gtk_entry_get_text(GTK_ENTRY(gusercmd)), sizeof(usercmd) - 1);

		//gexitwhenunfocused = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(wexitwhenunfocused));

			fprintf(fp, "[GWMenu Configuration File]\n");
			fprintf(fp, "iconsize=%d\n", iconsize);
			fprintf(fp, "showuser=%d\n", showuser);
			fprintf(fp, "showsettings=%d\n", showsettings);
			fprintf(fp, "showmusic=%d\n", showmusic);
			fprintf(fp, "showdoc=%d\n", showdoc);
			fprintf(fp, "showdwn=%d\n", showdwn);
			fprintf(fp, "showimg=%d\n", showimg);
			fprintf(fp, "showvid=%d\n", showvid);
			fprintf(fp, "showsession=%d\n", showsession);
			fprintf(fp, "showsessionpwroff=%d\n", showsessionpwroff);
			fprintf(fp, "showsessionreboot=%d\n", showsessionreboot);
			fprintf(fp, "showsessionhibernate=%d\n", showsessionhibernate);
			fprintf(fp, "showsessionsuspend=%d\n", showsessionsuspend);
			fprintf(fp, "showsessionlogout=%d\n", showsessionlogout);
			fprintf(fp, "showsessionlockscreen=%d\n", showsessionlockscreen);
			fprintf(fp, "pwroffcmd=%s\n", pwroffcmd);
			fprintf(fp, "rebootcmd=%s\n", rebootcmd);
			fprintf(fp, "hibernatecmd=%s\n", hibernatecmd);
			fprintf(fp, "suspendcmd=%s\n", suspendcmd);
			fprintf(fp, "logoutcmd=%s\n", logoutcmd);
			fprintf(fp, "lockscreencmd=%s\n", lockscreencmd);
			fprintf(fp, "settingscmd=%s\n", settingscmd);
			fprintf(fp, "usercmd=%s\n", usercmd);
			fprintf(fp, "defheight=%d\n", defheight);
			fprintf(fp, "showcalc=%d\n", showcalc);
			fprintf(fp, "showscientific=%d\n", showscientific);
		//fprintf(fp, "exitwhenunfocused=%d\n", gexitwhenunfocused);
	}
	fclose(fp);
	restarting = 1;
	exit_window();
}

void readconf()
{
	// READ THE CONF
	if (home_dir == NULL)
	{
		nohome = 1;
		return;
	}
	else
	{
		snprintf(config_file_path, sizeof(config_file_path), "%s/.config/gwmenu.conf", home_dir);
		FILE *file = fopen(config_file_path, "r");

		char line[ML];
		while (fgets(line, ML, file) != NULL)
		{
			char *name = strtok(line, "=");
			char *value_str = strtok(NULL, "=");

			if (name != NULL && value_str != NULL)
			{
				value_str[strcspn(value_str, "\n")] = '\0';

				if (strcmp(name, "iconsize") == 0) 
					iconsize = atoi(value_str);
				else if (strcmp(name, "showuser") == 0) 
					showuser = atoi(value_str);
				else if (strcmp(name, "showdoc") == 0) 
					showdoc = atoi(value_str);
				else if (strcmp(name, "showdwn") == 0) 
					showdwn = atoi(value_str);
				else if (strcmp(name, "showimg") == 0) 
					showimg = atoi(value_str);
				else if (strcmp(name, "showvid") == 0) 
					showvid = atoi(value_str);
				else if (strcmp(name, "showsettings") == 0) 
					showsettings = atoi(value_str);
				else if (strcmp(name, "showsession") == 0) 
					showsession = atoi(value_str);
					else if (strcmp(name, "showsessionpwroff") == 0) 
						showsessionpwroff = atoi(value_str);
					else if (strcmp(name, "showsessionreboot") == 0) 
						showsessionreboot = atoi(value_str);
					else if (strcmp(name, "showsessionhibernate") == 0) 
						showsessionhibernate = atoi(value_str);
					else if (strcmp(name, "showsessionsuspend") == 0) 
						showsessionsuspend = atoi(value_str);
					else if (strcmp(name, "showsessionlogout") == 0) 
						showsessionlogout = atoi(value_str);
					else if (strcmp(name, "showsessionlockscreen") == 0) 
						showsessionlockscreen = atoi(value_str);

				else if (strcmp(name, "pwroffcmd") == 0) 
					strncpy(pwroffcmd, value_str, sizeof(pwroffcmd) - 1);
				else if (strcmp(name, "rebootcmd") == 0) 
					strncpy(rebootcmd, value_str, sizeof(rebootcmd) - 1);
				else if (strcmp(name, "hibernatecmd") == 0) 
					strncpy(hibernatecmd, value_str, sizeof(hibernatecmd) - 1);
				else if (strcmp(name, "suspendcmd") == 0) 
					strncpy(suspendcmd, value_str, sizeof(suspendcmd) - 1);
				else if (strcmp(name, "logoutcmd") == 0) 
					strncpy(logoutcmd, value_str, sizeof(logoutcmd) - 1);
				else if (strcmp(name, "lockscreencmd") == 0) 
					strncpy(lockscreencmd, value_str, sizeof(lockscreencmd) - 1);
				else if (strcmp(name, "settingscmd") == 0) 
					strncpy(settingscmd, value_str, sizeof(settingscmd) - 1);
				else if (strcmp(name, "usercmd") == 0) 
					strncpy(usercmd, value_str, sizeof(usercmd) - 1);

				else if (strcmp(name, "defheight") == 0) 
					defheight = atoi(value_str);
				else if (strcmp(name, "showcalc") == 0) 
					showcalc = atoi(value_str);
				else if (strcmp(name, "showscientific") == 0) 
					showscientific = atoi(value_str);
				else if (strcmp(name, "exitwhenunfocused") == 0) 
					exitwhenunfocused = atoi(value_str);
			}
		}
		fclose(file);

		if (pwroffcmd[0] == '\0')
		{
			strncpy(pwroffcmd, "systemctl poweroff", sizeof(pwroffcmd) - 1);
		}
		if (rebootcmd[0] == '\0')
		{
			strncpy(rebootcmd, "systemctl reboot", sizeof(rebootcmd) - 1);
		}
		if (hibernatecmd[0] == '\0')
		{
			strncpy(hibernatecmd, "systemctl hibernate", sizeof(hibernatecmd) - 1);
		}
		if (suspendcmd[0] == '\0')
		{
			strncpy(suspendcmd, "systemctl suspend", sizeof(suspendcmd) - 1);
		}
		if (logoutcmd[0] == '\0')
		{
			strncpy(logoutcmd, "systemctl terminate-user $USER", sizeof(logoutcmd) - 1);
		}
		if (lockscreencmd[0] == '\0')
		{
			strncpy(lockscreencmd, "xset s activate", sizeof(lockscreencmd) - 1);
		}
		if (settingscmd[0] == '\0')
		{
			strncpy(settingscmd, "sgsettings", sizeof(settingscmd) - 1);
		}
		if (usercmd[0] == '\0')
		{
			strncpy(usercmd, "sgusers", sizeof(usercmd) - 1);
		}
	}
}