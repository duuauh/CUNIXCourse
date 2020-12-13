import mynet
from torchvision import datasets, transforms
import torch
import sys

def main(mode="test"):
	if(sys.argv[1]=="train"):
		module = mynet.Mynet().cuda()
		train_dataset = datasets.MNIST(root='../data/', train=True, transform=transforms.ToTensor(), download=True)
		train_loader = torch.utils.data.DataLoader(dataset=train_dataset, batch_size=64, shuffle=True)
		mynet.train(100, train_loader, module)
	if(sys.argv[1]=="test"):
		module = torch.load("/home/zzl/zzlWorkspace/NNInference/MNIST/module/my_mnist.pkl")
		test_dataset = datasets.MNIST(root='../data/', train=False, transform=transforms.ToTensor(), download=True)
		test_loader = torch.utils.data.DataLoader(dataset=test_dataset, batch_size=16, shuffle=False)
		mynet.test(test_loader, module)

if __name__=="__main__":
	main()
