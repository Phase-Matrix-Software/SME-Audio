# SME\_Audio
[![Build Status](https://travis-ci.org/Phase-Matrix-Software/SME-Audio.svg?branch=master)](https://travis-ci.org/Phase-Matrix-Software/SME-Audio)

# Building and installing
## Install dependencies

### Ubuntu
```
sudo apt-get install -y libglm-dev
sudo apt-get install -y libopenal-dev
sudo apt-get install -y libalut-dev
sudo apt-get install -y libvorbis-dev
```

### Arch
```
sudo pacman -S glm
sudo pacman -S openal
sudo pacman -S freealut
sudo pacman -S libvorbis
```

##Install (Option 1 - only install SME\_Audio)
```
git clone https://github.com/Phase-Matrix-Software/SME-Audio
cd SME-Audio
make
make install
```

##Install (Option 2 - install SME\_Audio and SME\_Core)
```
git clone https://github.com/Phase-Matrix-Software/SME-Core SME_Core
git clone https://github.com/Phase-Matrix-Software/SME-Audio SME_Audio
cd SME_Audio
make CONF=Debug
make install CONF=Debug
```
