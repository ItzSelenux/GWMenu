# GWMenu
Windows 10 Menu-like clone in GTK 

## Features:

- [x] Show system menu apps
- [x] Show Actions
- [x] Sidebar
- [x] have a simple configuration too
- [ ] Metro mosaic


## Build
Main Program:

```
make
```

## Configuration:

You can use the Settings (`gwmenu --cfg`) program to easily edit the values with a GUI, but values are also editable in `$HOME/.config/gwmenu.conf`

| Item                       | Description                              | Possible values                    | Values explanation                                   | Example                        |
|----------------------------|------------------------------------------|------------------------------------|-----------------------------------------------------|--------------------------------|
| iconsize                   | Size of icons                            | Positive integer                   | Sets the size of icons in pixels                     | iconsize=16                    |
| showuser                   | Toggle show user icon                 | 0, 1                               | 0: disabled <br> 1: enabled                          | showuser=1                     |
| showsettings               | Toggle show settings icon             | 0, 1                               | 0: disabled <br> 1: enabled                          | showsettings=1                 |
| showmusic                  | Toggle show music icon                | 0, 1                               | 0: disabled <br> 1: enabled                          | showmusic=1                    |
| showdoc                    | Toggle show documents icon            | 0, 1                               | 0: disabled <br> 1: enabled                          | showdoc=1                      |
| showdwn                    | Toggle show downloads icon            | 0, 1                               | 0: disabled <br> 1: enabled                          | showdwn=1                      |
| showimg                    | Toggle show images icon               | 0, 1                               | 0: disabled <br> 1: enabled                          | showimg=1                      |
| showvid                    | Toggle show videos icon               | 0, 1                               | 0: disabled <br> 1: enabled                          | showvid=1                      |
| showsession                | Toggle show session controls             | 0, 1                               | 0: disabled <br> 1: enabled                          | showsession=1                  |
| showsessionpwroff          | Toggle show power off option             | 0, 1                               | 0: disabled <br> 1: enabled                          | showsessionpwroff=1            |
| showsessionreboot          | Toggle show reboot option                | 0, 1                               | 0: disabled <br> 1: enabled                          | showsessionreboot=1            |
| showsessionhibernate       | Toggle show hibernate option             | 0, 1                               | 0: disabled <br> 1: enabled                          | showsessionhibernate=1         |
| showsessionsuspend         | Toggle show suspend option               | 0, 1                               | 0: disabled <br> 1: enabled                          | showsessionsuspend=1           |
| showsessionlogout          | Toggle show logout option                | 0, 1                               | 0: disabled <br> 1: enabled                          | showsessionlogout=1            |
| showsessionlockscreen      | Toggle show lock screen option           | 0, 1                               | 0: disabled <br> 1: enabled                          | showsessionlockscreen=1        |
| pwroffcmd                  | Command to power off the system          | Command string                     | Custom command to power off the system               | pwroffcmd=systemctl poweroff   |
| rebootcmd                  | Command to reboot the system             | Command string                     | Custom command to reboot the system                  | rebootcmd=systemctl reboot     |
| hibernatecmd               | Command to hibernate the system          | Command string                     | Custom command to hibernate the system               | hibernatecmd=systemctl hibernate|
| suspendcmd                 | Command to suspend the system            | Command string                     | Custom command to suspend the system                 | suspendcmd=systemctl suspend   |
| logoutcmd                  | Command to log out user                  | Command string                     | Custom command to log out the user                   | logoutcmd=systemctl terminate-user \$USER|
| lockscreencmd              | Command to lock screen                   | Command string                     | Custom command to lock the screen                    | lockscreencmd=xset s activate  |
| settingscmd                | Command to open settings                 | Command string                     | Custom command to open settings                      | settingscmd=sgsettings         |
| usercmd                    | Command to open user management          | Command string                     | Custom command to open user management               | usercmd=sgusers                |
| defheight                  | Default height of the menu               | Positive integer                   | Sets the default height of the menu in pixels        | defheight=500                  |
| showcalc                   | Toggle show answers of math formula      | 0, 1                               | 0: disabled <br> 1: enabled                          | showcalc=1                     |
| showscientific             | Toggle show math answer in scientific format | 0, 1                            | 0: disabled <br> 1: enabled                          | showscientific=0               |

The configuration file should be in `~/.config/gwmenu.conf`.

## About

GWMenu is a fork of [SGLauncher](https://github.com/ItzSelenux/SGLauncher) (GitHub doesn't mark this as a fork since it is a self-forked project).