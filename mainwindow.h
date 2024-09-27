void create_window();

void exit_window()
{
	if (restarting)
	{
		gtk_widget_destroy(window);
		gtk_widget_destroy(dialog);
		restarting = 0;
		readconf();
		create_window();
	}
	else
	{
		gtk_main_quit();
		exit(0);
	}
}

void on_submenu_item_about_selected(GtkMenuItem *menuitem, gpointer userdata) 
{
	dialog = gtk_about_dialog_new();
		theme = gtk_icon_theme_get_default();
		info = gtk_icon_theme_lookup_icon(theme, iconame, 48, 0);
		if (info != NULL)
		{
			icon = gtk_icon_info_load_icon(info, NULL);
			gtk_window_set_icon(GTK_WINDOW(dialog), icon);
			g_object_unref(icon);
			g_object_unref(info);
		}
	gtk_about_dialog_set_program_name(GTK_ABOUT_DIALOG(dialog), "GWMenu");
	gtk_about_dialog_set_copyright(GTK_ABOUT_DIALOG(dialog), "Copyright © 2024 ItzSelenux");
	gtk_about_dialog_set_comments(GTK_ABOUT_DIALOG(dialog), "Windows 10 Menu-like clone in GTK");
	gtk_about_dialog_set_version(GTK_ABOUT_DIALOG(dialog), pver);
	gtk_about_dialog_set_website(GTK_ABOUT_DIALOG(dialog), "");
	gtk_about_dialog_set_website_label(GTK_ABOUT_DIALOG(dialog), "Project WebSite");
	gtk_about_dialog_set_license_type(GTK_ABOUT_DIALOG(dialog),GTK_LICENSE_GPL_3_0);
	gtk_about_dialog_set_logo_icon_name(GTK_ABOUT_DIALOG(dialog),iconame);
	gtk_window_set_position(GTK_WINDOW(dialog), GTK_WIN_POS_CENTER);
	gtk_dialog_run(GTK_DIALOG(dialog));
	gtk_widget_destroy(dialog);
}

void on_submenu_item_onlinehelp_selected(GtkMenuItem *menuitem, gpointer userdata) 
{

	dialog = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title(GTK_WINDOW(dialog), "Online Help - Confirmation");
	gtk_window_set_position(GTK_WINDOW(dialog), GTK_WIN_POS_CENTER);

	theme = gtk_icon_theme_get_default();
	info = gtk_icon_theme_lookup_icon(theme, "dialog-question", 48, GTK_ICON_LOOKUP_USE_BUILTIN);
	if (info != NULL)
	{
		icon = gtk_icon_info_load_icon(info, NULL);
		gtk_window_set_icon(GTK_WINDOW(dialog), icon);
		g_object_unref(icon);
		g_object_unref(info);
	}

	gtk_container_set_border_width(GTK_CONTAINER(dialog), 10);
	GtkWidget *vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
	gtk_container_add(GTK_CONTAINER(dialog), vbox);

	GtkWidget *question_label = gtk_label_new("Do you want to open this link?");
	GtkWidget *link_button = gtk_link_button_new_with_label("https://github.com/ItzSelenux/GWMenu/wiki",
		"https://github.com/ItzSelenux/GWMenu/wiki");

	gtk_box_pack_start(GTK_BOX(vbox), question_label, FALSE, FALSE, 0);
	gtk_box_pack_start(GTK_BOX(vbox), link_button, FALSE, FALSE, 0);

	gtk_widget_show_all(dialog);
}

