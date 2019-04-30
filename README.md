# Working Of Nqueen-CG-project

An OpenGL computer graphic mini-project on Working of Nqueen 

### Installation Instruction (Ubuntu/Linux)

- The first step is to install the development libraries of OpenGL/Glut in Ubuntu:
```
sudo apt-get install freeglut3 freeglut3-dev
```
- Clone the repository and 'cd' over to [the main directory](https://github.com/cristonkrizz/Nqueen-CG-project), execute the following command

```
$ gcc CG-nqueen.cpp -lGL -lGLU -lglut -lm -o output
$ ./output
```
### Instruction for CodeBlocks

- If you have CodeBlocks installed just Create a new project in it as "GLUT-Project",then copy the content from CG-nqueen.cpp to main.cpp and run the main.cpp file. Make sure you have freeglut setup in your codeblocks.
