FROM ubuntu

RUN apt-get -qq update
RUN apt-get install -y cmake
RUN apt-get install -y g++ build-essential
# RUN echo "mysql-server mysql-server/root_password password root" | debconf-set-selections
# RUN echo "mysql-server mysql-server/root_password_again password root" | debconf-set-selections
# RUN apt-get install -y mysql-server
RUN apt-get install -y libpthread-stubs0-dev
RUN apt-get install -y libmysqlcppconn-dev

# FROM installs2

COPY . /home/api/

RUN cd /home/api/pistache/build && rm -rf ./*
RUN cd /home/api/pistache/build && cmake -G "Unix Makefiles" -DCMAKE_BUILD_TYPE=Release ..
RUN cd /home/api/pistache/build && make
RUN cd /home/api/pistache/build && make install

RUN cd /home/api/build && rm -rf ./*
RUN cd /home/api/build && cmake ..
RUN cd /home/api/build && make

EXPOSE 9080
