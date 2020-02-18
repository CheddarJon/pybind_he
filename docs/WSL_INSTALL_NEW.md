### Install HElib on Windows Subsystem For Linux (Ubuntu) (NEW)

1. Install Cmake `$ sudo apt-get install cmake`

2. Install pthreads `$ sudo apt-get install libpthread-stubs0-dev`

3. Install patchelf `$ sudo apt-get install patchelf`

4. Install m4 `$ sudo apt-get install m4`

5. Run *install_HElib.sh* 

   ```bash
   $ cd script
   $ chmod u+x install_HElib.sh
   $ ./install_HElib.sh
   ```

6. At last: Check the folder *pybind_he\lib* for a folder named *helib_pack* (!)

