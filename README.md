# **My Online Portfolio**
A website for hosting my new online portfolio.
## **TODO**
 * [ ] Create the index page
 * [ ] Create a backend for the index page
## **Build this project**
**1.** Open a terminal window in the root directory of this project.

**2.** Install the required packages.
```bash
$ sudo apt install g++ cmake libssl-dev
```
**3.** Enter the `external` directory and unzip all packages.
```bash
$ cd external
$ unzip *.zip
```
**4.** Exit the `external` directory, create the `build` directory, and enter it.
```bash
$ cd ..
$ mkdir build && cd build
```
**5.** Generate CMake build files.
```bash
$ cmake ..
```
**6.** Build the project.
```bash
$ make
```
**7.** Run the generated executable.
```bash
$ ./bin/cs-server
```
