typedef struct
{
	gchar *name;
	gchar *icon;
	gchar *path;
	gchar *toexec;
}AppDetails;

typedef struct
{
	GtkEntry *entry;
	GtkTreeModelFilter *filter;
	gchar *filter_text;
	GtkTreeView *treeview;
} FilterData;
FilterData filter_data;

gint gtk_tree_iter_compare_func(GtkTreeModel *model, GtkTreeIter *a, GtkTreeIter *b, gpointer user_data)
{
	gchar *name_a = NULL;
	gchar *name_b = NULL;
	gchar *casefolded_a = NULL;
	gchar *casefolded_b = NULL;
	gint result;

	gtk_tree_model_get(model, a, 0, &name_a, -1);
	gtk_tree_model_get(model, b, 0, &name_b, -1);

	if (name_a == NULL)
	{
		if (name_b == NULL) return 0;
		return -1;
	}
	if (name_b == NULL) return 1;

	casefolded_a = g_utf8_casefold(name_a, -1);
	casefolded_b = g_utf8_casefold(name_b, -1);

	result = g_utf8_collate(casefolded_a, casefolded_b);

	g_free(name_a);
	g_free(name_b);
	g_free(casefolded_a);
	g_free(casefolded_b);

	return result;
}

#define MAX_LETTERS 1000 

// Global array to store the first letters
char first_letters[MAX_LETTERS];
int letter_count = 0;

gboolean is_letter_in_first_letters(char letter) {
	for (int i = 0; i < letter_count; i++) {
		if (first_letters[i] == letter) {
			return TRUE;
		}
	}
	return FALSE;
}

