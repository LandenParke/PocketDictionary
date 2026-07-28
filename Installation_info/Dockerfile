FROM ubuntu:latest

ENV DEBIAN_FRONTEND=noninteractive

# Install all required build dependencies
RUN apt-get update && apt-get install -y \
    git \
    curl \
    sqlite3 \
    libsqlite3-dev \
    kconfig-frontends \
    bison \
    flex \
    gettext \
    texinfo \
    libncurses5-dev \
    libncursesw5-dev \
    xxd \
    gperf \
    automake \
    libtool \
    pkg-config \
    build-essential \
    genromfs \
    libgmp-dev \
    libmpc-dev \
    libmpfr-dev \
    libisl-dev \
    binutils-dev \
    libelf-dev \
    libexpat1-dev \
    gcc-multilib \
    g++-multilib \
    picocom \
    u-boot-tools \
    util-linux \
    tcl \
    unzip \
    cargo \
    && rm -rf /var/lib/apt/lists/*

# Install Rust toolchain for cargo/libromaji
RUN curl --proto '=https' --tlsv1.2 -sSf https://sh.rustup.rs | sh -s -- -y
ENV PATH="/root/.cargo/bin:${PATH}"

WORKDIR /home/build

# Clone the PocketDictionary repo
RUN git clone https://github.com/LandenParke/PocketDictionary

WORKDIR /home/build/PocketDictionary/NUTTXSIM/nuttx

# Configure NuttX for the sqlite simulator
RUN tools/configure.sh sim:sqlite

# Copy in the app-specific config
RUN cp ../../GUI/nuttxspace/.config .

# Install the dictionary database
RUN mkdir -p /usr/nuttx_stuff \
    && cp ../../Dictionary_Resources/dict.db /usr/nuttx_stuff/

# Build the binary
RUN make

# On container start: launch the simulator and auto-run lvgldemo
CMD ["bash", "-c", "(sleep 1; echo lvgldemo) | ./nuttx"]
