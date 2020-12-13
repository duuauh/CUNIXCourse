import torch
import torch.nn as nn
from torch.nn import functional as F
import torchvision.models as models
import numpy as np
from PIL import Image
import mynet

def main():
    path = '/home/zzl/zzlWorkspace/NNInference/'
    module = torch.load(path+'MNIST/module/my_mnist.pkl')
    
    '''
    test_data = Image.open(path+"test/0.png")
    test_data = np.array(test_data)
    test_data = test_data[np.newaxis, np.newaxis,:]
    tensor_test = torch.from_numpy(test_data).float()
    torch.no_grad()
    output = module(tensor_test.cuda())
    predict = output.data.max(1)[1]

    params = list(module.named_parameters())
    conv1bias = params[1][1].cpu().detach().numpy()
    #print(conv1bias)
    '''
 
    params = list(module.named_parameters())
    f = open('../params.txt', 'w')
    conv1weight = params[0][1].cpu().detach().numpy()
    print(conv1weight[0,0,0,0])
    for i in range(16):
        for j in range(3):
            for k in range(3):
                f.write(str(conv1weight[i,0,j,k])+' ')
    f.write('\n')
    conv1bias = params[1][1].cpu().detach().numpy()
    print(conv1bias[0])
    for i in range(16):
        f.write(str(conv1bias[i])+' ')
    f.write('\n')
    conv2weight = params[2][1].cpu().detach().numpy()
    for i in range(32):
        for j in range(16):
            for k in range(3):
                for m in range(3):
                    f.write(str(conv2weight[i,j,k,m])+' ')
    conv2bias = params[3][1].cpu().detach().numpy()
    f.write('\n')
    for i in range(32):
        f.write(str(conv2bias[i])+' ')
    f.write('\n')
    fcweight = params[4][1].cpu().detach().numpy()
    for i in range(10):
        for j in range(3872):
            f.write(str(fcweight[i,j])+' ')
    f.write('\n')
    fcbias = params[5][1].cpu().detach().numpy()
    for i in range(10):
        f.write(str(fcbias[i])+' ')


if __name__ == "__main__":
    main()