void create_window()
{
	char local_app_dir[1024] = "";
	char profilepic[1024] = "";
	sprintf(local_app_dir, "%s/.local/share/applications", home_dir);
	sprintf(profilepic, "%s/.face", home_dir);
	app_dirs[2] = local_app_dir;

	listbox2 = gtk_list_box_new();
	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title(GTK_WINDOW(window), "GWMenu");
	//gtk_container_set_border_width(GTK_CONTAINER(window), 10);
	gtk_widget_set_size_request(window, 333, defheight);
	gtk_window_set_decorated(GTK_WINDOW(window), FALSE);
	gtk_window_set_skip_taskbar_hint(GTK_WINDOW(window), TRUE);
	gtk_window_set_skip_pager_hint(GTK_WINDOW(window), TRUE);
	g_signal_connect(window, "destroy", G_CALLBACK(exit_window), NULL);

	theme = gtk_icon_theme_get_default();
	info = gtk_icon_theme_lookup_icon(theme, "gwmenu", 48, 0);
	if (info != NULL)
	{
		icon = gtk_icon_info_load_icon(info, NULL);
		iconame="gwmenu";
		g_object_unref(info);
	}
	else
	{
		info = gtk_icon_theme_lookup_icon(theme, "menulibre", 48, 0);
		if (info != NULL) {
			icon = gtk_icon_info_load_icon(info, NULL);
			iconame="menulibre";
			g_object_unref(info);
		}
	}

	if (icon != NULL) {
		gtk_window_set_icon(GTK_WINDOW(window), icon);
		g_object_unref(icon);
	}

	entry = gtk_entry_new();

	gtk_widget_set_hexpand(GTK_WIDGET(entry), FALSE);
	gtk_widget_set_vexpand(GTK_WIDGET(entry), FALSE);

	submenu = gtk_menu_new();

	if (!nohome)
	{
		submenu_item_settings = gtk_menu_item_new_with_label("Settings");
		gtk_menu_shell_append(GTK_MENU_SHELL(submenu), submenu_item_settings);
	}

	submenu_item_help = gtk_menu_item_new_with_label("Help");
	submenu_menu_help = gtk_menu_new();
		submenu_item_onlinehelp = gtk_menu_item_new_with_label("Online help");
		submenu_item_about = gtk_menu_item_new_with_label("About");

	gtk_menu_shell_append(GTK_MENU_SHELL(submenu_menu_help), submenu_item_onlinehelp);
	gtk_menu_shell_append(GTK_MENU_SHELL(submenu_menu_help), submenu_item_about);

	gtk_menu_item_set_submenu(GTK_MENU_ITEM(submenu_item_help), submenu_menu_help);
	gtk_menu_shell_append(GTK_MENU_SHELL(submenu), submenu_item_help);

	gtk_widget_show_all(submenu);

	scrolled_window = gtk_scrolled_window_new(NULL, NULL);
	gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(scrolled_window),
		GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);

	treeview = gtk_tree_view_new();
	gtk_tree_view_set_activate_on_single_click(GTK_TREE_VIEW(treeview), TRUE);
	gtk_tree_view_set_headers_visible(GTK_TREE_VIEW(treeview), FALSE);
	gtk_container_add(GTK_CONTAINER(scrolled_window), treeview);
	gtk_widget_grab_focus(entry);

	cmd_row = gtk_list_box_row_new();
	GtkWidget *cmd_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);
	gtk_container_add(GTK_CONTAINER(cmd_row), cmd_box);

	GtkWidget *cmdicon = gtk_image_new_from_icon_name("terminal-tango", GTK_ICON_SIZE_BUTTON);
	gtk_box_pack_start(GTK_BOX(cmd_box), cmdicon, FALSE, FALSE, 0);

	GtkWidget *cmdrun = gtk_label_new("Run in Terminal");
	gtk_box_pack_start(GTK_BOX(cmd_box), cmdrun, FALSE, FALSE, 0);

	web_row = gtk_list_box_row_new();
	web_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);
	gtk_container_add(GTK_CONTAINER(web_row), web_box);

	GtkWidget *webicon = gtk_image_new_from_icon_name("edit-find", GTK_ICON_SIZE_BUTTON);
	gtk_box_pack_start(GTK_BOX(web_box), webicon, FALSE, FALSE, 0);

	GtkWidget *webrun = gtk_label_new("Search on Web");
	gtk_box_pack_start(GTK_BOX(web_box), webrun, FALSE, FALSE, 0);
	
	if (showcmd == 1)
	{
		gtk_list_box_insert(GTK_LIST_BOX(listbox2), cmd_row, -1);
	}
	
	if (showweb == 1)
	{
		gtk_list_box_insert(GTK_LIST_BOX(listbox2), web_row, -1);
	}
	gtk_widget_set_size_request(web_row, -1, 32);
	gtk_widget_set_size_request(cmd_row, -1, 32);

	g_signal_connect(window, "key-release-event", G_CALLBACK(on_key_release), row);
	g_signal_connect(submenu_item_settings, "activate", G_CALLBACK(showcfg), NULL);
	g_signal_connect(submenu_item_about, "activate", G_CALLBACK(on_submenu_item_about_selected), NULL);
	g_signal_connect(submenu_item_onlinehelp, "activate", G_CALLBACK(on_submenu_item_onlinehelp_selected), NULL);
	g_signal_connect(listbox2, "row-activated", G_CALLBACK(on_run_command), entry);
	g_signal_connect(treeview, "row-activated", G_CALLBACK(on_item_activated), NULL);

	//g_signal_connect(window, "button-press-event", G_CALLBACK(on_button_press), submenu);

	//if (exitwhenunfocused)
	//{
		//g_signal_connect(window, "focus-out-event", G_CALLBACK(on_focus_out), NULL);
	//}

	// Load apps into the list box
	grid = gtk_grid_new();
	gtk_container_add(GTK_CONTAINER(window), grid);
	mathtext = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 2);
	math = gtk_label_new("Math Answer: ");
	manswer = gtk_label_new("");
	gtk_label_set_selectable(GTK_LABEL(manswer), TRUE);

	sidebox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 1);

	// Sidebox
	opt_btn = gtk_menu_button_new();
	gtk_button_set_image(GTK_BUTTON(opt_btn), gtk_image_new_from_icon_name("application-menu", GTK_ICON_SIZE_BUTTON));
	gtk_box_pack_start(GTK_BOX(sidebox), opt_btn, FALSE, FALSE, 2);
	gtk_menu_button_set_popup(GTK_MENU_BUTTON(opt_btn), submenu);
	//g_signal_connect(opt_btn, "clicked", G_CALLBACK(on_sidebarbutton_clicker), GINT_TO_POINTER(0));

	if (showsession)
	{
		session_btn = gtk_menu_button_new();
		gtk_button_set_image(GTK_BUTTON(session_btn), gtk_image_new_from_icon_name("system-shutdown", GTK_ICON_SIZE_BUTTON));
		gtk_box_pack_end(GTK_BOX(sidebox), session_btn, FALSE, FALSE, 2);
		//g_signal_connect(session_btn, "clicked", G_CALLBACK(on_sidebarbutton_clicker), GINT_TO_POINTER(9));

		sessionmenu = gtk_menu_new();
		if (showsessionlogout)
		{
			sessionmenu_item_logout = gtk_menu_item_new_with_label("Logout");
			gtk_menu_shell_append(GTK_MENU_SHELL(sessionmenu), sessionmenu_item_logout);
			g_signal_connect(sessionmenu_item_logout, "activate", G_CALLBACK(sessionrun), logoutcmd);
		}
		if (showsessionlockscreen)
		{
			sessionmenu_item_lockscreen = gtk_menu_item_new_with_label("Lock Screen");
			gtk_menu_shell_append(GTK_MENU_SHELL(sessionmenu), sessionmenu_item_lockscreen);
			g_signal_connect(sessionmenu_item_lockscreen, "activate", G_CALLBACK(sessionrun), lockscreencmd);
		}
		if (showsessionpwroff)
		{
			sessionmenu_item_pwroff = gtk_menu_item_new_with_label("Power Off");
			gtk_menu_shell_append(GTK_MENU_SHELL(sessionmenu), sessionmenu_item_pwroff);
			g_signal_connect(sessionmenu_item_pwroff, "activate", G_CALLBACK(sessionrun), pwroffcmd);
		}
		if (showsessionreboot)
		{
			sessionmenu_item_reboot = gtk_menu_item_new_with_label("Reboot");
			gtk_menu_shell_append(GTK_MENU_SHELL(sessionmenu), sessionmenu_item_reboot);
			g_signal_connect(sessionmenu_item_reboot, "activate", G_CALLBACK(sessionrun), rebootcmd);
		}
		if (showsessionsuspend)
		{
			sessionmenu_item_suspend = gtk_menu_item_new_with_label("Suspend");
			gtk_menu_shell_append(GTK_MENU_SHELL(sessionmenu), sessionmenu_item_suspend);
			g_signal_connect(sessionmenu_item_suspend, "activate", G_CALLBACK(sessionrun), suspendcmd);
		}
		if (showsessionhibernate)
		{
			sessionmenu_item_hibernate = gtk_menu_item_new_with_label("Hibernate");
			gtk_menu_shell_append(GTK_MENU_SHELL(sessionmenu), sessionmenu_item_hibernate);
			g_signal_connect(sessionmenu_item_hibernate, "activate", G_CALLBACK(sessionrun), hibernatecmd);
		}
		gtk_widget_show_all(sessionmenu);
		gtk_menu_button_set_popup(GTK_MENU_BUTTON(session_btn), sessionmenu);
	}

	if (showsettings)
	{
		cfg_btn = gtk_button_new();
		gtk_button_set_image(GTK_BUTTON(cfg_btn), gtk_image_new_from_icon_name("settings-configure", GTK_ICON_SIZE_BUTTON));
		gtk_box_pack_end(GTK_BOX(sidebox), cfg_btn, FALSE, FALSE, 2);
		g_signal_connect(cfg_btn, "clicked", G_CALLBACK(on_sidebarbutton_clicker), GINT_TO_POINTER(7));
	}
	if (showuser)
	{
		user_btn = gtk_button_new();
		gtk_box_pack_end(GTK_BOX(sidebox), user_btn, FALSE, FALSE, 2);
		GdkPixbuf *icon_pixbuf = gdk_pixbuf_new_from_file(profilepic, NULL);
		if (icon_pixbuf)
		{
			GdkPixbuf *resized_icon = gdk_pixbuf_scale_simple(icon_pixbuf, 16, 16, GDK_INTERP_BILINEAR);

			g_object_unref(icon_pixbuf);

			GtkWidget *image = gtk_image_new_from_pixbuf(resized_icon);
			gtk_button_set_image(GTK_BUTTON(user_btn), image);

			g_object_unref(resized_icon);
		}
		g_signal_connect(user_btn, "clicked", G_CALLBACK(on_sidebarbutton_clicker), GINT_TO_POINTER(1));
	}
	if (showvid)
	{
		vid_btn = gtk_button_new();
		gtk_button_set_image(GTK_BUTTON(vid_btn), gtk_image_new_from_icon_name("folder-videos-symbolic", GTK_ICON_SIZE_BUTTON));
		gtk_box_pack_end(GTK_BOX(sidebox), vid_btn, FALSE, FALSE, 2);
		g_signal_connect(vid_btn, "clicked", G_CALLBACK(on_sidebarbutton_clicker), GINT_TO_POINTER(6));
	}
	if (showimg)
	{
		img_btn = gtk_button_new();
		gtk_button_set_image(GTK_BUTTON(img_btn), gtk_image_new_from_icon_name("folder-pictures-symbolic", GTK_ICON_SIZE_BUTTON));
		gtk_box_pack_end(GTK_BOX(sidebox), img_btn, FALSE, FALSE, 2);
		g_signal_connect(img_btn, "clicked", G_CALLBACK(on_sidebarbutton_clicker), GINT_TO_POINTER(5));
	}
	if (showmusic)
	{
		music_btn = gtk_button_new();
		gtk_button_set_image(GTK_BUTTON(music_btn), gtk_image_new_from_icon_name("folder-music-symbolic", GTK_ICON_SIZE_BUTTON));
		gtk_box_pack_end(GTK_BOX(sidebox), music_btn, FALSE, FALSE, 2);
		g_signal_connect(music_btn, "clicked", G_CALLBACK(on_sidebarbutton_clicker), GINT_TO_POINTER(4));
	}
	if (showdwn)
	{
		dwn_btn = gtk_button_new();
		gtk_button_set_image(GTK_BUTTON(dwn_btn), gtk_image_new_from_icon_name("folder-download-symbolic", GTK_ICON_SIZE_BUTTON));
		gtk_box_pack_end(GTK_BOX(sidebox), dwn_btn, FALSE, FALSE, 2);
		g_signal_connect(dwn_btn, "clicked", G_CALLBACK(on_sidebarbutton_clicker), GINT_TO_POINTER(3));
	}
	if (showdoc)
	{
		doc_btn = gtk_button_new();
		gtk_button_set_image(GTK_BUTTON(doc_btn), gtk_image_new_from_icon_name("folder-documents-symbolic", GTK_ICON_SIZE_BUTTON));
		gtk_box_pack_end(GTK_BOX(sidebox), doc_btn, FALSE, FALSE, 2);
		g_signal_connect(doc_btn, "clicked", G_CALLBACK(on_sidebarbutton_clicker), GINT_TO_POINTER(2));
	}

	if (showcalc == 1)
	{
		gtk_box_pack_start(GTK_BOX(mathtext), math, TRUE, TRUE, 0);
		gtk_box_pack_start(GTK_BOX(mathtext), manswer, TRUE, TRUE, 0);
	}

	gtk_widget_set_vexpand(scrolled_window, TRUE);
	gtk_widget_set_hexpand(scrolled_window, TRUE);

	gtk_grid_attach(GTK_GRID(grid), sidebox, 0, 0, 1, 1);
	gtk_grid_attach(GTK_GRID(grid), scrolled_window, 1, 0, 1, 1);
	gtk_grid_attach(GTK_GRID(grid), mathtext, 1, 1, 1, 1);
	gtk_grid_attach(GTK_GRID(grid), entry, 0, 2, 2, 1);

	gtk_widget_set_size_request(listbox2, -1, -1);
	gtk_widget_set_size_request(scrolled_window, -1, 256);

	if (sgcfg)
	{
		gtk_widget_activate(submenu_item_settings);
	}
	else
	{
		gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_MOUSE);
		load_apps(GTK_TREE_VIEW(treeview));

		filter_model = GTK_TREE_MODEL_FILTER(gtk_tree_model_filter_new(GTK_TREE_MODEL(sorted_model), NULL));

		filter_data.filter_text = g_strdup("");
		filter_data.filter = filter_model;
		filter_data.treeview = GTK_TREE_VIEW(treeview);  

		gtk_tree_model_filter_set_visible_func(filter_model,
			(GtkTreeModelFilterVisibleFunc) on_filter_visible, &filter_data, NULL);
			gtk_tree_view_set_model(GTK_TREE_VIEW(treeview), GTK_TREE_MODEL(filter_model));
			filter_data.entry = GTK_ENTRY(entry);

		g_signal_connect(entry, "changed", G_CALLBACK(on_entry_changed), &filter_data);
		gtk_widget_show_all(window);
		gtk_widget_hide(mathtext);
		gtk_widget_grab_focus(entry);
		gtk_main();
	}
}