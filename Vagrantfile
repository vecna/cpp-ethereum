# -*- mode: ruby -*-
# vi: set ft=ruby :

# Depending of the fact that you're running a 64 or a 32
# bit arch, you've to 
# http://cloud-images.ubuntu.com/vagrant/precise/current/

Vagrant.configure("2") do |config|

  config.vm.hostname = "EthereumTest"
  # it's possible using:
  #
  # $ vagrant box add ubuntu/trusty64
  # https://vagrantcloud.com/ubuntu/trusty64/version/1/provider/virtualbox.box
  config.vm.box = "ubuntu/trusty64"
  config.vm.network :public_network

  #config.vm.provider :virtualbox do |vb|
  #  vb.gui = true
  #end

end

$script = <<SCRIPT
date > /etc/vagrant_provisioned_at

# Based on https://github.com/ethereum/cpp-ethereum/wiki/Building-on-Ubuntu

apt-get update

# these elements are just useless in our case
aptitude remove juju-core lxc -y

apt-get install build-essential g++-4.8 git cmake libgmp-dev libgmp3-dev libboost-all-dev -y
apt-get install automake unzip libtool libleveldb-dev yasm libminiupnpc-dev libreadline-dev scons -y
apt-get install libncurses5-dev -y
apt-get install qtbase5-dev qt5-default qtdeclarative5-dev libqt5webkit5-dev -y
apt-get install libcurl4-openssl-dev -y

git clone https://github.com/mmoss/cryptopp.git
cd cryptopp
scons --shared --prefix=/usr
cd ..

git clone git://github.com/cinemast/libjson-rpc-cpp.git
cd libjson-rpc-cpp/build
cmake .. && make
sudo make install
sudo ldconfig
cd ../..

git clone https://github.com/ethereum/cpp-ethereum.git
cd cpp-ethereum
mkdir build
cd build
cmake .. -DCMAKE_BUILD_TYPE=Release && make



SCRIPT

Vagrant.configure("2") do |config|
  config.vm.provision "shell", inline: $script
end
