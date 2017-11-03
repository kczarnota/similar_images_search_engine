# Similar images search engine
Application measuring performance of state-of-art feature descriptors when combined together in different ways.
It uses Bag of Words approach to create a visual word dictionary and then perform search.
Dictionary creation and tests runs are executed on [Wang dataset](http://wang.ist.psu.edu/docs/related/). Used libraries: OpenCV, Boost, QT.

## Requirements
```bash
sudo apt-get install cmake git libgtk2.0-dev pkg-config libavcodec-dev libavformat-dev libswscale-dev qtcreator qt5-default
```

### OpenCV
```bash
git clone https://github.com/opencv/opencv.git
git clone https://github.com/opencv/opencv_contrib.git
cd ~/opencv
mkdir build
cd build
cmake -D CMAKE_BUILD_TYPE=Release -D CMAKE_INSTALL_PREFIX=/usr/local ..
cmake -DOPENCV_EXTRA_MODULES_PATH=../../opencv_contrib/modules ..
make -j5
sudo make install
```

### BOOST
```bash
sudo ./bootstrap.sh --prefix=/usr/local
sudo ./b2 install
```

## Program compilation
```bash
git clone https://github.com/kczarnota/similar_images_search_engine
cd similar_images_search_engine
mkdir build
cd build
cmake ..
make
./BagOfWords
```

## Usage
* Specify path to directory with images(they should be grouped in sub-directories which represents different categories)
* Provide dictionary size
* Choose descriptor(if it's a combination you have to provide weights)
* Click prepare and wait for the process to finish
* Computed database will be saved, so you can load it next time
* Now you can pick an image and perform a query
* Or click test and compute precision and recall on whole dataset

## Screenshots
![](Screenshots/main_window.png?raw=true)

![](Screenshots/query.png?raw=true)