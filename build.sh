rm -rf build
mkdir build
cd interface && npm run build && cd ..
mv interface/build build/static
go build -C server -o ../build/khalifah -v