FROM centos:7

# Setup base system
RUN yum -y update
RUN yum -y install yum-utils wget fontconfig freetype freetype-devel fontconfig-devel libstdc++ libX11 mesa-libGL-devel fuse fuse-devel rpm-build libXcomposite libXcursor libXrender libX11-xcb libXi libXtst libXrandr libnotify-devel alsa-lib mesa-libEGL xorg-x11-drv-dummy
RUN yum -y groupinstall development

# Setup CMake
RUN yum -y install https://dl.fedoraproject.org/pub/epel/epel-release-latest-7.noarch.rpm
RUN yum -y install cmake3
RUN ln -s /usr/bin/cmake3 /usr/bin/cmake
RUN ln -s /usr/bin/ctest3 /usr/bin/ctest

# Setup C++17 compiler
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

# Setup Qt
COPY extract-qt-installer /
COPY install-qt.sh /
RUN chmod +x /install-qt.sh
RUN chmod +x /extract-qt-installer
RUN /install-qt.sh

# Setup DBus
RUN dbus-uuidgen > /etc/machine-id
RUN dbus-uuidgen --ensure=/etc/machine-id
