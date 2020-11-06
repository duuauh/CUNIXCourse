import argparse

def get_args():
    parser = argparse.ArgumentParser(description='csvfiles')

    parser.add_argument('--usage', type = str, default = "csv2bin",
                        help = "usage, default: csv2bin")
    

    args = parser.parse_args()

    return args