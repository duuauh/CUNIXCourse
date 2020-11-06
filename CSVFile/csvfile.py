import trans

from arguments import get_args

def main():
    args = get_args()
    
    if(args.usage == "csv2bin"):
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


if __name__ == "__main__":
    main()