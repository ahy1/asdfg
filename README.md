# Elm Engine Template [![License](https://img.shields.io/github/license/JonasAlmaas/ElmTemplate.svg)](https://github.com/JonasAlmaas/ElmTemplate/blob/main/LICENSE)

Elm engine template repository

## Getting started

### 1. Cloning the repository

Start by cloning the repository with `git clone --recursive https://github.com/JonasAlmaas/ElmTemplate.git`

If the repository was cloned non-recursively previously, use `git submodule update --init --recursive` to clone the necessary submodules.

### 2. Install Vulkan SDK

[https://vulkan.lunarg.com](https://vulkan.lunarg.com)

I don't exactly know what you need, so just tick everything for now :D

### 3. Naming the project

Search for every instance of "GameName" and replace it with the name of your game/project.

### 4. Generation build

This project uses [Premake](https://premake.github.io) to generate build files. Here is an example of how to generate a Visual Studio solution:

```bash
premake5 vs2022
```
