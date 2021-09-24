## C Programming Book

A free and open source book on the C Programming Language, with code examples
which work on Windows, Linux, and MacOS.  Book is fork
of https://publications.gbdirect.co.uk//c_book/copyright.html


### Install Dependencies

#### Windows

You can use Cygwin or Visual Studio.

##### Cygwin

Install cygwin.  From the cygwin installer, install cmake and gcc.

##### Visual Studio

Download and install [CMake](http://www.cmake.org/cmake/resources/software.html), and
Visual Studio.  The author uses the community edition.


On visual studio command prompt
    buildDebug.bat

will build and install the programs.  There is a visual studio file
put in the "build" directory, from which you can laucch the programs
and debug them.


#### Mac OS X

    brew install cmake
    ./macBuildDebug.sh


#### Linux (Ubuntu)

    sudo apt-get install cmake gcc
    ./buildDebug.sh
    ./buildInstall/bin/example1.1


### Build the book

Install Python, either through Cygwin, Visual Studio, brew, or apt.

#### Windows

        python -m venv venv
        source venv\bin\activate.bat
        python -m pip install --upgrade pip setuptools
        python -m pip install -r requirements.txt
        cd doc
        make html

#### Mac OS X

        python -m venv venv
        source venv/bin/activate
        python -m pip install --upgrade pip setuptools
        python -m pip install -r requirements.txt
        cd doc
        make html

#### Linux (Ubuntu)


        python -m venv venv
        source venv/bin/activate
        python -m pip install --upgrade pip setuptools
        python -m pip install -r requirements.txt
        cd doc
        make html
        make latexpdf
