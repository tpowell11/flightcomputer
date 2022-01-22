SOURCE_DIR=pwd #store the location of the repo

# /remote build

# /software build
# Credit to https://solarianprogrammer.com/2017/12/08/raspberry-pi-raspbian-install-gcc-compile-cpp-17-programs/
# for the install script for g++10
# using this version of the compiler allows
# the usage of new c++ features making writing the
# ground software conciderably easier.
## File acquisition
cd ~
###download, install, and delete the binary
git clone https://bitbucket.org/sol_prog/raspberry-pi-gcc-binary.git
cd raspberry-pi-gcc-binary
tar -xjvf gcc-10.1.0-armhf-raspbian.tar.bz2
sudo mv gcc-10.1.0 /opt
cd ..
rm -rf raspberry-pi-gcc-binary
## Linking
echo 'export PATH=/opt/gcc-10.1.0/bin:$PATH' >> ~/.bashrc
echo 'export LD_LIBRARY_PATH=/opt/gcc-10.1.0/lib:$LD_LIBRARY_PATH' >> ~/.bashrc
. ~/.bashrc
sudo ln -s /usr/include/arm-linux-gnueabihf/sys /usr/include/sys
sudo ln -s /usr/include/arm-linux-gnueabihf/bits /usr/include/bits
sudo ln -s /usr/include/arm-linux-gnueabihf/gnu /usr/include/gnu
sudo ln -s /usr/include/arm-linux-gnueabihf/asm /usr/include/asm
sudo ln -s /usr/lib/arm-linux-gnueabihf/crti.o /usr/lib/crti.o
sudo ln -s /usr/lib/arm-linux-gnueabihf/crt1.o /usr/lib/crt1.o
sudo ln -s /usr/lib/arm-linux-gnueabihf/crtn.o /usr/lib/crtn.o
cd $SOURCE_DIR # back home
## 