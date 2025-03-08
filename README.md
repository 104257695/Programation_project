<<<<<<< HEAD
<img src="docs/header.png" width="100%" />

# Assignment 0: Setup!

Due Friday, January 17th at 11:59PM

## Overview

Welcome to CS106L! This assignment will get you setup for the rest of the quarter so that setup for the rest of the assignments is simple and smooth. By the end of this assignment, you should be able to compile and run C++ files from VSCode and run the autograder, which you'll be doing for each of the remaining assignments!

If you run into any issues during setup, please reach out to us on [EdStem](https://edstem.org/us/courses/72089/discussion) or come to our office hours!

## Part 1: Installing Python

### Part 1.1: Checking for an existing Python installation

The autograder for each assignment in CS106L uses Python. You must have a Python installation of version `3.8` or higher. To check your Python version you can run the following in your terminal:

If you're on Linux or Mac:

```sh
python3 --version
```

If you're on Windows:

```sh
python --version
```

If you get a version that is `3.8` or higher, then you're good, **you can continue to Part 2**. Otherwise, please follow Part 1.2 to install Python on your machine.

### Part 1.2: Installing Python (if you don't already have it installed)

#### Mac & Windows

Please download the latest Python version [here](https://www.python.org/downloads/) and run the installer. **Note: on Windows, you must check `Add python.exe to PATH` in the installer**. After installing, verify that the installation worked by following the steps in **Part 1.1**.

#### Linux

These instructions are for Debian-based distributions, like Ubuntu. Tested on Ubuntu 20.04 LTS.

1. Update the Ubuntu package lists by running

    ```sh
    sudo apt-get update
    ```

2. Install Python:

    ```sh
    sudo apt-get install python3 python3-venv
    ```

3. Restart your terminal and verify that the installation worked by running:

    ```sh
    python3 --version
    ```

## Part 2: Setup VSCode and C++ Compiler

We will use VSCode to write C++ code for this class. Below are instructions to setup VSCode along with the GCC compiler for your machine.

### Mac

#### Step One: Installing VSCode

Go to [this link](https://code.visualstudio.com/docs/setup/mac)
and download Visual Studio Code for Mac. Follow the instructions on this webpage under the
section **Installation**.

Inside VSCode, head to the extensions tab <img src="docs/vscode-extensions.png" display="inline" height="20px"></img> and search for **C/C++**. Click on the **C/C++** extension, and then click **Install**.

Finally, open the command palette (<kbd>Cmd+Shift+P</kbd>), search for `Shell Command: Install 'code' command in PATH`, and select it. This will allow you to launch VSCode directly from the terminal by running the `code` command.

**🥳 At this point you should successfully have VSCode on your Mac 👏**

#### Step Two: Installing a C++ Compiler

1. Check if you have Homebrew by running 

    ```sh
    brew --version
    ```

   If you get something like

   ```sh
    brew --version
    Homebrew 4.2.21
   ```

   then skip ahead to step 3. If you get anything else that looks suspicious, proceed to step 2!

2. Run this command:

    ```sh
    /bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"
    ```

    which will download Homebrew🍺, a package manager for Mac. Woot woot.

3. Run the following command:

    ```sh
    brew install gcc
    ```

    which will install the GCC compiler on your machine.

4. Make note of which GCC version Homebrew installs. In most cases, this will be `g++-14`. 
    By default, the `g++` command on Mac is an alias to the built-in `clang` compiler. We can fix this by running 
    
    ```sh
    echo 'alias g++="g++-14"' >> ~/.zshrc
    ```
    
    to make `g++` point to the version of GCC we just installed. Change `g++-14` in the above command to whichever version of GCC was installed.

5. Restart your terminal and verify that everything worked by running the following command:

    ```sh
    g++ --version
    ```

### Windows

#### Step One: Installing VSCode

Go to [this link](https://code.visualstudio.com/docs/setup/windows)
and download Visual Studio Code for Windows. Follow the instructions on this webpage under the
section **Installation**.

Inside VSCode, head to the extensions tab <img src="docs/vscode-extensions.png" display="inline" height="20px"></img> and search for **C/C++**. Click on the **C/C++** extension, and then click **Install**.

**🥳 At this point you should successfully have VSCode on your PC 👏**

#### Step Two: Installing a C++ Compiler

1. Follow the instructions at [this link](https://code.visualstudio.com/docs/cpp/config-mingw) under the section **Installing the MinGW-w64 toolchain.**

2. After fully following the instructions under **Installing the MinGW-w64 toolchain** you should now be able to verify everything worked by running the following command:

    ```sh
    g++ --version
    ```

### Linux

These instructions are for Debian-based distributions, like Ubuntu. Tested on Ubuntu 20.04 LTS.

#### Step One: Installing VSCode

Go to [this link](https://code.visualstudio.com/docs/setup/linux)
and download Visual Studio Code for Linux. Follow the instructions on this webpage under the section **Installation**.

Inside VSCode, head to the extensions tab <img src="docs/vscode-extensions.png" display="inline" height="20px"></img> and search for **C/C++**. Click on the **C/C++** extension, and then click **Install**.

Finally, open the command palette (<kbd>Ctrl+Shift+P</kbd>), search for `Shell Command: Install 'code' command in PATH`, and select it. This will allow you to launch VSCode directly from the terminal by running the `code` command.

**🥳 At this point you should successfully have VSCode on your Linux machine 👏**

#### Step Two: Installing a C++ Compiler

1. In a terminal, update the Ubuntu package lists by running

    ```sh
    sudo apt-get update
    ```

2. Next install the `g++` compiler: 

    ```sh
    sudo apt-get install g++-10
    ```

3. By default, the system version of `g++` will be used. To change it to the version you just installed, you can configure Linux to use G++ version 10 or a higher version installed like so: 

    ```sh
    sudo update-alternatives --install /usr/bin/g++ g++ /usr/bin/g++-10 10
    ```

4. Restart your terminal and verify that GCC was installed correctly. You must have a `g++` version of 10 or higher: 

    ```sh
    g++ --version
    ```

## Part 3: Cloning the class code via Git!

Git is a popular VCS (version control system) that we will use to distribute starter codes for the assignments. Make sure that you have Git installed by running

```sh
git --version
```

If you see anything that looks off, [download and install Git from this page](https://git-scm.com/downloads)!

### Download the starter code

Open VSCode, and then open a terminal (hit <kbd>Ctrl+\`</kbd> or go to **Terminal > New Terminal** at the top of the window) and run the following command:

```sh
git clone https://github.com/cs106l/cs106l-assignments.git
```

which will download the starter code into a folder `cs106l-assignments`. 

### Opening a VSCode workspace

When working on assignments in this class, we recommend you open up a VSCode workspace for the specific assignment folder you are working on. So if you now have a folder `cs106l-assignments`, you can first `cd` (change directory) into the correct folder:

```sh
cd cs106l-assignments/assign0
```

which changes your working directory to `assign0`, and then you can open up a VSCode workspace dedicated to this folder:

```sh
code .
```

and now you should be ready to go!

### Fetching assignments

As we update existing assignments and release new ones, we will push updates to this repository. To fetch a new assignment, open up a terminal to your `cs106l-assignments` directory and run

```sh
git pull origin main
```

You should now have the latest starter code!

# Part 4: Testing your setup!

Now we will have you compile your first C++ file and run the autograder. To run any C++ code, first you'll need to compile it. Open up a VSCode terminal (again, hit <kbd>Ctrl+\`</kbd> or go to **Terminal > New Terminal** at the top of the window). Then make sure that you are in the `assign0/` directory and run:
=======
<p align="center">
  <img src="docs/marriage_pact.png" alt="Marriage Pact Logo" />
</p>

# Assignment 2: Marriage Pact

Due Friday, January 31st at 11:59PM

## Overview

Happy assignment 2! This is meant to be a very short and sweet bit of practice to get you started working with the STL’s containers and pointers.

These are the files you need to care about:

- `main.cpp`: All your code goes here 😀!
- `short_answer.txt`: Short answer responses go here 📝!

To download the starter code for this assignment, please see the instructions for [**Getting Started**](../README.md#getting-started) on the course assignments repository.

## Running your code

To run your code, first you'll need to compile it. Open up a terminal (if you are using VSCode, hit <kbd>Ctrl+\`</kbd> or go to **Terminal > New Terminal** at the top). Then make sure that you are in the `assign2/` directory and run:
>>>>>>> 9a663b0 (assign 2)

```sh
g++ -std=c++20 main.cpp -o main
```

<<<<<<< HEAD
This **compiles** the C++ file `main.cpp` into an executable file called `main` which contains raw machine code that your processor can execute. Assuming that your code compiles without any errors, you can now do:
=======
Assuming that your code compiles without any compiler errors, you can now do:
>>>>>>> 9a663b0 (assign 2)

```sh
./main
```

<<<<<<< HEAD
which will actually run the `main` function in `main.cpp`. This will execute your code and then run an autograder that will check that your installation is correct.
=======
which will actually run the `main` function in `main.cpp`.

As you are following the instructions below, we recommend intermittently compiling/testing with the autograder as a way to make sure you're on the right track!
>>>>>>> 9a663b0 (assign 2)

> [!NOTE]
>
> ### Note for Windows
>
> On Windows, you may need to compile your code using
>
> ```sh
> g++ -static-libstdc++ -std=c++20 main.cpp -o main
> ```
>
> in order to see output. Also, the output executable may be called `main.exe`, in which case you'll run your code with:
>
> ```sh
> ./main.exe
> ```
<<<<<<< HEAD
> 

> [!NOTE]
>
> ### Note for Mac
>
> You may get a compiler error when attempting to compile this code due to a missing `wchar.h` (or some similar file). If this happens, you may need to reinstall the Xcode command line tools on your machine by running the following commands:
>
> ```sh
> sudo rm -rf /Library/Developer/CommandLineTools
> sudo xcode-select --install
> ```
>
> Afterwards, you should be able to compile normally.

# 🚀 Submission Instructions

After compiling and running, if your autograder looks like this:

![An image showing a terminal window where the autograder has run with all tests passing](docs/autograder.png)

then you have finished the assignment! Woot woot. To submit the assignment, please complete the feedback form [at this link](https://forms.gle/QNedgpAXdVHipZgYA)!
=======

## Part 0: Setup

Welcome to the Marriage Pact! Before you begin, we'll need to know your name. Please change the constant `kYourName` at the top of `main.cpp` from `"STUDENT TODO"` to your full name (with a space between first and last).

## Part 1: Get all applicants

You’ve been waiting for days to get your Marriage Pact initials this year, and they’ve finally arrived in your inbox! This year, they’re implementing a new rule: your match MUST share your own initials to be eligible. However, even after talking about it for hours with your friends, you have no idea who your match could be! There are thousands of students on campus, and you can’t just go through the whole roster by hand to draft up a list of your potential soulmates. Fortunately enough for you, you’re in CS106L, and you remember that C++ has a pretty quick method of going through collected, similar information – containers!

We’ve included a `.txt` file of all of the (fictional) students who signed up for The Marriage Pact this year (`students.txt`). Each line includes the first and last name of the student. You will first write the function `get_applicants`:

> [!IMPORTANT]
>
> ### `get_applicants`
>
> From the `.txt` file, parse all of the names into a set. Each line contained in the file named `filename` is a single applicant's name. In your implementation, you are free to choose between an ordered (`std::set`) and unordered set (`std::unordered_set`) as you wish! If you do choose to use an unordered set, please change the relevant function definitions!

Additionally, please answer the following short answer question in `short_answer.txt`:

> [!IMPORTANT]
>
> ### `short_answer.txt`
>
> **Q1:** It is your choice to use either an ordered or unordered set. In a few sentences, what are some of the tradeoffs between the two? Additionally, please give an example (that has not been shown in lecture) of a valid hash function that could be used to hash student names for an unordered set.

> [!NOTE]
> All names appearing in this assignment are fictitious. Any resemblance to real persons, living or dead, is purely coincidental.

## Part 2: Find matches

Great detective work! Now that you’ve narrowed down your list of potential soulmates, it’s time to put it to the test. After a long day of acapella and consulting club meetings, you return to your dorm to learn from your roommate that there is a mixer for Marriage Pact matches at Main Quad that night! Your best chance of finding true love is imminent — if only you can get out of your Ultimate Frisbee practice. Quickly, you decide to interview everyone who shares your initials at the mixer, and you get to work coding up a function that will compile the order for you automatically.

For this section, you will write the functions `find_matches` and `get_match`:

> [!IMPORTANT]
>
> ### `find_matches`
>
> From the set `students` (generated in the previous part), take all names that share initials with the parameter `name` and place pointers to them in a new `std::queue`.
>
> - If you’re having trouble figuring out how to iterate through a set, it could be helpful to look back over [Thursday’s lecture on iterators and pointers](https://office365stanford-my.sharepoint.com/:p:/g/personal/jtrb_stanford_edu/EbOKUV784rBHrO3JIhUSAUgBvuIGn5rSU8h3xbq-Q1JFfQ?e=BlZwa7).
> - You will need to be familiar with the operations of a `std::queue` for this part. Take a look at cppreference's documentation [here](https://en.cppreference.com/w/cpp/container/queue).
> - Hint: It might help to define a helper function that computes the initials of some student's name. Then you can use that helper function to compare the initials of `name` with the initials of each name in `students`.

From here please implement the function `get_match` to find your “one true match.”:

> [!IMPORTANT]
>
> ### `get_match`
>
> Gets your “one true match” from the queue of all possible matches. This can be determined as you see fit; choose some method of acquiring one student from the queue, ideally something with a bit more thought than a single `pop()`, but it doesn’t have to be particularly complicated! Consider random values or other methods of selection.
>
> If your initials have no matches in the dataset, print `“NO MATCHES FOUND.”` Better luck next year 😢

Afterwards, answer the following question in `short_answer.txt`:

> [!IMPORTANT]
>
> ### `short_answer.txt`
>
> **Q2:** Note that we are saving pointers to names in the queue, not names themselves. Why might this be desired in this problem? What happens if the original set where the names are stored goes out of scope and the pointers are referenced?

## 🚀 Submission Instructions

Before you submit the assignment, please fill out this [short feedback form](https://forms.gle/8sPwrAsMKMspPShc8). **Completion of the form is required to receive credit for the assignment.** After filling out the form, please upload the files to Paperless under the correct assignment heading.

Your deliverable should be:

- `main.cpp`
- `short_answer.txt`

You may resubmit as many times as you'd like before the deadline.
>>>>>>> 9a663b0 (assign 2)
