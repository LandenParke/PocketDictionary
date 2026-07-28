POCKETDICT_REPO = https://github.com/LandenParke/PocketDictionary
NUTTX_DIR = PocketDictionary/NUTTXSIM/nuttx

PACKAGES = git \
	make \
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
	util-linux

.PHONY: all deps clone configure move_stuff running_sim

all: deps clone configure move_stuff running_sim

deps:
	@echo "Installing packages"
	sudo apt update
	sudo apt install -y $(PACKAGES)

clone:
	@echo "cloning repos"
	git clone $(POCKETDICT_REPO)
	mkdir -p nuttxspace

configure:
	cd $(NUTTX_DIR) && tools/configure.sh sim:sqlite

move_stuff:
	cp ./PocketDictionary/GUI/nuttxspace/.config $(NUTTX_DIR)/
	sudo mkdir -p /usr/nuttx_stuff
	sudo cp ./PocketDictionary/Dictionary_Resources/dict.db /usr/nuttx_stuff/

running_sim:
	cd $(NUTTX_DIR) && make && ./nuttx