In general source files only used by a specific HAVE_* option can be deleted if this option is 
not used; but keep in mind that certain options enable other options; see the root BUSY file
for more information.

Directories such as image, gui, freetype, harfbuz or libpng may be deleted, if the corresponding 
BUSY module is not used. 

### Things required by core

- md4, md5, sha1: files included by qcryptographichash.cpp, required in any configuration
- freebsd: files included by qlocale_tools.cpp, required in any configuration
- forkfd: includes files only used by HAVE_PROCESS
- zlib: BUSY module, only used by HAVE_ZLIB and HAVE_IMAGE
- pcre16: BUSY module, only used by HAVE_RE

### Things required by net

- openssl: headers used by HAVE_SSL

### Things required by image

- libpng
- libjpeg

### Things required by gui

- harfbuzz
- freetype (Linux only)

### Things required by gui/xcb (Linux only)

- xcb
- xkbcommon

### Things required by widgets

- easing
