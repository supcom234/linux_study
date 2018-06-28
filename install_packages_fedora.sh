#!/bin/bash

# Immediately bail if an error is encountered
#set -e

PACKAGE_MANAGER=dnf
CMAKE_VERSION=3.10.2
INSTALLX=true

echo "Installing cmake.  This may take a while..."
sudo mkdir -p /opt/cmake/
pushd /opt/cmake
sudo curl -s -o cmake-${CMAKE_VERSION}-Linux-x86_64.sh https://cmake.org/files/v3.10/cmake-${CMAKE_VERSION}-Linux-x86_64.sh
sudo chmod a+x cmake-${CMAKE_VERSION}-Linux-x86_64.sh
sudo bash ./cmake-${CMAKE_VERSION}-Linux-x86_64.sh --skip-license
sudo ln -s /opt/cmake/bin/* /usr/local/bin
popd

echo "Installing required software packages..."
sudo ${PACKAGE_MANAGER} update -y -q
declare -a software_packages=(
    "nasm"
    "make"
    "gcc-c++"
    "glibc-devel.i686"
    "libstdc++-devel.i686"
    "glibc-static"
    "kernel-devel-uname-r == $(uname -r)"
    "vim"
    "man-pages"
    "strace"
    "gdb"
    "hexedit"
    "git"
    #libraries for 32-bit
    "redhat-lsb-core.i686"
    "glib2.i686"
    "libXext.i686"
    "libXi.i686"
    "libSM.i686"
    "libICE.i686"
    "freetype.i686"
    "fontconfig.i686"
    "dbus-libs.i686"
)


for p in "${software_packages[@]}"
do
    echo "Installing $p..."
    sudo ${PACKAGE_MANAGER} install "$p" -y -q
done

if [ "$INSTALLX" = true ] ; then
    sudo ${PACKAGE_MANAGER} group install lxde-desktop-environment -y
    sudo ${PACKAGE_MANAGER} install gvim -y
    sudo ${PACKAGE_MANAGER} install qhexedit2 -y
    sudo ${PACKAGE_MANAGER} install ddd -y
    VBoxClient --display
fi

#peda and ./.gdbinit creation
git clone https://github.com/longld/peda
echo "source ~/peda/peda.py" > ./.gdbinit
echo "set disassembly-flavor intel" >> ./.gdbinit
echo "set pagination off" >> ./.gdbinit
echo "history save on" >> ./.gdbinit
echo "set history filename ~/.gdb_history" >> ./.gdbinit
echo "history size 32768" >> ./.gdbinit
echo "history expansion on" >> ./.gdbinit

#clone Developer_Test_Bank
git clone git@gitlab.com:JCantu248/Developer_Test_Bank.git

#ida pro install
wget https://out7.hex-rays.com/files/idafree70_linux.run
chmod 007 ./idafree70_linux.run

#./idafree70_linux.run

# Addtitional stuff I would like to be on the test VM
sudo systemctl set-default graphical.target
sudo rpm -v --import https://download.sublimetext.com/sublimehq-rpm-pub.gpg
sudo dnf config-manager --add-repo https://download.sublimetext.com/rpm/stable/x86_64/sublime-text.repo
sudo dnf install -y sublime-text

sudo timedatectl set-timezone America/Chicago
sudo dnf install -y ntpdate
sudo systemctl start ntpdate
sudo systemctl enable ntpdate
