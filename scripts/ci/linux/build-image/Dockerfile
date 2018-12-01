FROM centos:7

# Setup base system
RUN yum -y update
RUN yum -y install yum-utils wget fontconfig freetype freetype-devel fontconfig-devel libstdc++ libX11 mesa-libGL-devel fuse fuse-devel xorg-x11-server-Xvfb rpm-build
RUN yum -y groupinstall development

# Setup Qt
COPY extract-qt-installer /
COPY install-qt.sh /
RUN chmod +x /install-qt.sh
RUN chmod +x /extract-qt-installer
RUN /install-qt.sh
RUN yum -y install https://dl.fedoraproject.org/pub/epel/epel-release-latest-7.noarch.rpm
RUN yum -y install cmake3
RUN ln -s /usr/bin/cmake3 /usr/bin/cmake
RUN yum -y install libnotify-devel
RUN yum -y install centos-release-scl
RUN yum -y install devtoolset-7-gcc-c++
RUN ls /opt/rh/devtoolset-7/root/bin
RUN ln -s /opt/rh/devtoolset-7/root/bin/gcc /usr/bin/gcc --force
RUN ln -s /opt/rh/devtoolset-7/root/bin/g++ /usr/bin/g++ --force
RUN ln -s /opt/rh/devtoolset-7/root/bin/cc /usr/bin/cc --force
RUN ln -s /opt/rh/devtoolset-7/root/bin/c++ /usr/bin/c++ --force
RUN ln -s /opt/rh/devtoolset-7/root/bin/cpp /usr/bin/cpp --force
RUN ln -s /opt/rh/devtoolset-7/root/bin/gcov /usr/bin/gcov --force
RUN ln -s /opt/rh/devtoolset-7/root/bin/strip /usr/bin/strip --force
RUN ln -s /opt/rh/devtoolset-7/root/bin/objcopy /usr/bin/objcopy --force
RUN ln -s /usr/bin/ctest3 /usr/bin/ctest
RUN yum -y install libXcomposite libXcursor libXrender libX11-xcb libXi libXtst libXrandr
RUN yum -y install alsa-lib mesa-libEGL
