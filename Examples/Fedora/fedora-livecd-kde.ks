# fedora-livecd-kde.ks
#
# Description:
# - Fedora Live Spin with the K Desktop Environment (KDE), default 1.4 GB version
#
# Maintainer(s):
# - Sebastian Vahl <fedora@deadbabylon.de>
# - Fedora KDE SIG, http://fedoraproject.org/wiki/SIGs/KDE, kde@lists.fedoraproject.org

%include fedora-live-kde-base.ks
%include fedora-live-minimization.ks
%include fedora-kde-minimization.ks

# DVD payload
part / --size=6500 --fstype ext4

%post
%end
