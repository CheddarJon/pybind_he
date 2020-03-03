###  Procedure
1. Install Ubuntu from Microsoft Store

2. Allow WSL by either
    Running the following command in powershell:
    `Enable-WindowsOptionalFeature -Online -FeatureName Microsoft-Windows-Subsystem-Linux`
    ,and restarting the system when prompted. 
    NOTE: you must run powershell as an administrator
    OR 
    Go to Conctorl Panel -> Programs -> Turn Windows features on or off, and select Windows Subsystem For Linux.
    
3. Run Ubuntu and finish the setup process

4. Checkout submodules

5. Installing HElib in WSL
    
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
    NOTE: if they system hangs itself on the test after the library is
          build you can interrupt with ctrl + C
    
    6. Run *cp_HElip_pack* and check for a folder named *helib_pack* in *pybind_he\lib* afterwards
    7. Run sanity check (*run_example_HElib.sh*)
    
6. Installing pybind in WSL

    1. Install *pytest* `$ python3.6 -m pip install pytest`
    2. Run *install_Pybind.sh*

    ```bash
    $ cd script
    $ chmod u+x install_Pybind.sh
    $ ./install_Pybind.sh
    ```
    Run *install_pybind_he.sh*

    3. Copy Pybind (*cp_Pybind11.sh*)
    4. Pybin documentation: "https://buildmedia.readthedocs.org/media/pdf/pybind11/master/pybind11.pdf"

7. Run `$ python3 setup.py install`

8. Run the python tests (*run_python_unittest.sh*)
