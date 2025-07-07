#!/usr/bin/env bash

# write a file /etc/sddm.conf.d/99-initial-setup with the contents:
# 
# [Autologin]
# User=kde-initial-system-setup
# Session=plasma-wayland

cat <<EOF > /etc/sddm.conf.d/99-initial-setup.conf
[Autologin]
User=kde-initial-system-setup
Session=plasmawayland
EOF

