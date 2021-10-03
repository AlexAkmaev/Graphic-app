# Graphic-app  
  
### Installation:  
  need graphics.h lib:
  ```
  sudo apt-get install build-essential
  sudo apt-get install libsdl-image1.2 libsdl-image1.2-dev guile-2.0 \
guile-2.0-dev libsdl1.2debian libart-2.0-dev libaudiofile-dev \
libesd0-dev libdirectfb-dev libdirectfb-extra libfreetype6-dev \
libxext-dev x11proto-xext-dev libfreetype6 libaa1 libaa1-dev \
libslang2-dev libasound2 libasound2-dev
  ```  
  Download lib from here [libgraph](http://download.savannah.gnu.org/releases/libgraph/libgraph-1.0.2.tar.gz)
  ```
  ./configure
  make
  sudo make install
  sudo cp /usr/local/lib/libgraph.* /usr/lib
  ```
  
### Launch: 
  ```
  gcc ScreenSaver.c -lgraph -lm
  ./a.out
  ```
