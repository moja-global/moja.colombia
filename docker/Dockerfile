# ==================================================================================================================
#
# Docker to ubuntu 18.04 image for Moja libraries and executables
#
# Building this Docker: 
#   docker build --build-arg NUM_CPU=8 --build-arg GITHUB_AT=[TOKEN] --build-arg Moja_Branch=[BRANCH] -t moja/mai.colombia:bionic .
#
# ==================================================================================================================

FROM mojaglobal/baseimage:bionic

LABEL maintainer="info@moja.global"

ARG Moja_Branch=develop
ARG NUM_CPU=8
ARG DEBIAN_FRONTEND=noninteractive

ENV ZIPPER_VERSION 1.0.1
ENV ROOTDIR /usr/local

WORKDIR $ROOTDIR/src

# set environment variables
ENV PATH $ROOTDIR/bin:$PATH
ENV LD_LIBRARY_PATH $ROOTDIR/lib:$ROOTDIR/lib/x86_64-linux-gnu:$LD_LIBRARY_PATH
ENV PYTHONPATH $ROOTDIR/lib:$PYTHONPATH
ENV CURL_CA_BUNDLE /etc/ssl/certs/ca-certificates.crt
ENV GDAL_DATA=/usr/local/share/gdal
ENV GDAL_HTTP_VERSION 2
ENV GDAL_HTTP_MERGE_CONSECUTIVE_RANGES YES
ENV GDAL_HTTP_MULTIPLEX YES

RUN apt-get update -y && apt-get install -y doxygen doxygen-latex graphviz\
        postgis \
	&& 	apt-get clean

RUN	git clone --recursive https://github.com/sebastiandev/zipper.git \
	&& cd zipper && git checkout e9f150516cb55d194b5e01d21a9527783e98311d && mkdir build  && cd build \
	&& cmake .. \
	&& make --quiet -j $NUM_CPU \
    && make --quiet install/strip \
    && make clean \
    && cd $ROOTDIR/src

RUN git clone --recursive --depth 1 -b ${Moja_Branch} https://github.com/moja-global/FLINT.git moja.global \
    && mkdir -p moja.global/Source/build && cd moja.global/Source/build \
    && cmake -DCMAKE_BUILD_TYPE=RELEASE  \
            -DCMAKE_INSTALL_PREFIX=$ROOTDIR \
            -DENABLE_TESTS:BOOL=OFF \
            -DENABLE_MOJA.MODULES.GDAL=ON \
            -DENABLE_MOJA.MODULES.LIBPQ=ON \
            -DBoost_USE_STATIC_LIBS=OFF \
            -DBUILD_SHARED_LIBS=ON .. \
	&& make --quiet -j $NUM_CPU \
	&& make --quiet install/strip \
	&& make clean \
    && cd $ROOTDIR/src    

# MAI.Colombia
ARG GITHUB_AT
RUN git clone --recursive --depth 1 https://${GITHUB_AT}@github.com/MullionGroup/MAI.Colombia.git MAI.Colombia \
    && mkdir -p MAI.Colombia/source/build && cd MAI.Colombia/source/build \
    && cmake -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=$ROOTDIR \
            -DBUILD_SHARED_LIBS=ON \
            -DBoost_USE_STATIC_LIBS=OFF \
            -DENABLE_TESTS:BOOL=OFF .. \
	&& make --quiet -j $NUM_CPU \
	&& make --quiet install/strip \
	&& make clean \
   && cd $ROOTDIR/src    

RUN ln -s $ROOTDIR/lib/libmoja.modules.* $ROOTDIR/bin	

ENV LC_ALL=C.UTF-8
ENV LANG=C.UTF-8

RUN pip3 install setuptools
RUN git clone --recursive --depth 1 -b ${Moja_Branch}  https://github.com/moja-global/FLINT.data.git FLINT.data \
    && cd FLINT.data \
    && pip3 install .

RUN rm -Rf $ROOTDIR/src/* \
    && ldconfig

RUN useradd -ms /bin/bash moja
USER moja
WORKDIR /home/moja



