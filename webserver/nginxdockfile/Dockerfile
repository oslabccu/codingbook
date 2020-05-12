FROM linuxserver/nginx
RUN wget https://www.python.org/ftp/python/3.6.5/Python-3.6.5.tgz
RUN apk add build-base	
RUN apk add zlib-dev
RUN tar xvf Python-3.6.5.tgz	
WORKDIR /Python-3.6.5
RUN  ./configure --enable-optimizations --with-ensurepip=install
RUN make -j 8
RUN make altinstall
WORKDIR /usr/local/bin
RUN ln -s python3.6 python
