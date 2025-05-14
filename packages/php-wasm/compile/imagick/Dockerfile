FROM playground-php-wasm:base

# Install ImageMagick from source with proper configuration
RUN wget https://imagemagick.org/archive/ImageMagick.tar.gz && \
    tar -xvf ImageMagick.tar.gz && \
    rm ImageMagick.tar.gz && \
    cd ImageMagick-* && \
    ./configure && \
    make && \
    make install

# Install PHP Imagick extension
# RUN wget https://github.com/Imagick/imagick/archive/refs/heads/master.zip && \
#     unzip master.zip && \
#     rm master.zip && \
#     cd imagick-master && \
#     phpize && \
#     ./configure && \
#     make && \
#     make install && \
#     echo "extension=imagick.so" > /usr/local/lib/php.ini

# # Verify installation
# RUN convert -version
