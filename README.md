# Chiisho [Pocket Dictionary]
The Chiisho is a portable, pocket dictionary that is not reliant on internet and has all translation capabilities built in. Our repo provides the software for a full translation UI to be implemented on hardware. 

https://github.com/LandenParke/PocketDictionary

## Installation of local simulation
To use the simulation preview Chiisho on your local device, follow these steps.
The simulation requires Ubuntu architecture.
If you are using Windows, follow [this tutorial](https://ubuntu.com/wsl/docs/stable/howto/install-ubuntu-wsl2/#install-and-enable-wsl) for installing Ubuntu on WSL

Then download the Dockerfile [here](https://github.com/LandenParke/PocketDictionary/releases/download/Simulation/Dockerfile), make sure to place the file into a directory in Ubuntu if you are working on a different OS.

first run
```
docker --version
```
to see if you have docker, if you do not, run
```
sudo apt install docker.io
```

Make sure the Dockerfile has no extension such as .txt, then run the following commands in the directory with the file:
```
sudo docker build -t pocketdictionary .
xhost +local:docker
sudo docker run -it --rm \
    -e DISPLAY=$DISPLAY \
    -v /tmp/.X11-unix:/tmp/.X11-unix \
    pocketdictionary
```

Those commands should auto launch the ui, where you can interact with it via the command line.
Type out the romanji and it will appear on the UI, press enter to search.
Press '2' to go down through the options, and '1' to go up.
# Change me before submitting
