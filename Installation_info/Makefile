

NUTTX_REPO = https://github.com/apache/nuttx.git
NUTTXAPPS_REPO = https://github.com/apache/nuttx-apps

POCKETDICT_REPO = https://github.com/LandenParke/PocketDictionary


deps:
	@echo "Installing packages"
	sudo apt update
	xargs -a packages.txt sudo apt install -y

clone:
	@echo "cloning repos"
	git clone $(POCKETDICT_REPO)
	mkdir nuttxspace
	cd nuttxspace
	git clone $(NUTTX_REPO)
	git clone $(NUTTXAPPS_REPO)

configure:
	tools/configure.sh sim:sqlite
	

move_stuff:
	mv ./PocketDictionary/GUI/nuttxspace/.config ./nuttxspace/nuttx/.config
	mv ./PocketDictionary/GUI/fonts/jp_font_16_hiragana.c ./nuttxspace/apps/examples/lvgldemo/
	mv ./PocketDictionary/GUI/fonts/jp_font_24.c ./nuttxspace/apps/examples/lvgldemo/
	mv ./PocketDictionary/Dictionary_Resources/romaji.c ./nuttxspace/apps/examples/lvgldemo/
	mv ./PocketDictionary/Dictionary_Resources/romaji.h ./nuttxspace/apps/examples/lvgldemo/
	mv ./PocketDictionary/Dictionary_Resources/dict.h ./nuttxspace/apps/examples/lvgldemo/
	mv ./PocketDictionary/Dictionary_Resources/dict.c ./nuttxspace/apps/examples/lvgldemo/
	mv ./PocketDictionary/GUI/nuttxspace/jp_fonts.h ./nuttxspace/apps/examples/lvgldemo/
	mv ./PocketDictionary/GUI/nuttxspace/lvgldemo.c ./nuttxspace/apps/examples/lvgldemo/

running_sim:
	make
	./nuttx

