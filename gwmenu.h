#include <gtk/gtk.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <math.h>
#include <ctype.h>
#define ML 256

const gchar *cweb, *cwebng, *corder, *active_text; 
const gchar* app_dirs[] = {"/usr/share/applications", "", NULL};
const gchar* tile_dirs[] = {"/usr/share/gwmenu/tiles", "", NULL};
const gchar* quick_dirs[] = {NULL};
const gchar* pver = mver;
gchar *pm, *webengine, *cwengine, cengine[ML], *home_dir, config_file_path[ML], *iconame,
pwroffcmd[ML], rebootcmd[ML], hibernatecmd[ML], suspendcmd[ML], logoutcmd[ML], lockscreencmd[ML],
settingscmd[ML], usercmd[ML];
gint wengine, order = 0, showweb = 1, showcmd = 1, showcalc = 1, showda = 1,
	showscientific = 1, exitwhenunfocused = 0, sgcfg,  
callconfig = 0, nohome = 0, restarting = 0, iconsize = 16, showuser = 1, showmusic = 1, 
showdoc = 1, showdwn = 1, showimg = 1, showvid = 1, showsession = 1,
showsessionpwroff=1, showsessionreboot=1, showsessionhibernate=1, showsessionsuspend=1, 
showsessionlogout=1, showsessionlockscreen=1, showsettings=1, defheight = 500, defwidth = 300,
 showtiles=1, tilesize=32;

gboolean gshowcmd, gshowcalc, gshowweb, gshowda, gshowscientific, gexitwhenunfocused;

GtkWidget *window, *grid, *button, *cmd_row, *dialog, *web_row, *entry, *manswer, *mathtext,
*listbox2,*pr, *row, *headerbar, *button, *image, *wtitle, *submenu, *submenu_item_settings, *submenu_item_quickhelp,
*submenu_item_about, *submenu_item4, *submenu_item5, *weblabel, *webcombo, *webctm, *worder, *wshowcmd,
*wshowweb, *wshowcalc, *wshowscientific, *wexitwhenunfocused, *defbtn, *applybtn, *treeview,
*web_box, *wshowda, *scrolled_window, *math, *submenu_item_onlinehelp, *submenu_menu_help, *submenu_item_help,
*tilegrid, *scrolled_tiles,

*sidebox, *cfg_btn, *session_btn, *home_btn, *music_btn, *doc_btn, *vid_btn, *user_btn, *dwn_btn, *opt_btn,
	*img_btn,

*sessionmenu, *sessionmenu_item_logout, *sessionmenu_item_lockscreen, *sessionmenu_item_pwroff,
*sessionmenu_item_reboot, *sessionmenu_item_hibernate, *sessionmenu_item_suspend,

*confbox ,*notebook, *cfggrid0, *cfggrid1, *cfggrid2,

*gdefwidth, *gdefheight, *giconsize,
		*gshowdoc, *gshowdwn, *gshowmusic, *gshowimg, *gshowvid, *gshowsettings, *gshowsession, *gshowuser,
		*gshowsessionhibernate, *gshowsessionlockscreen, *gshowsessionlogout, *gshowsessionpwroff,
		*gshowsessionreboot, *gshowsessionsuspend,

		*gpwroffcmd, *grebootcmd, *gsuspendcmd, *glogoutcmd, *glockscreencmd, *ghibernatecmd,
		*gusercmd, *gsettingscmd

;

GtkIconTheme *theme;
GtkIconInfo *info;
GdkPixbuf *icon;

GtkTreeStore *store;
GtkTreeViewColumn *column;
GtkCellRenderer *renderer;
GtkTreeModelSort *sorted_model;
GtkTreeModelFilter *filter_model;

#include "settings.h"
#include "calc.h"
#include "exec.h"
#include "entryloader.h"
#include "keyhandler.h"
#include "cfgmgr.h"
#include "events.h"
#include "mainwindow.h"