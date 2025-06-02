FROM playground-php-wasm:base

# Temporary install vim
RUN apt-get update && apt-get install -y vim

RUN wget https://imagemagick.org/archive/ImageMagick.tar.gz; \
    tar -xvf ImageMagick.tar.gz; \
    rm ImageMagick.tar.gz; \
    cd ImageMagick-*; \
    source /root/emsdk/emsdk_env.sh; \

    # Disable functions that are not supported by Emscripten
    ## TODO: Check if we can support these functions
    ac_cv_func_vfprintf_l=no \
    ac_cv_func_vsnprintf_l=no \
    ac_cv_func_getexecname=no \
    ac_cv_func__NSGetExecutablePath=no \
    ac_cv_func_getdtablesize=no \
        emconfigure ./configure \
            # Disable X11 support
            --without-x \
            ## Disable libm
            --disable-openmp \
            --without-threads \
            ## Build shared library
            --disable-static \
            --enable-shared; \
    export EMCC_FLAGS="-sSIDE_MODULE -D__x86_64__ -sWASM_BIGINT=1 -sERROR_ON_UNDEFINED_SYMBOLS=0 -sWARN_ON_UNDEFINED_SYMBOLS=0"; \
    if [ "${WITH_JSPI}" = "yes" ]; then \
        export EMCC_FLAGS="${EMCC_FLAGS} -sASYNCIFY=2"; \
    else \
        export EMCC_FLAGS="${EMCC_FLAGS} -sASYNCIFY=1"; \
    fi; \
    if [ "${WITH_DEBUG}" = "yes" ]; then \
        export EMCC_FLAGS="${EMCC_FLAGS} -O0 -g3"; \
    else \
        export EMCC_FLAGS="${EMCC_FLAGS} -O3"; \
    fi; \
    # Remove -lm from the Makefile
    /root/replace.sh 's/^(MATH_LIBS\s*=).*$/$1/' Makefile; \
    /root/replace.sh 's/^(MAGICK_LIBS\s*=).*$/$1/' Makefile; \
    /root/replace.sh 's/^(MAGICK_DEP_LIBS\s*=).*$/$1/' Makefile; \
    EMCC_SKIP="-lz -ledit -ldl -lncurses -lzip -lpng16 -lssl -lcrypto -lxml2 -lc -lm -lsqlite3 /root/lib/lib/libxml2.a /root/lib/lib/libsqlite3.so /root/lib/lib/libsqlite3.a /root/lib/lib/libsqlite3.a /root/lib/lib/libpng16.so /root/lib/lib/libwebp.a /root/lib/lib/libsharpyuv.a /root/lib/lib/libjpeg.a" \
        emmake make -j1; \
    emmake make install
RUN ls -la /usr/local/lib/;
# Check if the library is built as a shared library
RUN test -f "/usr/local/lib/libMagickCore-7.Q16HDRI.so";