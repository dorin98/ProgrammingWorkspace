#!/usr/bin/env python

import sys
import random
import names

R = 0

def get_MOVE(P):
    my_randoms=[85, 76, 68, 82]
    moves=""
    ID = random.randint(0,P-1)
    for i in range(0,random.randint(3,5)):
        moves += chr(my_randoms[random.randint(0,3)])
    print 'MOVE', ID, moves

def get_PRINTSCOREBOARD():
    print 'PRINT_SCOREBOARD'

def get_MELTDOWN():
    print 'MELTDOWN', random.randint(1,30)

def get_SNOWSTORM():
    x = "{0:08b}".format(random.randint(0,2*R+1))
    y = "{0:08b}".format(random.randint(0,2*R+1))
    r = "{0:08b}".format(random.randint(0,R))
    dmg = "{0:08b}".format(random.randint(1,25))
    # CAREFUL TO ENDIANNESS 
    theNo = x + y + r + dmg
    print 'SNOWSTORM', int(theNo, 2)

def main():
    # GET RADIUS AND NO. OF PLAYERS
    R = int(input("R = "))
    P = int(input("P = "))
    testID = int(input("testID = "))
    test = 'test' + str(testID) + '.in'
    sys.stdout = open(test, 'w')
    print R, P

    # PRINT MAP
    for i in range(0,2*R+1):
        for j in range(0,4*R+2):
            print random.randint(10,8*R),random.randint(1,50), 
        print

    # PRINT PLAYERS
    for i in range(0,P):
        name = names.get_first_name(gender='male')
        pozX = random.randint(0,2*R+1)
        pozY = random.randint(0,2*R+1)
        stamina = random.randint(80,120)
        dmg = random.randint(1,60)
        print(name, pozX, pozY, stamina, dmg)

    freq=[P+3,P/3,R/3,P/2]
    cmd_list=[]
    # GENERATE COMMANDS
    for i in range(0,4):
        for j in range(0, freq[i]):
            cmd_list.append(i)
    random.shuffle(cmd_list)
    # PRINT COMMANDS
    for i in cmd_list:
        if i == 0:
            get_MOVE(P)
        elif i == 1:
            get_PRINTSCOREBOARD()
        elif i == 2:
            get_MELTDOWN()
        else:
            get_SNOWSTORM()

    
    # # # END 

if __name__ == '__main__':
    main()
