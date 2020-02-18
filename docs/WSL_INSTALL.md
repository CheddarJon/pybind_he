### Install HElib on Windows Subsystem For Linux (Ubuntu)

1. Goto http://homenc.github.io/HElib/ (for more instructions)

   1. Check if GNU Multiple Precision Arithmetic Library is installed, `$ ldconfig -p | grep gmp`

   2. Else .... ***(not completed)***:

      1.   `$ sudo apt-get install  libgmp3-dev`

   3. Download & Install NTL (Library for doing Number Theory)

      1. `$ wget https://www.shoup.net/ntl/ntl-XXX.tar.gz `

      2. `$ tar -xf ntl/ntl-XXX.tar.gz`

      3. There could be a file: *ntl-XXX/doc/tour-unix.html*

      4. The above section in the file contains (i.e. run these commands): 

         ```
            ...
            $ ./configure 
            $ make
            $ make check
            $ sudo make install
         ```

(Branches on Slack)

         
