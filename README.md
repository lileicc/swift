# swift
A compiler for BLOG probabilistic programming language (http://bayesianlogic.github.io/).

### Check the paper: 
Appeared IJCAI 2016: http://www.ijcai.org/Proceedings/16/Papers/512.pdf

Arxiv Version: https://arxiv.org/abs/1606.09242 (arxiv)

### Code style:

1.  double spaces for indentation
2.  use linux line terminator
3.  follow http://google-styleguide.googlecode.com/svn/trunk/cppguide.xml

### Dependencies:
1. A C++ compiler (default GNU C++, VC++/Clang compatible)
2. The armadillo package: http://arma.sourceforge.net/
3. C++11 required

### How to Use:
1. Compile the Swift compiler: ```make compile``` (see compile.bat for windows)
2. Generate target C++ code:```./swift -i <Model File> -o <Target C++ File> -e <Algorithm>``` (swift.exe in Windows). Run ```./swift``` to see all the command line options
3. Compile your target code: ```g++ -o -O3 <target> <your C++ file> random/* -larmadillo``` (see swifty.sh)
4. Run your final binary!

### Armadillo Setup for OS X:
1. install armadillo library: ```brew install armadillo```
2. link C++ libraries for OS X: ```xcode-select --install```

### Armadillo Setup for Windows:
Download the VC++ solution config file from the armadillo webpage

### Documentation
Swift inherits all the syntax from BLOG with some extentions. Detailed documentations are under development. Please firstly check models under "example" directory to have a first impression. You can also check the documentations for BLOG for basic usage (http://bayesianlogic.github.io/pages/documentation.html).
