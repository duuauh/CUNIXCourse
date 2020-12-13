
mkdir datasets
wget -P datasets/ http://yann.lecun.com/exdb/mnist/train-images-idx3-ubyte.gz
wget -P datasets/ http://yann.lecun.com/exdb/mnist/train-labels-idx1-ubyte.gz
wget -P datasets/ http://yann.lecun.com/exdb/mnist/t10k-images-idx3-ubyte.gz
wget -P datasets/ http://yann.lecun.com/exdb/mnist/t10k-labels-idx1-ubyte.gz

mkdir MNIST/data/raw
gzip -c datasets/train-images-idx3-ubyte.gz > MNIST/data/raw/train-images-idx3-ubyte
gzip -c datasets/train-labels-idx1-ubyte.gz > MNIST/data/raw/train-labels-idx1-ubyte
gzip -c datasets/t10k-images-idx3-ubyte.gz > MNIST/data/raw/t10k-images-idx3-ubyte
gzip -c datasets/t10k-labels-idx1-ubyte.gz > MNIST/data/raw/t10k-labels-idx1-ubyte

mkdir test

python utils/convert_data.py

python utils/set_mxnet.py

g++ -o convertdata utils/convertdata.cpp
./convertdata
rm convertdata