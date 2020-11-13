import trans

from arguments import get_args

def main():
    args = get_args()
    
    if((args.usage == "csv2bin") & (args.multi_thread == False)):
        with open('student.csv','r') as csv:
            lines = csv.readlines()
            with open('student.bin', 'wb') as binary:
                for line in lines:
                    binary.write(trans.str2bin(line))
                    print(trans.str2bin(line))

    elif(args.usage == "bin2csv"):
        with open('student.bin', 'rb') as binary:
            lines = binary.readlines()
            string = trans.bin2strh(lines[0])
            print(string)
            for line in lines[1:]:
                string = trans.bin2str(line)
                print(string)
    
    elif((args.usage == "csv2bin") & (args.multi_thread == True)):
        with open('student.csv','r') as csv:
            lines = csv.readlines()
            Trans_threads = []
            index = 0
            for i in range(len(lines)):
                Trans_threads.append(trans.th_str2bin(index, lines[i]))
                index += 1
            for i in range(len(lines)):
                Trans_threads[i].start()
            for i in range(len(lines)):
                Trans_threads[i].join()
            with open('student.bin', 'wb') as binary:
                for i in range(len(Trans_threads)):
                    binary.write(Trans_threads[i].binflow)


if __name__ == "__main__":
    main()