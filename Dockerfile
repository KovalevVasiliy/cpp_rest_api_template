# Get the base Ubuntu image from Docker Hub
FROM conanio/gcc7:latest

COPY ./src app
# Specify the working directory
WORKDIR app
EXPOSE 8000
USER root
RUN chmod 777 -R /home/conan/app
USER conan
#RUN conan profile update settings.compiler.libcxx=libstdc++11 default
RUN conan install . -s compiler.libcxx=libstdc++11 --build missing
RUN mkdir build && cd build && cmake .. && cmake --build .
CMD ["build/bin/timer"]

#conan install conanfile.txt --build missing
#docker build -t docker-cpp-sample .
#RUN find . -iwholename '*cmake*' -not -name CMakeLists.txt -delete