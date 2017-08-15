# Yaml #

---

[![Github Tag](https://img.shields.io/github/tag/LuxAtrumStudio/Yaml.svg)](https://github.com/LuxAtrumStudio/Yaml)
[![Github Pages](https://img.shields.io/badge/Documentation-gh--pages-blue.svg)](https://luxatrumstudio.github.io/Yaml/)

[![Build Status](https://img.shields.io/travis/LuxAtrumStudio/Yaml.svg)](https://travis-ci.org/LuxAtrumStudio/Yaml)
[![CodeCov](https://img.shields.io/codecov/c/github/LuxAtrumStudio/Yaml/master.svg)](https://codecov.io/gh/LuxAtrumStudio/Yaml)
[![Codacy Grade](https://img.shields.io/codacy/grade/6245acd81a924d53a26a7eda45bc4073.svg)](https://www.codacy.com/app/LuxAtrumStudio/Yaml)

---

## Introduction ##

Yaml is a header only project intended for creating and parsing yaml files from
C++ projects. The project is intended to be as similar to standard library
containers as possible, in order to make a simple transition.

## Installation ##

The yaml project can be installed with these commands

```
git clone https://github.com/LuxAtrumStudio/Yaml.git
cd Yaml
make install
```

## Usage ##

Inorder to use the yaml project, only a single header file must be included
like so:

```cpp
#include<yaml/yaml.hpp>
```

Then Yaml classes can be defined with:

```cpp
yaml::Yaml myYaml;
```
