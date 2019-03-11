Emerald-unmaximize-fix
======================

About
-----

This is small program intended to be used as a daemon for fixing well known problem with Compiz fusion (Now Compiz Reloaded) and Emerald theme manager with enabled "borderless/titlebar-less" tweak in CompizConfig settings manager on almost all Linux machines.

Problem are missing window buttons on titlebar (close, minimize, etc...) after window comes back from maximized mode.

How it works
------------

Well, there is some Slavic science behind this creation. 
One thing I found is that buttons comes back when window title was changed. It forces me to start looking web for know-how about manipulating Linux display managers and UI.
Basic principle of this Gopnik-patch is only adding and removing one space into window title of window that comes from maximized mode.

Installation
------------

Some libraries are required:
```
apt-get install libunac1-dev
apt-get install libwnck-common libwnck-dev
```

Compile if needed using (included binary is compiled on x64 machine):
```
gcc $(pkg-config --cflags --libs libwnck-1.0) -lunac emerald_fix.c -o emerald_fix
```

Known issues
------------

- Window titles will loose diacritics (accents). Not my mistake, some bug in `xdotool` 
 