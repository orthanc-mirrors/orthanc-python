FROM ubuntu:18.04

RUN export DEBIAN_FRONTEND=noninteractive
RUN apt-get --assume-yes update
RUN apt-get --assume-yes install build-essential
RUN apt-get --assume-yes install python-clang-4.0
RUN apt-get --assume-yes install python-pip
RUN apt-get --assume-yes install clang-4.0

# force pystache 0.5.0 (last version supported for python 2.7)
RUN pip install pystache==0.5.0

RUN mkdir /source
RUN mkdir /target
RUN mkdir /CodeAnalysis
COPY *.mustache /CodeAnalysis/
COPY *.py /CodeAnalysis/

ENTRYPOINT ["./CodeAnalysis/ParseOrthancSDK.py"]
CMD ["--libclang=libclang-4.0.so.1", "--source", "source/OrthancCPlugin.h", "--target", "target/"]
