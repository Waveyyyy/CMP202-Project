# CMP202 - Data Structures and Algorithms 2

## Statically compile SFML

1. Download SFML source `wget https://github.com/SFML/SFML/releases/download/2.5.1/SFML-2.5.1-sources.zip -O ~/Downloads/SFML-2.5.1-sources.zip`
1. unzip to the /opt directory `unzip ~/Downloads/SFML-2.5.1-sources.zip -d /opt/`
1. Install dependencies (Ubuntu 20.04.4 used for testing)
    - libx11-dev (X11)
    - libxrandr-dev (xrandr)
    - libgl1-mesa-dev (OpenGL)
    - libudev-dev (UDev)
    - libfreetype-dev (freetype)
    - libopenal-dev (OpenAL)
    - libvorbis-dev (Vorbis)
    - libflac-dev (FLAC)
1. `cmake -S /opt/SFML-2.5.1 -B /opt/sfml-build -G Ninja -DBUILD_SHARED_LIBS=FALSE`
1. change directory to `/opt/sfml-build` and create a new file `CMAKELists.txt`
1. add the line `set(BUILD_SHARED_LIBS FALSE)` to `CMAKELists.txt`
1. run `cmake . && ninja all` to build the static libs
1. finally run `ninja install` may need to be ran with sudo privileges

## Compile the program 
1. run the following command in the root of the project directory 
    - `cmake -DCMAKE_BUILD_TYPE=Release -DCMAKE_MAKE_PROGRAM=ninja -G Ninja -S . -B ./cmake-build-release`
1. change directory to `cmake-build-release` and run `ninja all`
