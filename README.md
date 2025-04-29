# drs4-ana
Software for DRS4 Evaluation Board data analyses.

## Installation
You have to install ROOT before you compile this project.
```
# Install thirdparty
brew install cmake
brew install boost

# Compile this project
git clone https://github.com/daigohirata/drs4-ana ~/drs4-ana
cd ~/drs4-ana
mkdir build
cd build
cmake -DCMAKE_INSTALL_PREFIX=/opt/drs4-ana ..
make 
sudo make install

# Add to PATH
export PATH=/opt/drs4-ana/bin:${PATH}
# (This command should be added to ~/.zshrc)
```
## Usage
Use the following command to see help:
```
drsDecoder --help
```