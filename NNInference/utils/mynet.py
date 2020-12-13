import torch
from torchvision import datasets, transforms
import torch.nn.functional as F
import os
import torch.nn as nn
from torch.autograd import Variable
import torch.optim as optim

class Mynet(nn.Module):
	def __init__(self):
		super(Mynet, self).__init__()
		self.conv1 = nn.Conv2d(in_channels=1, out_channels=16, kernel_size=3)
		self.conv2 = nn.Conv2d(in_channels=16, out_channels=32, kernel_size=3)
		self.maxpool = nn.MaxPool2d(kernel_size=2)
		self.fc = nn.Linear(3872, 10)
		self.dropout = nn.Dropout(p=0.1)
	def forward(self, x):
		x = self.conv1(x)
		x = self.maxpool(x)
		x = F.relu(x)
		#x = self.dropout(x)
		x = self.conv2(x)
		x = F.relu(x)
		x = x.view(x.shape[0],-1)
		x = self.fc(x)
		print(x)
		return F.log_softmax(x, dim=1)

def train(epoch, dataloader, module):
	for i in range(epoch):
		for batch_idx, (data, target) in enumerate(dataloader):
			data, target = Variable(data), Variable(target)
			optimizer = optim.SGD(module.parameters(), lr=0.01, momentum=0.9)
			optimizer.zero_grad()
			output = module(data.cuda())
			loss = F.cross_entropy(output, target.cuda()).cuda()
			loss.backward()
			optimizer.step()
			if batch_idx % 200 == 0:
				print('Train Epoch: {} [{}/{} ({:.0f}%)]\tLoss: {:.6f}'.format(i, batch_idx * len(data), len(dataloader.dataset), 100. * batch_idx / len(dataloader), loss.data))
	torch.save(module, "../module/my_mnist.pkl")

def test(dataloader, module):
	test_loss = 0
	correct = 0
	print("start test")
	for data, target in dataloader:
		data, target = Variable(data), Variable(target)
		print(data)
		torch.no_grad()
		output = module(data.cuda())
		test_loss += F.nll_loss(output, target.cuda(), size_average=False).data
		predict = output.data.max(1)[1]
		correct += torch.eq(target.cuda(),predict).sum()
	test_loss /= len(dataloader.dataset)
	print('\nTest set: Average loss: {:.4f}, Accuracy: {})\n'.format(test_loss, float(correct.sum())/float(len(dataloader.dataset))))
