# Minishell 🇪🇸

Minishell es un proyecto de la escuela 42 que consiste en implementar una pequeña shell escrita en C que pueda interpretar comandos de forma interactiva, simulando el comportamiento de una shell real como Bash.


## 🧠 Descripción

Este proyecto desarrolla un intérprete de comandos en lenguaje C, capaz de interpretar instrucciones básicas, gestionar procesos, redirigir entradas/salidas y manejar señales, entre otras funcionalidades. Su objetivo es familiarizar al programador con los conceptos fundamentales de sistemas UNIX y la programación a bajo nivel.


## ✨ Características principales

- Soporte para comandos con argumentos (ej: `ls -la`)
- Pipes (`|`) entre comandos
- Redirecciones:
  - Entrada: `<`
  - Salida: `>`, `>>`
  - Here document: `<<`
- Expansión de variables de entorno (`$VAR`)
- Manejo de comillas simples y dobles (`'`, `"`)
- Implementación de comandos **built-in**:
  - `cd`
  - `echo`
  - `pwd`
  - `export`
  - `unset`
  - `env`
  - `exit`
- Gestión de errores personalizada
- Manejo de señales (`Ctrl+C`, `Ctrl+D`, `Ctrl+\`)


## ⚙️ Instalación y uso

Clona el repositorio y compílalo usando `make`:

```bash
git clone https://github.com/Pablo-VH/Minishell.git
cd Minishell
make && ./minishell
```
---

# Minishell 🇬🇧

Minishell is a project from School 42 that consists of implementing a small shell written in C that can interpret commands interactively, simulating the behavior of a real shell such as Bash.


## 🧠 Description

This project develops a command interpreter in C language, capable of interpreting basic instructions, managing processes, redirecting inputs/outputs, and handling signals, among other functionalities. Its goal is to familiarize the programmer with the fundamental concepts of UNIX systems and low-level programming.


## ✨ Main features

- Support for commands with arguments (e.g., `ls -la`)
- Pipes (`|`) between commands
- Redirections:
  - Input: `<`
  - Output: `>`, `>>`
  - Here document: `<<`
- Expansion of environment variables (`$VAR`)
- Handling of single and double quotes (`'`, `"`)
- Implementation of **built-in** commands:
  - `cd`
  - `echo`
  - `pwd`
  - `export`
  - `unset`
  - `env`
  - `exit`
- Custom error handling
- Signal handling (`Ctrl+C`, `Ctrl+D`, `Ctrl+\`)


## ⚙️ Installation and use

Clone the repository and compile it using `make`:

```bash
git clone https://github.com/Pablo-VH/Minishell.git
cd Minishell
make && ./minishell
