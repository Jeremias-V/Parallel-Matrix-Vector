from random import randint
from sys import stdout

LO = 0
HI = 100

def main():
    N = int(input())
    stdout.write("{}\n".format(N))
    for i in range(N):
        for j in range(N):
            string = "{}".format(randint(LO,HI))
            if(j != N-1):
                string += ' '
            stdout.write(string)
        stdout.write('\n')

    stdout.write('\n')
    for i in range(N):
        string = "{}".format(randint(LO,HI))
        if(i != N-1):
            string += ' '
        stdout.write(string)
    stdout.write('\n')
main()
