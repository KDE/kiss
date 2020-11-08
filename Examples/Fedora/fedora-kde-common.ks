
%packages
@firefox
@kde-apps
@kde-desktop
@kde-media
@kde-office
@networkmanager-submodules
fedora-release-kde

### The KDE-Desktop

### Browser
falkon

### fixes

# use kde-print-manager instead of system-config-printer
-system-config-printer
# make sure mariadb lands instead of MySQL (hopefully a temporary hack)
mariadb-embedded
mariadb-connector-c
mariadb-server

# minimal localization support - allows installing the kde-l10n-* packages
system-config-language
kde-l10n

# unwanted packages from @kde-desktop
# don't include these for now to fit on a cd
-desktop-backgrounds-basic
-kdeaccessibility*
#-ktorrent			# kget has also basic torrent features (~3 megs)
-digikam			# digikam has duplicate functionality with gwenview (~28 megs)
#-amarok 			# ~23 megs (mysql-embedded etc.)
-kipi-plugins			# ~8 megs + drags in Marble
#-kdeplasma-addons		# ~16 megs
#-krusader			# ~4 megs

# Additional packages that are not default in kde-* groups, but useful
k3b				# ~15 megs
#kdeartwork			# only include some parts of kdeartwork
fuse
mediawriter

### space issues

# admin-tools
-gnome-disk-utility
# kcm_clock still lacks some features, so keep system-config-date around
#-system-config-date
# prefer kcm_systemd
-system-config-services
# prefer/use kusers
-system-config-users

## avoid serious bugs by omitting broken stuff

%end
