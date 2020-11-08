#!/usr/bin/env bash

mock --root fedora-rawhide-x86_64 --install appliance-tools
mock --root fedora-rawhide-x86_64 --copyin ./*.ks /
mock --root fedora-rawhide-x86_64 --enable-network --isolation=simple --chroot "/usr/bin/appliance-creator -c /fedora-livecd-kde.ks -d -v --logfile appliance.log --cache /tmp/koji-appliance -o app-output --format raw --name KISS --version rawhide --release Today.n.0"
mock --root fedora-rawhide-x86_64 --copyout /app-output/KISS/KISS-sda.raw.xz .
