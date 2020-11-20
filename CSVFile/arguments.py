import argparse

def get_args():
    parser = argparse.ArgumentParser(description='csvfiles')

    parser.add_argument('--usage', type = str, default = "csv2bin",
                        help = "usage, default: csv2bin")

    parser.add_argument('--multi_processing', type = bool, default = False,
                        help = "to use multiprocessing method or not")

    parser.add_argument('--processc', type = bool, default = False,
                        help = "to use communitaction between processes or not")
    
    parser.add_argument('--mmap', type = bool, default = False,
                        help = "to use mmap or not")
    
 
    args = parser.parse_args()

    return args