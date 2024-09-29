void on_webcombo_changed(GtkComboBox *webcombo, gpointer user_data)
{
	active_text = gtk_combo_box_text_get_active_text(GTK_COMBO_BOX_TEXT(webcombo));
	GtkWidget *webctm = GTK_WIDGET(user_data);
	//GtkWidget *webctmlb = GTK_WIDGET(g_object_get_data(G_OBJECT(webctm), "webctmlb"));

	if (g_strcmp0(active_text, "Custom") != 0)
	{
		gtk_widget_hide(webctm);
		gtk_widget_hide(weblabel);
	}
	else
	{
		gtk_widget_show(webctm);
		gtk_widget_show(weblabel);
	}

	g_free((gpointer) active_text);
}

void on_dialog_destroy(GtkWidget *widget, gpointer data)
{
	callconfig = 0;
}

void showcfg()
{
	callconfig = 1;
	dialog = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title(GTK_WINDOW(dialog), "Settings - GWMenu");
	gtk_container_set_border_width(GTK_CONTAINER(dialog), 10);
	gtk_widget_set_size_request(dialog, 400, 300);
	g_signal_connect(dialog, "destroy", G_CALLBACK(gtk_main_quit), NULL);
	theme = gtk_icon_theme_get_default();
	info = gtk_icon_theme_lookup_icon(theme, "menulibre", 48, 0);
	if (info != NULL)
	{
		icon = gtk_icon_info_load_icon(info, NULL);
		gtk_window_set_icon(GTK_WINDOW(dialog), icon);
		g_object_unref(icon);
		g_object_unref(info);
	}

	defbtn = gtk_button_new_with_label("Default");
	applybtn  = gtk_button_new_with_label("Apply");

	GtkWidget *applybox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 1);
		gtk_box_pack_end(GTK_BOX(applybox), applybtn, FALSE, FALSE, 2);
		gtk_box_pack_end(GTK_BOX(applybox), defbtn, FALSE, FALSE, 2);
	g_signal_connect(applybtn, "clicked", G_CALLBACK(updateconf), GINT_TO_POINTER(0));
	g_signal_connect(defbtn, "clicked", G_CALLBACK(updateconf), GINT_TO_POINTER(1));

	gtk_window_set_position(GTK_WINDOW(dialog), GTK_WIN_POS_CENTER);

		gdefwidth = gtk_entry_new();
		gdefheight = gtk_entry_new();
		giconsize = gtk_entry_new();

		gshowdoc = gtk_check_button_new();
		gshowdwn = gtk_check_button_new();
		gshowmusic = gtk_check_button_new();
		gshowimg = gtk_check_button_new();
		gshowvid = gtk_check_button_new();
		gshowsettings = gtk_check_button_new();
		gshowuser = gtk_check_button_new();
		gshowsession = gtk_check_button_new();
			gshowsessionhibernate = gtk_check_button_new();
			gshowsessionlockscreen = gtk_check_button_new();
			gshowsessionlogout = gtk_check_button_new();
			gshowsessionpwroff = gtk_check_button_new();
			gshowsessionreboot = gtk_check_button_new();
			gshowsessionsuspend = gtk_check_button_new();

		gusercmd = gtk_entry_new();
		gsettingscmd = gtk_entry_new();
		ghibernatecmd = gtk_entry_new();
		glockscreencmd = gtk_entry_new();
		glogoutcmd = gtk_entry_new();
		gpwroffcmd = gtk_entry_new();
		grebootcmd = gtk_entry_new();
		gsuspendcmd = gtk_entry_new();

	notebook = gtk_notebook_new();

	cfggrid0 = gtk_grid_new();
		gtk_grid_attach(GTK_GRID(cfggrid0), gtk_label_new("Icon Size"), 0, 0, 1, 1);
			gtk_grid_attach(GTK_GRID(cfggrid0), giconsize, 1, 0, 1, 1);
		gtk_grid_attach(GTK_GRID(cfggrid0), gtk_label_new("Menu Width"), 0, 1, 1, 1);
			gtk_grid_attach(GTK_GRID(cfggrid0), gdefwidth, 1, 1, 1, 1);
		gtk_grid_attach(GTK_GRID(cfggrid0), gtk_label_new("Menu height"), 0, 2, 1, 1);
			gtk_grid_attach(GTK_GRID(cfggrid0), gdefheight, 1, 2, 1, 1);

		gchar ciconsize[32];
		gchar cdefwidth[32];
		gchar cdefheight[32];
		g_snprintf(ciconsize, sizeof(ciconsize), "%d", iconsize);
		g_snprintf(cdefwidth, sizeof(cdefwidth), "%d", defwidth);
		g_snprintf(cdefheight, sizeof(cdefheight), "%d", defheight);

		gtk_entry_set_text(GTK_ENTRY(giconsize), ciconsize);
		gtk_entry_set_text(GTK_ENTRY(gdefwidth), cdefwidth);
		gtk_entry_set_text(GTK_ENTRY(gdefheight), cdefheight);

	gtk_grid_set_column_homogeneous(GTK_GRID(cfggrid0), TRUE);
	gtk_notebook_append_page(GTK_NOTEBOOK(notebook), cfggrid0, gtk_label_new("Appearance"));


	cfggrid1 = gtk_grid_new();
		gtk_grid_attach(GTK_GRID(cfggrid1), gtk_label_new("Show Documents"), 0, 0, 1, 1);
			gtk_grid_attach(GTK_GRID(cfggrid1), gshowdoc, 1, 0, 1, 1);
		gtk_grid_attach(GTK_GRID(cfggrid1), gtk_label_new("Show Downloads"), 0, 1, 1, 1);
			gtk_grid_attach(GTK_GRID(cfggrid1), gshowdwn, 1, 1, 1, 1);
		gtk_grid_attach(GTK_GRID(cfggrid1), gtk_label_new("Show Music"), 0, 2, 1, 1);
			gtk_grid_attach(GTK_GRID(cfggrid1), gshowmusic, 1, 2, 1, 1);
		gtk_grid_attach(GTK_GRID(cfggrid1), gtk_label_new("Show Pictures"), 0, 3, 1, 1);
			gtk_grid_attach(GTK_GRID(cfggrid1), gshowimg, 1, 3, 1, 1);
		gtk_grid_attach(GTK_GRID(cfggrid1), gtk_label_new("Show Videos"), 0, 4, 1, 1);
			gtk_grid_attach(GTK_GRID(cfggrid1), gshowvid, 1, 4, 1, 1);
		gtk_grid_attach(GTK_GRID(cfggrid1), gtk_label_new("Show User"), 0, 5, 1, 1);
			gtk_grid_attach(GTK_GRID(cfggrid1), gshowuser, 1, 5, 1, 1);
		gtk_grid_attach(GTK_GRID(cfggrid1), gtk_label_new("Show Settings"), 0, 6, 1, 1);
			gtk_grid_attach(GTK_GRID(cfggrid1), gshowsettings, 1, 6, 1, 1);
		gtk_grid_attach(GTK_GRID(cfggrid1), gtk_label_new("Show Session"), 0, 7, 1, 1);
			gtk_grid_attach(GTK_GRID(cfggrid1), gshowsession, 1, 7, 1, 1);
			gtk_grid_attach(GTK_GRID(cfggrid1), gtk_label_new("Show Log out"), 0, 8, 1, 1);
				gtk_grid_attach(GTK_GRID(cfggrid1), gshowsessionlogout, 1, 8, 1, 1);
			gtk_grid_attach(GTK_GRID(cfggrid1), gtk_label_new("Show Lock Screen"), 0, 9, 1, 1);
				gtk_grid_attach(GTK_GRID(cfggrid1), gshowsessionlockscreen, 1, 9, 1, 1);
			gtk_grid_attach(GTK_GRID(cfggrid1), gtk_label_new("Show Power Off"), 0, 10, 1, 1);
				gtk_grid_attach(GTK_GRID(cfggrid1), gshowsessionpwroff, 1, 10, 1, 1);
			gtk_grid_attach(GTK_GRID(cfggrid1), gtk_label_new("Show Reboot"), 0, 11, 1, 1);
				gtk_grid_attach(GTK_GRID(cfggrid1), gshowsessionreboot, 1, 11, 1, 1);
			gtk_grid_attach(GTK_GRID(cfggrid1), gtk_label_new("Show Suspend "), 0, 12, 1, 1);
				gtk_grid_attach(GTK_GRID(cfggrid1), gshowsessionsuspend, 1, 12, 1, 1);
			gtk_grid_attach(GTK_GRID(cfggrid1), gtk_label_new("Show Hibernate"), 0, 13, 1, 1);
				gtk_grid_attach(GTK_GRID(cfggrid1), gshowsessionhibernate, 1, 13, 1, 1);

			gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(gshowdoc), showdoc);
			gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(gshowdwn), showdwn);
			gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(gshowmusic), showmusic);
			gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(gshowimg), showimg);
			gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(gshowvid), showvid);
			gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(gshowuser), showuser);
			gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(gshowsettings), showsettings);
			gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(gshowsession), showsession);
				gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(gshowsessionlogout), showsessionlogout);
				gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(gshowsessionlockscreen), showsessionlockscreen);
				gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(gshowsessionpwroff), showsessionpwroff);
				gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(gshowsessionreboot), showsessionreboot);
				gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(gshowsessionsuspend), showsessionsuspend);
				gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(gshowsessionhibernate), showsessionhibernate);

	gtk_grid_set_column_homogeneous(GTK_GRID(cfggrid1), TRUE);
	gtk_notebook_append_page(GTK_NOTEBOOK(notebook), cfggrid1, gtk_label_new("Elements"));

	cfggrid2 = gtk_grid_new();
		gtk_grid_attach(GTK_GRID(cfggrid2), gtk_label_new("User"), 0, 0, 1, 1);
			gtk_grid_attach(GTK_GRID(cfggrid2), gusercmd, 1, 0, 1, 1);
		gtk_grid_attach(GTK_GRID(cfggrid2), gtk_label_new("Settings"), 0, 1, 1, 1);
			gtk_grid_attach(GTK_GRID(cfggrid2), gsettingscmd, 1, 1, 1, 1);
		gtk_grid_attach(GTK_GRID(cfggrid2), gtk_label_new("Log Out"), 0, 2, 1, 1);
			gtk_grid_attach(GTK_GRID(cfggrid2), glogoutcmd, 1, 2, 1, 1);
		gtk_grid_attach(GTK_GRID(cfggrid2), gtk_label_new("Lock Screen"), 0, 3, 1, 1);
			gtk_grid_attach(GTK_GRID(cfggrid2), glockscreencmd, 1, 3, 1, 1);
		gtk_grid_attach(GTK_GRID(cfggrid2), gtk_label_new("Power Off"), 0, 4, 1, 1);
			gtk_grid_attach(GTK_GRID(cfggrid2), gpwroffcmd, 1, 4, 1, 1);
		gtk_grid_attach(GTK_GRID(cfggrid2), gtk_label_new("Reboot"), 0, 5, 1, 1);
			gtk_grid_attach(GTK_GRID(cfggrid2), grebootcmd, 1, 5, 1, 1);
		gtk_grid_attach(GTK_GRID(cfggrid2), gtk_label_new("Suspend"), 0, 6, 1, 1);
			gtk_grid_attach(GTK_GRID(cfggrid2), gsuspendcmd, 1, 6, 1, 1);
		gtk_grid_attach(GTK_GRID(cfggrid2), gtk_label_new("Hibernate"), 0, 7, 1, 1);
			gtk_grid_attach(GTK_GRID(cfggrid2), ghibernatecmd, 1, 7, 1, 1);


		gtk_entry_set_text(GTK_ENTRY(gusercmd), usercmd);
		gtk_entry_set_text(GTK_ENTRY(gsettingscmd), settingscmd);
		gtk_entry_set_text(GTK_ENTRY(glogoutcmd), logoutcmd);
		gtk_entry_set_text(GTK_ENTRY(glockscreencmd), lockscreencmd);
		gtk_entry_set_text(GTK_ENTRY(gpwroffcmd), pwroffcmd);
		gtk_entry_set_text(GTK_ENTRY(grebootcmd), rebootcmd);
		gtk_entry_set_text(GTK_ENTRY(gsuspendcmd), suspendcmd);
		gtk_entry_set_text(GTK_ENTRY(ghibernatecmd), hibernatecmd);

	gtk_grid_set_column_homogeneous(GTK_GRID(cfggrid2), TRUE);
	gtk_notebook_append_page(GTK_NOTEBOOK(notebook), cfggrid2, gtk_label_new("Commands"));

	confbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 1);

	gtk_box_pack_start(GTK_BOX(confbox), notebook, FALSE, FALSE, 2);
	gtk_box_pack_start(GTK_BOX(confbox), applybox, FALSE, FALSE, 2);

	gtk_container_add(GTK_CONTAINER(dialog), confbox);

	gtk_widget_show_all(dialog);
	g_signal_connect(dialog, "destroy", G_CALLBACK(on_dialog_destroy), NULL);

	gtk_main();
}