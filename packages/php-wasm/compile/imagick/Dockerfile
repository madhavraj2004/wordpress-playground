FROM playground-php-wasm:base

# sudo apt install php-dev
RUN apt-get update && apt-get install -y php-dev

# Install ImageMagick from source with proper configuration
# ImageMagick install configuration arguments https://github.com/ImageMagick/ImageMagick/blob/main/Install-unix.txt
RUN wget https://imagemagick.org/archive/ImageMagick.tar.gz && \
    tar -xvf ImageMagick.tar.gz && \
    rm ImageMagick.tar.gz && \
    cd ImageMagick-* && \
    ./configure && \
    make && \
    make install

# Install PHP Imagick extension
# Extension install instructions https://github.com/Imagick/imagick#installation-on-linux
RUN wget https://github.com/Imagick/imagick/archive/refs/heads/master.zip && \
    unzip master.zip && \
    rm master.zip && \
    cd imagick-master && \
    phpize && \
    ./configure && \
    make && \
    make install

