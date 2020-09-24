FROM kdeneon/plasma

# Setup base system
RUN sudo apt -y update
COPY env-setup.sh /
RUN sudo chmod +x /env-setup.sh
RUN /env-setup.sh
RUN sudo apt -y install lcov
