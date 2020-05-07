# Get the base Ubuntu image from Docker Hub
FROM ubuntu:latest

#RUN find . -iwholename '*cmake*' -not -name CMakeLists.txt -delete

#install timezone
ENV TZ=Europe/Kiev
RUN ln -snf /usr/share/zoneinfo/$TZ /etc/localtime && echo $TZ > /etc/timezone
# Update apps on the base image
RUN apt-get -y update && apt-get install -y

# Install the Clang compiler
RUN apt-get -y install clang cmake python3-pip
RUN pip3 install conan

# Copy the current folder which contains C++ source code to the Docker image under /usr/src
COPY . app
# Specify the working directory
WORKDIR app

EXPOSE 8000
RUN cd src && conan install conanfile.txt --build missing

RUN cd src && mkdir build && ls && cd build && cmake ../ && cmake --build .

# Run the output program from the previous step
#CMD chmod 777 bin/timer
CMD build/bin/timer

#conan install conanfile.txt --build missing
#docker build -t docker-cpp-sample .
#RUN find . -iwholename '*cmake*' -not -name CMakeLists.txt -delete