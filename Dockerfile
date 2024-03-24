# Use an officiel Ubuntu runtime as a parent image
FROM ubuntu:latest

# set the working directory in the container to /app
WORKDIR /app

# Copy the current directory into the container at /app
COPY . /app

# Intall any needed pakages required
RUN apt-get update && \
    apt-get install -y gcc g++ cmake && \
    if [ -d "build" ]; then rm -Rf build; fi && \
    mkdir build &&\
    cd build && \
    cmake .. && \
    make && \
    cd .. && \
    cd client && \
    if [ -d "build" ]; then rm -Rf build; fi && \
    mkdir build &&\
    cd build && \
    cmake .. && \
    make && \
    cd ../.. && \
    cd server && \
    if [ -d "build" ]; then rm -Rf build; fi && \
    mkdir build &&\
    cd build && \
    cmake .. && \
    make

# Make port 80 available to the world outside this container
EXPOSE 80

# Use an environment variable for the socket path
ARG SOCKET_PATH
ENV SOCKET_PATH ${SOCKET_PATH}

# Run server.cpp when the container lunches
CMD [ "./server/build/server", "${SOCKET_PATH}" ]
