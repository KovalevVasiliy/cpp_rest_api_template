# Get the base Ubuntu image from Docker Hub
FROM ubuntu:latest

#RUN find . -iwholename '*cmake*' -not -name CMakeLists.txt -delete

#install timezone
ENV TZ=Europe/Kiev
RUN ln -snf /usr/share/zoneinfo/$TZ /etc/localtime && echo $TZ > /etc/timezone
# Update apps on the base image
RUN apt-get -y update && apt-get install -y

# Install the Clang compiler
RUN apt-get -y install gcc cmake python3-pip
RUN pip3 install conan

# Copy the current folder which contains C++ source code to the Docker image under /usr/src
COPY . app
# Specify the working directory
WORKDIR app

EXPOSE 8000
#RUN cd src && conan install conanfile.txt
#--build missing

RUN cd src && conan install conanfile.txt && ls
RUN cd src && conan profile update settings.compiler.libcxx=libstdc++11 default
RUN cd src && ls && cmake . && ls && cmake --build .

#RUN app/src/bin/timer
#RUN cd src && mkdir build && mv conanfile.txt build && cd build && conan install conanfile.txt
#RUN cd src/build && cmake .. && make && make install

# Run the output program from the previous step
#CMD chmod 777 bin/timer
CMD src/bin/timer

#conan install conanfile.txt --build missing
#docker build -t docker-cpp-sample .
#RUN find . -iwholename '*cmake*' -not -name CMakeLists.txt -delete