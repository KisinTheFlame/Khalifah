rm -rf build
mkdir build
GOARCH=arm \
GOARM=7 \
GOOS=linux \
CGO_ENABLED=1 \
CC=arm-linux-gnueabihf-gcc-9 \
CXX=arm-linux-gnueabihf-g++-9 \
AR=arm-linux-gnueabihf-ar-9 \
go build -C server -o ../build/khalifah -v
