# FROM pistache
# FROM gpp
# FROM cmake

# Embedded in cmake
# FROM ubuntu

# RUN mkdir /home/api
# COPY . /home/api/

# RUN apt-get -qq update
# RUN apt-get install -y cmake

# Embedded in gpp 
# RUN apt-get install -y g++ build-essential

# Embedded in pistache
# FROM gpp
# RUN apt-get install -y libpthread-stubs0-dev

# RUN rm -rf /home/api/*
# COPY . /home/api/

# RUN cd /home/api/pistache/build && rm -rf ./*
# RUN cd /home/api/pistache/build && cmake -G "Unix Makefiles" -DCMAKE_BUILD_TYPE=Release ..
# RUN cd /home/api/pistache/build && make
# RUN cd /home/api/pistache/build && make install

# FROM pistache
# RUN apt-get install -y libmysqlcppconn-dev

# RUN ls /usr/include
# RUN ls /usr/lib
# RUN ls /usr/local/
# RUN ls /usr/local/lib/

FROM msql
RUN rm -rf /home/api/*
COPY . /home/api/
RUN cd /home/api/build && rm -rf ./*
RUN cd /home/api/build && cmake ..
RUN cd /home/api/build && make