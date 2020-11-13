import argparse

def get_args():
    parser = argparse.ArgumentParser(description='csvfiles')

    parser.add_argument('--usage', type = str, default = "csv2bin",
                        help = "usage, default: csv2bin")

    parser.add_argument('--multi_thread', type = bool, default = False,
                        help = "to use multi-thread method or not")
    

    args = parser.parse_args()

    return args