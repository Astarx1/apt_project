# FROM ubuntu

# RUN apt-get -qq update
# RUN apt-get install -y cmake
# RUN apt-get install -y g++ build-essential
# RUN echo "mysql-server mysql-server/root_password password root" | debconf-set-selections
# RUN echo "mysql-server mysql-server/root_password_again password root" | debconf-set-selections
# RUN apt-get install -y mysql-server
# RUN apt-get install -y libpthread-stubs0-dev
# RUN apt-get install -y libmysqlcppconn-dev

FROM installs

COPY . /home/api/

RUN /etc/init.d/mysql start

RUN cd /home/api/pistache/build && rm -rf ./*
RUN cd /home/api/pistache/build && cmake -G "Unix Makefiles" -DCMAKE_BUILD_TYPE=Release ..
RUN cd /home/api/pistache/build && make
RUN cd /home/api/pistache/build && make install

RUN ls /usr/include
RUN ls /usr/lib
RUN ls /usr/local/
RUN ls /usr/local/lib/

RUN rm -rf /home/api/*
COPY . /home/api/
RUN cd /home/api/build && rm -rf ./*
RUN cd /home/api/build && cmake ..
RUN cd /home/api/build && make

