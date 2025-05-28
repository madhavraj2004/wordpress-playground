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
    source /root/emsdk/emsdk_env.sh && \
    EMCC_FLAGS="-sSIDE_MODULE -D__x86_64__ -sWASM_BIGINT=1" emmake make && \
    emmake make install