void load_apps(GtkTreeView *treeview)
{
	store = gtk_tree_store_new(4, G_TYPE_STRING, G_TYPE_STRING, GDK_TYPE_PIXBUF, G_TYPE_STRING);

	renderer = gtk_cell_renderer_pixbuf_new();
	column = gtk_tree_view_column_new_with_attributes("", renderer, "pixbuf", 2, NULL);
	gtk_tree_view_append_column(treeview, column);

	renderer = gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes("", renderer, "text", 0, NULL);
	gtk_tree_view_append_column(treeview, column);

	sorted_model = GTK_TREE_MODEL_SORT(gtk_tree_model_sort_new_with_model(GTK_TREE_MODEL(store)));
	gtk_tree_sortable_set_sort_func(GTK_TREE_SORTABLE(sorted_model), 0, (GtkTreeIterCompareFunc)gtk_tree_iter_compare_func, NULL, NULL);
	gtk_tree_sortable_set_sort_column_id(GTK_TREE_SORTABLE(sorted_model), 0, GTK_SORT_ASCENDING);

	gtk_tree_view_set_model(treeview, GTK_TREE_MODEL(sorted_model));

	for (int i = 0; i < sizeof(app_dirs) / sizeof(app_dirs[0]); i++)
	{
		DIR *dir = opendir(app_dirs[i]);
		if (dir == NULL) continue;

		struct dirent *ent;
		while ((ent = readdir(dir)) != NULL)
		{
			if (ent->d_name[0] == '.' || !g_str_has_suffix(ent->d_name, ".desktop")) continue;

			gchar *path = g_strdup_printf("%s/%s", app_dirs[i], ent->d_name);
			GKeyFile *key_file = g_key_file_new();
			GError *error = NULL;

			if (!g_key_file_load_from_file(key_file, path, G_KEY_FILE_NONE, &error))
			{
				g_warning("Error loading .desktop file: %s", error->message);
				g_error_free(error);
				g_free(path);
				g_key_file_free(key_file);
				continue;
			}

			if (g_key_file_get_boolean(key_file, "Desktop Entry", "NoDisplay", NULL))
			{
				g_free(path);
				g_key_file_free(key_file);
				continue;
			}

			gchar *app_name = g_key_file_get_string(key_file, "Desktop Entry", "Name", NULL);
			gchar *icon_name = g_key_file_get_string(key_file, "Desktop Entry", "Icon", NULL);
			gchar *toexec = g_key_file_get_string(key_file, "Desktop Entry", "Exec", NULL);
			GdkPixbuf *icon_pixbuf = NULL;

			if (g_path_is_absolute(icon_name) && g_file_test(icon_name, G_FILE_TEST_EXISTS))
			{
				icon_pixbuf = gdk_pixbuf_new_from_file(icon_name, &error);
			}
			else
			{
				GtkIconTheme *icon_theme = gtk_icon_theme_get_default();
				GtkIconInfo *icon_info = gtk_icon_theme_lookup_icon(icon_theme, icon_name, iconsize, GTK_ICON_LOOKUP_USE_BUILTIN);

				if (icon_info)
				{
					icon_pixbuf = gtk_icon_info_load_icon(icon_info, &error);
					g_object_unref(icon_info);
				}
			}

			if (icon_pixbuf)
			{
				GdkPixbuf *resized_icon = gdk_pixbuf_scale_simple(icon_pixbuf, iconsize, iconsize, GDK_INTERP_BILINEAR);
				g_object_unref(icon_pixbuf);
				icon_pixbuf = resized_icon;
			}
			else
			{
				icon_pixbuf = gtk_icon_theme_load_icon(gtk_icon_theme_get_default(), "application-x-executable", 16, 0, NULL);
			}

			GtkTreeIter app_iter;
			gtk_tree_store_append(store, &app_iter, NULL);
			gchar *merged_data = g_strdup_printf("%s%s%s", app_name, toexec, icon_name);
			gtk_tree_store_set(store, &app_iter, 0, app_name, 1, toexec, 2, icon_pixbuf, 3, merged_data, -1);

			// Store the first letter
			if (app_name && letter_count < MAX_LETTERS)
			{
				first_letters[letter_count++] = g_utf8_get_char(app_name);
			}

			// Handling Desktop Actions
			gchar **groups = g_key_file_get_groups(key_file, NULL);
			if (showda)
			{
				for (int j = 0; groups[j] != NULL; j++)
				{
					if (g_str_has_prefix(groups[j], "Desktop Action"))
					{
						gchar *action_name = g_key_file_get_string(key_file, groups[j], "Name", NULL);
						gchar *exec_value = g_key_file_get_string(key_file, groups[j], "Exec", NULL);

						if (action_name && exec_value)
						{
							GtkTreeIter action_iter;
							gtk_tree_store_append(store, &action_iter, &app_iter);
							gchar *action_merged_data = g_strdup_printf("%s%s%s", action_name, exec_value, icon_name);
							gtk_tree_store_set(store, &action_iter, 0, action_name, 1, exec_value, 2, icon_pixbuf, 3, action_merged_data, -1);
							g_free(action_name);
							g_free(exec_value);
							g_free(action_merged_data);
						}
					}
				}
			}

			g_strfreev(groups);
			g_free(app_name);
			g_free(icon_name);
			g_clear_object(&icon_pixbuf);
			g_free(toexec);
			g_free(merged_data);
			g_key_file_free(key_file);
			g_free(path);
		}
		closedir(dir);
	}

		// Add only letters that are in first_letters
	for (gchar letter = 'A'; letter <= 'Z'; letter++)
	{
		if (is_letter_in_first_letters(letter))
		{
			GtkTreeIter letter_iter;
			gtk_tree_store_append(store, &letter_iter, NULL);
			gchar *letter_str = g_strdup_printf("%c", letter);
			GtkTreeIter sub_iter;
			gtk_tree_store_append(store, &sub_iter, &letter_iter);
			gtk_tree_store_set(store, &letter_iter, 0, letter_str, 1, letter_str, 2, NULL, 3, letter_str, -1);
			g_free(letter_str);
		}
	}
}