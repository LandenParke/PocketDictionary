# Chiisho [Pocket Dictionary]
The Chiisho is a portable, pocket dictionary that is not reliant on internet and has all translation capabilities built in. Our repo provides the software for a full translation UI to be implemented on hardware. 

https://github.com/LandenParke/PocketDictionary

## Installation of local simulation
To use the simulation preview Chiisho on your local device, follow these steps.
The sim runs inside Docker, so first you will need to prep your OS.
## Linux Ubuntu
No extra setup needed

## Windows
You have two options, either run Ubuntu on WSL, or run natively on Windows.
If you are using WSL, no additional setup is needed after setup, follow [this tutorial](https://ubuntu.com/wsl/docs/stable/howto/install-ubuntu-wsl2/#install-and-enable-wsl) for installing Ubuntu on WSL

If not using WSL, follow these steps
1. Install [Docker Desktop](https://www.docker.com/products/docker-desktop/) for Windows.
2. Install an X server such as [VcXsrv](https://sourceforge.net/projects/vcxsrv/).
3. Launch VcXsrv (via XLaunch) with **"Disable access control"** checked, so Docker is allowed to connect.
4. When you get to the `docker run` step below, use the **native Windows** command block (it points `DISPLAY` at your host machine instead of `$DISPLAY`).

## MacOS
Docker containers can't draw windows on macOS directly, so you'll need an X11 server:

1. Install [XQuartz](https://www.xquartz.org/) and restart your Mac after installing.
2. Open XQuartz, go to **Settings → Security**, and check **"Allow connections from network clients."**
3. Restart XQuartz for the setting to take effect.
4. In Terminal, run:
   ```
   xhost + 127.0.0.1
   ```
5. When you get to the `docker run` step below, use the **macOS** command block (it sets `DISPLAY` differently than Linux).

## Build and Run

Download the Dockerfile
### [HERE](https://github.com/LandenParke/PocketDictionary/releases/download/Simulation/Dockerfile) 
make sure to place the file into a directory in Ubuntu (or WSL2/Linux) if you are working on a different OS.

first run
```
docker --version
```
to see if you have docker, if you do not, run
```
sudo apt install docker.io
```

Make sure the Dockerfile has no extension such as .txt, then run the following in the directory with the file:
```
sudo docker build -t pocketdictionary .
```

Then run the container using the command block for your OS:

**Linux / WSL2:**
```
xhost +local:docker
sudo docker run -it --rm -e DISPLAY=$DISPLAY -v /tmp/.X11-unix:/tmp/.X11-unix pocketdictionary
```

**macOS:**
```
sudo docker run -it --rm -e DISPLAY=host.docker.internal:0 pocketdictionary
```

**Native Windows (no WSL, using VcXsrv):**
Find your machine's IP address first (`ipconfig`, look for your active adapter's IPv4 address), then run:
```
docker run -it --rm -e DISPLAY=YOUR_IP_ADDRESS:0.0 pocketdictionary
```

Those commands should auto launch the ui, where you can interact with it via the command line.
Type out the romanji and it will appear on the UI, press enter to search.
Press '2' to go down through the options, and '1' to go up.
# Change me before submitting
