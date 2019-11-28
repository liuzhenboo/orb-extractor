# ORBExtractor(based on orbslam2)
**Authors:** [liuzhenbo](https://www.zhihu.com/people/liuzhenbo)

**29 Nov 2019**: First submit

To better understand the feature extractor strategy of orbslam2, I separate orb-feature extractor code from orbslam2 project.
so, **ORBExtractor** is a feature detector way which is based on [orbslam2](https://github.com/raulmur/ORB_SLAM2).

# 1. Prerequisites
I have tested the library in **Ubuntu 18.04**
 
## C++11 or C++0x Compiler

## OpenCV
I use [OpenCV](http://opencv.org) to manipulate images and features.My version is 3.4.8.

# 2. Building this library and examples(main.cpp)

Clone the repository:
```
git clone https://github.com/slaming/ORBExtractor
```

cd ORBExtractor
mkdir build
cd build
cmake ..
build -j4

# 3.Examples(main.cpp)

cd bin
./ORBextractor ../pictures/liu2.jpg ../param/orb.yaml

## Provide two results
<a href="https://github.com/slaming/ORBExtractor/blob/master/screenshots" target="_blank"><img src="https://github.com/slaming/ORBExtractor/blob/master/screenshots/liu1.jpg" 
alt="ORBExtractor" width="240" height="180" border="10" /></a>
