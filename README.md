V. Santos, 11-dez-2019 ( I was here :-) -- Cá estou eu a mudar outra vez!
V. Santos, 11-Dez-2019,15:18

# How to send files to online repo

```bash
git add .
git commit -m "mensagem de commit"
git push
```

# Compilation

```bash
mkdir build
cd build
cmake ..
make
```

Steps for the class
--------------------

 - Explain how to install git and create a github account and how to access it.
 - Brief introduction to github
 - Some examples of our projects: [rustbot](https://github.com/miguelriemoliveira/RustBot), [smobex](https://github.com/lardemua/SmObEx), [atlascar2_calibration](https://github.com/lardemua/AtlasCarCalibration) [v3v](https://github.com/miguelriemoliveira/v3v) and [vintra](https://github.com/miguelriemoliveira/vintra-miguel)
 - Some examples of other projects: [octomap](https://github.com/OctoMap/octomap)
 
  - How to create a fork of this repository or otherwise create a copy to start new developments.
 - **The README.md is everything**!
 - Create a gitignore file
 - Explain common procedures during development: status, commits and pushes.
 - github and IDEs

 - Procedures to carry out during the class:
   - Create teams of 4 students.
   - Nominate a project coordinator (PC).
   - PC creates the fork of repository for his team.
   - PC invites collaborators for the project (as well as the professors to follow their work)
   - All members of teams compile existing application locally in their computers and try the execution and documentation generation.
   - Create a project to manage the issues (Kanban)
   - (PC) creates issues for each collaborator and distributes tasks: one function for each to start!
   - Possible further developments upon function completion:
     - improve user interface (glade) to add more options (widgets)
     - improve documentation (instructions, images, examples, etc.)
     - other improvements that the PC and his team decide to propose.

In the end of the class, the professors will test the several projects and nominate the most successful development :-)
 

Instructions and main packages
------------------------------
To develop and build the application, besides the GNU C/C++ compiler,
you need to have installed some packages:

  cmake
  libgtk-3-dev
  glade

and some documentation tools are highly advised:

   libgtk-3-doc
   gtk-3-examples
   libcairo2-doc
   devhelp
   Doxygen

So, perform the following:

```bash
   sudo apt install cmake libgtk-3-dev libgtk-3-doc gtk-3-examples glade libcairo2-doc devhelp doxygen doxygen-gui
```

To test whether GTK was properly installed and also get acquainted with GTK
possibilities, you can use the following command to perform some testings and
verifications.

```bash
  /usr/bin/gtk3-demo

```

prototypes.h
------------

To generate the prototypes file from the proper cmake target, the following is needed:

```bash
  sudo apt install cproto exuberant-ctags indent
```

misc
----
There are other packages that can be useful for some scripts to work 
properly, but they are not necessary for this project. Follow some examples.


```bash
  sudo apt install xutils-dev graphviz imagemagick
```

asciidoc
--------
If you want to edit documents in asciidoc format, the following are
**needed/recomended**:

```bash
  sudo apt install asciidoc dblatex fop source-highlight
```

opencv
------
If you also need to use opencv, install it and its documentation:

```bash
  sudo apt install libopencv-dev opencv-doc
```

Although the documentation can be found online.
After version 3, openCV is focused on C++ and Python. So, its documentation is
oriented in those directions:

  https://docs.opencv.org/master/

However, up to that version, the documentation also incuded C language, keeping
the compatibility with the existing programs in C. So, if you use C language
for openCV, report to the last documentation version available for C, such as
version 2.4.X:

  https://docs.opencv.org/2.4/




