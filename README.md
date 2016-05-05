1. Potrzebne zależności
[compiler] sudo apt-get install build-essential
[required] sudo apt-get install cmake git libgtk2.0-dev pkg-config libavcodec-dev libavformat-dev libswscale-dev
[optional] sudo apt-get install python-dev python-numpy libtbb2 libtbb-dev libjpeg-dev libpng-dev libtiff-dev libjasper-dev libdc1394-22-dev

2. Klonowanie repo
git clone https://github.com/Itseez/opencv.git
git clone https://github.com/Itseez/opencv_contrib.git

3. Folder na build
cd ~/opencv
mkdir build
cd build

4. Użycie cmake

cmake -D CMAKE_BUILD_TYPE=Release -D CMAKE_INSTALL_PREFIX=/usr/local ..
cmake -DOPENCV_EXTRA_MODULES_PATH=../../opencv_contrib/modules ..
make -j5

5. Instalacja
sudo make install


BOOST
Pobranie i dwie komendy:

$ sudo ./bootstrap.sh --prefix=/usr/local
$ sudo ./b2 install 

niezbędne linie w cmake:
find_package( OpenCV REQUIRED )
find_package( Boost REQUIRED COMPONENTS system filesystem)
target_link_libraries( BagOfWords ${OpenCV_LIBS} )
target_link_libraries( BagOfWords ${Boost_LIBRARIES} )
