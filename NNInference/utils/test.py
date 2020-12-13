import MNISTNet
import cv2

pic_path = '../test/'

net = MNISTNet.MNISTNet('../params.bin')

f = open('../test/label.txt')
labels = f.read()

acc = 0

for i in range(9999):
    img = cv2.imread(pic_path + str(i) + '.png', cv2.IMREAD_GRAYSCALE)
    predict = net.Forward(img)
    label = int(labels[i*2])
    acc += (predict == label)

acc /= 10000

print(acc)