# Calc.Co
Welcome to the official page for EECS 348 Group 8's Calculator Project! We’re excited to share our journey as we work together to create a reliable and efficient calculator, our team is focused on developing a tool that’s user-friendly and effective, with features designed to simplify calculations and make your life easier. Stay tuned for updates as we bring this project to life!

## How to Use CalcCo
After downloading CalcCo open a terminal in the folder it was downloaded in then run:
```
> ./CalcCo
```

After running the program you will be met with the following prompted:

```
Enter a Mathimatical Equation (Q or q to quit):
```

Simply enter an equation to you desire to be solved for example:

```
Enter a Mathimatical Equation (Q or q to quit): (20/10) + (2**3)-8

```
Once you hit the enterf key the CalcCo calculate to solution to the equation an print it out in the terminal or return an appriate error message.

or to quit the program

```
Enter a Mathimatical Equation (Q or q to quit): q
```

## How to Setup CalcCo

### For Developers

#### Requirments 

clang++/g++ version 16.0.0

For ease of development this project uses GNU Make for building and compiling:
    * Linux: run ```apt install make```
    * MacOS: ```brew install make ```
    * Windows: If you have Git for Windows installed, you can use the make command from Git Bash.

#### Get Started

For developers to get started first you need to clone this directory then change directory to the program folder

In your terminal or command promt run the following:

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

To remove all *.o and executable, run:
```
make clean clear
```

This will compile all the neccesary files to build the CalcCo

Afterwards to run the CalcCo program:

```
./bin/CalcCo
```

### Operator Support Status 
Currently CalcCo has support for:
* addition (+)
* subtraction (-)
* multiplication (*)
* division (/)
* exponents (**)
* modulo (%)

<br>
<br>
<br>

<p align="center">
<img src="./assets/Logo.png">
</p>
