#!/usr/bin/env python3
# coding=utf-8

import socket
import sys
import argparse

IP = '140.123.97.31'
PORT = 10001

parser = argparse.ArgumentParser()

parser.add_argument('function', help="function number", type=str)
parser.add_argument('account', help="need a account", type=str)
parser.add_argument('--password', '-p', type=str, help='need a password')
parser.add_argument('--test', '-t', action='store_true', help='test mode')
args=parser.parse_args()
#print(args.function)

try:
    if args.test:
        print("test mode~")
    # open new container
    if args.function=='00':
        msg = args.function + ',' + args.account + '  ' + args.password
    #restart container
    elif args.function=='01':
        msg = args.function + ',' + args.account
    #create new account
    elif args.function=='02':
        print("create new account")
    #remove container
    elif args.function=='03':
        msg = args.function + ',' + args.account
    else:
        print("Request code not exist")
        sys.exit(0)
except Exception as e:
    print("99,",type(e))
    sys.exit(0)

client = socket.socket()
client.connect((IP, PORT))
client.send(msg.encode())

response = client.recv(1024)
print(response.decode())

client.close()



'''

#while flag:

#msg = input("Enter your message('q' for quit):").strip()
#if fun == '00':
#msg = fun + ','+ account + ','  + password
msg = args.function + ',' + args.account + ',' + args.password
#elif fun == '01':
 #   msg = fun + ',' + account

if len(msg) == 0 :
    print("Message cannot be empty")
    #continue

client.send(msg.encode())

if msg != 'q':
    data = client.recv(1024)
    print(data.decode())

else:
    flag = False

client.close()
print("Client closed")

'''
