# Chiisho [Pocket Dictionary]

The Chiisho is a portable, pocket dictionary that is not reliant on internet and has all translation capabilities built in. Our repo provides the software for a full translation UI to be implemented on hardware.

https://github.com/LandenParke/PocketDictionary

## Installation of local simulation

To use the simulation preview Chiisho on your local device, follow these steps.
The sim runs inside Docker, so first you will need to prep your OS.

## Linux Ubuntu

No extra setup needed.

## Windows

You have two options, either run Ubuntu on WSL, or run natively on Windows.

If you are using WSL, no additional setup is needed after setup. Follow [this tutorial](https://ubuntu.com/wsl/docs/stable/howto/install-ubuntu-wsl2/#install-and-enable-wsl) for installing Ubuntu on WSL.

If not using WSL, follow these steps:

1. Install [Docker Desktop](https://www.docker.com/products/docker-desktop/) for Windows.
2. Install an X server such as [VcXsrv](https://sourceforge.net/projects/vcxsrv/).
3. Launch VcXsrv (via XLaunch) with **"Disable access control"** checked, so Docker is allowed to connect.
4. When you get to the `docker run` step below, use the **native Windows** command block (it points `DISPLAY` at your host machine instead of `$DISPLAY`).

## MacOS

Docker containers can't draw windows on macOS directly, so you'll need an X11 server:

1. Install [XQuartz](https://www.xquartz.org/). If you have Homebrew you can also run `brew install --cask xquartz`. Log out of macOS and back in after installing.
2. Launch XQuartz by running `open -a XQuartz`, or by opening it from Applications. Once it is open, you can reach its settings by clicking **XQuartz** in the menu bar at the **top left of the screen**, then going to **Settings** (older versions call this **Preferences**).
3. In **Settings → Security**, check **"Allow connections from network clients."**
4. **Fully quit and relaunch XQuartz** so the setting takes effect. This step is required; the setting does not apply until XQuartz restarts.
5. In Terminal, set the display and authorize local connections:
   ```
   export DISPLAY=:0
   xhost + 127.0.0.1
   ```
   You should see `127.0.0.1 being added to access control list`. If you instead get `unable to open display ""`, XQuartz is not running yet or the `export DISPLAY=:0` line was skipped. Run both lines again after confirming XQuartz is open.
6. When you get to the `docker run` step below, use the **macOS** command block.

**Apple Silicon (M1/M2/M3/M4) note:** the build installs `gcc-multilib` and `g++-multilib`, which only exist on x86. You must build and run under amd64 emulation by adding `--platform linux/amd64` to both the `docker build` and `docker run` commands (shown in the macOS blocks below). Make sure Rosetta emulation is enabled in Docker Desktop under **Settings → General**.

## Build and Run

Download the Dockerfile

### [HERE](https://github.com/LandenParke/PocketDictionary/releases/download/Simulation/Dockerfile)

Make sure to place the file into a directory in Ubuntu (or WSL2/Linux) if you are working on a different OS.

First run

```
docker --version
```

to see if you have docker. If you do not, run

```
sudo apt install docker.io
```

on Linux, or install [Docker Desktop](https://www.docker.com/products/docker-desktop/) on macOS/Windows.

Make sure the Dockerfile has no extension such as .txt, then build the image from the directory containing the file.

**Linux / WSL2:**

```
sudo docker build -t pocketdictionary .
```

**macOS (Apple Silicon):**

```
docker build --platform linux/amd64 -t pocketdictionary .
```

Then run the container using the command block for your OS.

**Linux / WSL2:**

```
xhost +local:docker
sudo docker run -it --rm -e DISPLAY=$DISPLAY -v /tmp/.X11-unix:/tmp/.X11-unix pocketdictionary
```

**macOS (Apple Silicon):**

```
docker run --platform linux/amd64 -it --rm -e DISPLAY=host.docker.internal:0 pocketdictionary
```

**Native Windows (no WSL, using VcXsrv):**

Ensure that Docker Desktop is open or else it will fail.

Find your machine's IP address first (`ipconfig`, look for your active adapter's IPv4 address), then run (replacing YOUR_IP_ADDRESS with your address):

```
docker run -it --rm -e DISPLAY=YOUR_IP_ADDRESS:0.0 pocketdictionary
```

Those commands should auto launch the UI, where you can interact with it via the command line.

Type out the romanji and it will appear on the UI, press enter to search.
Press '2' to go down through the options, and '1' to go up.

# Change me before submitting
