
Debian
====================
This directory contains files used to package tokugawad/tokugawa-qt
for Debian-based Linux systems. If you compile tokugawad/tokugawa-qt yourself, there are some useful files here.

## tokugawa: URI support ##


tokugawa-qt.desktop  (Gnome / Open Desktop)
To install:

	sudo desktop-file-install tokugawa-qt.desktop
	sudo update-desktop-database

If you build yourself, you will either need to modify the paths in
the .desktop file or copy or symlink your tokugawaqt binary to `/usr/bin`
and the `../../share/pixmaps/tokugawa128.png` to `/usr/share/pixmaps`

tokugawa-qt.protocol (KDE)

