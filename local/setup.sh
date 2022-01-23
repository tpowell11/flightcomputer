# Premake script for this directory
# Intended to be called by global
# install script and not by itself.

# apt-gettable libs
sudo apt-get install libcap2

#bcm2835 download
cd ./lib
wget http://www.airspayce.com/mikem/bcm2835/bcm2835-1.71.tar.gz
tar -xjvf bcm2835-1.71.tar.gz
rm bcm2835-1.71.tar.gz
cd ..
