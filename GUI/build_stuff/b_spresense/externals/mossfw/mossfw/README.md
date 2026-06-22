# Motion Sensing Software Framework（MOSS-FW)
This code is a software framework for distributing data to and from each signal processing when building a signal processing pipeline using sensor data, etc.
It also includes a library of numerical operations required for signal processing.

Please refer to the documentation for details.

# How to Build Documentation

1. Installing Required Packages
sudo apt -qq -y install make ruby-dev build-essential graphviz default-jre
sudo apt -qq -y install bison flex libffi-dev libxml2-dev libgdk-pixbuf2.0-dev libcairo2-dev libpango1.0-dev fonts-lyx cmake libwebp-dev libzstd-dev
sudo gem install asciidoctor asciidoctor-pdf asciidoctor-pdf-cjk asciidoctor-diagram asciidoctor-mathematical

2. Generating Documents
> cd docs
> make

3. File to be output
- framework_spec.pdf
- framework_spec.html
- sensorlib_spec.pdf
- sensorlib_spec.html
