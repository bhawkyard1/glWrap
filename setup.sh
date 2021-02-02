# pull third parties
./get_latest_repos.sh

# regenerate build folder
if [ ! -d build ]; then
  mkdir build
fi
rm -rf ./build/*
cd build

# run build
cmake ..
make

# exit folder
cd ..