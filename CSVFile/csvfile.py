import trans
import os
from multiprocessing import Process, Pool, Queue
import mmap

from arguments import get_args

def writeToBin(name, strbuf):
    with open(name, 'r') as csv:
        line = csv.readlines()
        with open(name.replace('csv','bin'), 'wb') as binary:
            binary.write(trans.str2bin(line[0]))

def trancoding(csvq, binq):
    strbuf = csvq.get(True)
    binflow = trans.str2bin(strbuf)
    binq.put(binflow)
    #print(binq.qsize())

def main():
    args = get_args()
    
    if((args.usage == "csv2bin") & (args.multi_processing == False)):
        with open('student.csv','r') as csv:
            lines = csv.readlines()
            with open('student.bin', 'wb') as binary:
                for line in lines:
                    binary.write(trans.str2bin(line))
                    print(trans.str2bin(line))

    elif((args.usage == "bin2csv") & (args.mmap == False)):
        with open('student.bin', 'rb') as binary:
            lines = binary.readlines()
            string = trans.bin2strh(lines[0])
            print(string)
            for line in lines[1:]:
                string = trans.bin2str(line)
                print(string)

    elif((args.usage == "bin2csv") & (args.mmap == True)):
        with open('student.bin', 'r+b') as binary:
            mm = mmap.mmap(binary.fileno(), 0)
            lines = mm.readline()
            string = trans.bin2strh(lines)
            print(string)
            lines = mm.readline()
            while(lines):
                string = trans.bin2str(lines)
                print(string)
                lines = mm.readline()
    
    elif((args.usage == "csv2bin") & (args.multi_processing == True) & (args.processc == False)):
        basename = 'student.csv'
        with open(basename,'r') as csv:
            lines = csv.readlines()
            processPool = Pool(len(lines))
            for i in range(len(lines)):
                with open(basename.replace('.csv', str(i)+'.csv'), 'w') as c:
                    c.write(lines[i])
            for i in range(len(lines)):
                processPool.apply_async(writeToBin, args=(basename.replace('.csv', str(i)+'.csv'), lines[i],))
            processPool.close()
            processPool.join()
            with open(basename.replace('csv', 'bin'), 'wb') as binary:
                for i in range(len(lines)):
                    with open(basename.replace('.csv', str(i)+'.bin'), 'rb') as c:
                        tmp = c.read()
                        binary.write(tmp)
            for i in range(len(lines)):
                os.remove(basename.replace('.csv', str(i)+'.csv'))
                os.remove(basename.replace('.csv', str(i)+'.bin'))
    
    elif((args.usage == "csv2bin") & (args.multi_processing == True) & (args.processc == True)):
        csvq = Queue()
        binq = Queue()
        with open('student.csv','r') as csv:
            lines = csv.readlines()
            processList = [Process(target=trancoding, args=(csvq, binq,)) for index in range(len(lines))]
            for line in lines:
                csvq.put(line)
            for i in range(len(lines)):
                processList[i].start()
            for i in range(len(lines)):
                processList[i].join()
            with open('student.bin', 'wb') as binary:
                while(binq.qsize()):
                    tmp = binq.get(True)
                    binary.write(tmp)

if __name__ == "__main__":
    main()