# ros2 openvino toolkit env master f1b1ca4d914186a1881b87f103be9c6e910c9d80

from osrf/ros:jazzy-desktop-full

# Set non-interactive mode for APT
ENV DEBIAN_FRONTEND=noninteractive

# setting proxy env --option 
# If needed, enable the below ENV setting by correct proxies.
ENV http_proxy=http://proxy.png.intel.com:911
ENV https_proxy=http://proxy.png.intel.com:912

# maintainer information
LABEL maintainer="Jayabalaji Sathiyamoorthi <jayabalaji.sathiyamoorthi@intel.com>"

SHELL ["/bin/bash", "-c"]

# install openvino 2025.0.0
# https://docs.openvinotoolkit.org/latest/openvino_docs_install_guides_installing_openvino_apt.html
RUN apt update && apt install -y curl wget gnupg2 lsb-release
RUN wget https://apt.repos.intel.com/intel-gpg-keys/GPG-PUB-KEY-INTEL-SW-PRODUCTS.PUB && apt-key add GPG-PUB-KEY-INTEL-SW-PRODUCTS.PUB 
RUN echo "deb https://apt.repos.intel.com/openvino/2025 ubuntu22 main" | tee /etc/apt/sources.list.d/intel-openvino-2025.list   

RUN apt update \
    && apt-cache search openvino \ 
    && apt-get install -y openvino-2025.0.0
#    && apt-get install -y openvino-2024.2.0
#    && apt-get install -y openvino-2023.3.0 

# install librealsense2
# Reference : https://github.com/IntelRealSense/librealsense/blob/master/doc/distribution_linux.md
RUN apt-get install -y --no-install-recommends \
    software-properties-common \
    apt-transport-https \
    libyaml-cpp-dev \
    ros-jazzy-libyaml-vendor 

RUN apt-get install -y libssl-dev libusb-1.0-0-dev libudev-dev pkg-config libgtk-3-dev
RUN apt-get install -y git wget cmake build-essential

#build librealsense2
WORKDIR /root/
RUN git clone --branch v2.55.1 --single-branch https://github.com/IntelRealSense/librealsense.git
WORKDIR /root/librealsense
RUN mkdir build 
WORKDIR /root/librealsense/build 
RUN cmake ../
RUN make uninstall && make clean && make -j7 && make install

# build ros2 openvino toolkit
WORKDIR /root
RUN mkdir -p ros2_ws/src
WORKDIR /root/ros2_ws/src
RUN git clone https://github.com/intel/ros2_object_msgs.git
RUN git clone -b ros2_jazzy https://github.com/jb-balaji/ros2_openvino_toolkit.git
RUN git clone -b humble https://github.com/ros-perception/vision_opencv.git
WORKDIR /root/ros2_ws
RUN source /opt/ros/jazzy/setup.bash \
    && colcon build --cmake-args -DCMAKE_BUILD_TYPE=Release
