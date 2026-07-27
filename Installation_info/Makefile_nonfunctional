POCKETDICT_REPO = https://github.com/LandenParke/PocketDictionary
deps:
	@echo "Installing packages"
	sudo apt update
	xargs -a packages.txt sudo apt install -y

clone:
	@echo "cloning repos"
	git clone $(POCKETDICT_REPO)
	mkdir nuttxspace
	cd ./PocketDictionary/NUTTXSIM/nuttx


configure:
	tools/configure.sh sim:sqlite
	

move_stuff:
	cd ..
	cd ..
	cd ..
	cp ./PocketDictionary/GUI/nuttxspace/.config ./PocketDictionary/NUTTXSIM/nuttx/
	sudo mkdir /usr/nuttx_stuff
	sudo cp ./PocketDictionary/Dictionary_Resources/dict.db /usr/nuttx_stuff/
	cd PocketDictionary/NUTTXSIM/nuttx/
	

running_sim:
	make
	./nuttx

