# compiler

# Compiler - C-- to intC Translator

This project is a compiler that translates the C-- programming language into an intermediate language called **intC**. The compiler is written in **C++** and is designed to demonstrate the process of compiler construction, including lexical analysis, parsing, semantic analysis, and code generation.

## Table of Contents

- [Project Overview](#project-overview)
- [Features](#features)
- [Installation](#installation)
- [Usage](#usage)
- [Project Structure](#project-structure)
- [Contributing](#contributing)
- [License](#license)

## Project Overview

The compiler aims to translate C-- (a simplified version of C) into intC, an intermediate language that can be further compiled to machine code. The project involves key phases of compiler construction, including:

- **Lexical Analysis**: Breaking the source code into tokens.
- **Parsing**: Converting the token stream into an Abstract Syntax Tree (AST).
- **Semantic Analysis**: Ensuring that the code is semantically correct.
- **Code Generation**: Translating the AST into the intC intermediate language.

## Features

- **Lexical Analysis**: Converts C-- source code into tokens.
- **Parsing**: Generates an Abstract Syntax Tree (AST) from the token stream.
- **Semantic Analysis**: Checks for semantic errors, such as type mismatches or undeclared variables.
- **Intermediate Code Generation**: Translates the AST into the intC intermediate language.
- **Optimizations**: Basic optimizations are performed during the code generation phase to produce more efficient intermediate code.

## Installation

To use this compiler, you need to have a C++ development environment set up. The following steps will guide you through the installation process.

### Prerequisites

- C++ compiler (e.g., GCC, Clang)
- CMake (for building the project)

### Steps

1. Clone the repository:

   ```bash
   git clone https://github.com/AyoubTe/compiler.git
   cd compiler
