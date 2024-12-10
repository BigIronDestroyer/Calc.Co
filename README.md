# Calc.Co
Welcome to the official page for EECS 348 Group 8's Calculator Project! We’re excited to share our journey as we work together to create a reliable and efficient calculator, our team is focused on developing a tool that’s user-friendly and effective, with features designed to simplify calculations and make your life easier. Stay tuned for updates as we bring this project to life!

## How to Setup CalcCo

### For Developers

#### Requirments 

clang++/g++ version 16.0.0

For ease of development this project uses GNU Make for building and compiling:
    * Linux: run ```apt install make```
    * MacOS: ```brew install make ```
    * Windows: If you have Git for Windows installed, you can use the make command from Git Bash.

#### Get Started

For developers to get started first you need to clone this directory and then change the directory to the program folder

In your terminal or command prompt run the following:

```
git clone https://github.com/BigIronDestroyer/Calc.Co.git
cd Calc.co
```

Then run: 
```
make all
``` 

or 

```
make CalcCo
```

This will compile all the necessary files to build the CalcCo

Afterwards to run the CalcCo program:

```
./bin/CalcCo
```

## How to Use CalcCo
After running the program you will be met with the following prompts:

```
Enter a Mathematical Equation (! to quit):
```

Enter the equation you desire to be solved for example:

```
Enter a Mathematical Equation (! to quit): 20/10

```
Once you hit the enter key CalcCo calculates the solution to the equation and prints it out in the terminal

or to quit the program

```
Enter a Mathematical Equation (! to quit): !
```

### Operator Support Status 
Currently, CalcCo has support for:
* addition (+)
* subtraction (-)
* multiplication (*)
* division (/)
* exponents (**)
* modulo (%)

The current iteration does not follow PEMDAS; it only supports left-to-right calculations. Future support for PEMDAS is planned.

<br>
<br>
<br>

<p align="center">
<img src="./assets/Logo.png">
</p>
