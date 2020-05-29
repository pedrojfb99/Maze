# Maze

> The main goal of this project is a maze implementation provided in 2D and 3D visualization. All the project must be developed using C++ and the OpenGL, GLFW, GLEW and GLM libraries. The player should move around the maze avoiding some obstacles like holes, etc, through the keyboard (A,D,S,W). 

---

## Content

- [Installation](#installation)
	- [Brew](#brew)
		- [GLFW](#glfw)
		- [GLM](#glm)
		- [GLEW](#glew)
	- [Clone](#clone)
	- [Compile](#compile)
	- [Run](#run)
- [Demo](#demo)
- [Tests](#tests)
- [License](#license)
---

## Installation

Make sure that you are using **Linux** or **Unix** as the operative system for a simplification (avoiding import manually all the libraries).

### Brew

Use the following command in order to install **brew**.

```shell
$ test -d ~/.linuxbrew && eval $(~/.linuxbrew/bin/brew shellenv)
$ test -d /home/linuxbrew/.linuxbrew && eval $(/home/linuxbrew/.linuxbrew/bin/brew shellenv)
$ test -r ~/.bash_profile && echo "eval \$($(brew --prefix)/bin/brew shellenv)" >>~/.bash_profile
$ echo "eval \$($(brew --prefix)/bin/brew shellenv)" >>~/.profile
``` 

#### GLFW

Use the following command in order to install **glfw** library.

```shell
brew install glfw
```

#### GLM

Use the following command in order to install **glfw** library.

```shell
brew install glm
```

#### GLEW

Use the following command in order to install **glfw** library.

```shell
brew install glew
```

### Clone

Use the following command in order to clone the repository.

```shell
$ git clone https://github.com/XiBiTuH/Maze.git
```

### Compile

Use the following command in order to compile.

```shell
$ g++ main.cpp -lGL -lGLEW -lglfw
```

### Run

If you have already compiled, execute the program.

```shell
$ ./a.out
```

## Demo

![](CG-2-2020-05-29_23.50.01.gif)

## Tests


## License

[![License](http://img.shields.io/:license-mit-blue.svg?style=flat-square)](http://badges.mit-license.org)

- **[MIT license](http://opensource.org/licenses/mit-license.php)**