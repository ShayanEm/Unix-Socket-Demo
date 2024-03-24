# C++ Client/Server Application
This project is a C++ client/server application that communicates over a UNIX domain socket.

## Requirements
### Common

Errors are printed on stderr.
The application runs on a Linux-based operating system.

### Server

The server listens on a UNIX socket.
The path to the socket is provided as a command line argument.
If an error occurs while listening to the socket, the program stops with a positive error code and a log message explaining the error.
The server creates the socket if it does not exist.
The server supports the ‘VERSION’ command.
It replies to the client with the git string version of the application.
The “git string” is the full hash of the latest commit the application was compiled against.
The server replies ‘REJECTED’ if the command is not supported.

### Client

The client connects on the UNIX socket.
The path is provided as a command line argument.
If an error occurs while connecting to the socket, the program stops with a positive error code and a log message explaining the error.
The client allows sending text-based commands.
The command is provided as a command line argument.
The client command results are printed on stdout.

## Installation and Setup manually
Before you can build and run the application, you need to install the necessary tools and libraries. Here’s how you can do it:

1. Install CMake: CMake is used for managing the build process of the software. You can install it using the package manager of your Linux distribution. For example, on Ubuntu, you can use the following command:

    $ sudo apt-get install cmake

2. Install GCC: GCC is the GNU Compiler Collection. It includes compilers for various programming languages, including C++. You can install it using the package manager of your Linux distribution. For example, on Ubuntu, you can use the following command:

    $ sudo apt-get install build-essential

3. Clone the Repository: Clone this repository to your local machine using the following command:

    $ git clone https://github.com/ShayanEm/Unix-Socket-Demo.git

## Building the Application Manually
After you have installed the necessary tools and libraries, you can build the application using the following steps:

1. Navigate to the Project Directory: Use the cd command to navigate to the project directory:

    $ cd project-directory

2. Create a Build Directory: Create a new directory named build in the project directory:

    $ mkdir build

3. Navigate to the Build Directory: Use the cd command to navigate to the build directory:
    
    $ cd build

4. Run CMake: Run the cmake command to generate the Makefile:

    $ cmake ..

5. Build the Application: Run the make command to build the application:

    $ make

6. You need to do step 1 to 5 for each CMakelists (3 times in 3 different directories):
    -Unix-Socket-Demo/
    -server/
    -client/
    
7. After you have built the application, you can run it using the following command:
    
    $ cd build
    
    $ ./executable arguments

    Replace `executable-name` with the name of the server or client executable, and `command-line-arguments` with the appropriate command-line arguments. Run server before client. Replace `/path` with the path where you want to create the socket.

    For server:

    $ ./server /path/socket &

    For client:

    $ ./client /path/socket COMMAND

## Installation and Setup Docker
Before you can build and run the Dockerfile, you need to install the necessary tools and libraries. Here’s how you can do it:
1. Update your existing list of packages:
    
    $ sudo apt update

2. Install Docker:

    $ sudo apt install docker.io

3. Install additional pakages

    $ sudo snap install docker

4. To use Docker without sudo, add your user to the docker group (Remember to log out and back in for this to take effect! ): USER has a dollar sign behind it!

    $ sudo usermod -aG docker {USER}

5. Clone the Repository: Clone this repository to your local machine using the following command:

    $ git clone https://github.com/ShayanEm/Unix-Socket-Demo.git

## Building the Application Docker
After you have installed the necessary tools and libraries, you can build the application using the following steps:

1. Build the dockerfile using this command: Replace `/path` with the path where you want to create the socket and `my-image` with the name you want to use for your Docker image:

    $ docker build --build-arg SOCKET-PATH=/path/socket -t my-image .

2. Run the container: Replace `my-app` and `my-image` with the name you want to use for your Docker container:

    $ sudo docker run -d --name my-app my-image /bin/bash -c "while true; do sleep 1000; done"

3. Run the server application: replace `/path` with the path where you want to create the socket:

    $ sudo docker exec my-app ./server/build/server /path/socket &

4. Run the client application: replace `my-app` and `COMMANDE` and `/path` with your arguments:

    $ docker exec my-app ./client/build/client /path/socket COMMANDE

5. Once you are done with the application, close the running container:

    $ docker stop container-name_or_id

6. Check for running containers:

    $ docker ps

## Expected Results
When you run the server, it listens on the specified UNIX socket and waits for connections from clients. When a client connects and sends a command, the server processes the command and sends a response back to the client. The client then prints the response on stdout.

If the client sends the ‘VERSION’ command, the server responds with the git string version of the application. If the client sends an unsupported command, the server responds with ‘REJECTED’.

If an error occurs while the server is listening to the socket or the client is connecting to the socket, the program stops with a positive error code and a log message explaining the error.