# drs4-ana
Software for DRS4 Evaluation Board data analyses.

## Installation
You have to install ROOT before you compile this project.
```
# Install dependencies
brew install cmake
brew install boost

# Clone source codes and make a build directory
git clone https://github.com/daigohirata/drs4-ana ~/drs4-ana
mkdir ~/drs4-ana/build
cd ~/drs4-ana/build

# Build configuration (specify the installion directory)
cmake -DCMAKE_INSTALL_PREFIX=/opt/drs4-ana ..

# Compile and install this project
make 
sudo make install

# Add to PATH
# (This command should be added to ~/.zshrc)
export PATH="/opt/drs4-ana/bin:${PATH}"
```
## Usage
Use the following command to see help:
```
drsDecoder --help
```
## Uninstallation
```
# Remove source codes
rm -rf ~/drs4-ana

# Remove installed binaries
sudo rm -rf /opt/drs4-ana

# Remove the environment viariable configuration 
#（edit ~/.zshrc manually）
# remove : export PATH="/opt/drs4-ana/bin:${PATH}" 
```