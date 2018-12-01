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
