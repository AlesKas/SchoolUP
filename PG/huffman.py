import json
import sys

from nodeTree import NodeTree

def huffmanCodeTree(node, left=True, binString=""):
    if type(node) is str:
        return {node: binString}
    (l, r) = node.children()
    d = dict()
    d.update(huffmanCodeTree(l, True, "0"+ binString))
    d.update(huffmanCodeTree(r, False, "1" + binString))
    return d    

def encode(string):
    freq = {}
    for c in string:
        if c in freq:
            freq[c] += 1
        else:
            freq[c] = 1

    freq = sorted(freq.items(), key=lambda x: x[1], reverse=True)
    nodes = freq

    while len(nodes) > 1:
        key1, c1 = nodes[-1]
        key2, c2 = nodes[-2]
        nodes = nodes[:-2]
        node = NodeTree(key1, key2)
        nodes.append((node, c1 + c2))
        nodes = sorted(nodes, key=lambda x: x[1], reverse=True)

    huffmanCode = huffmanCodeTree(nodes[0][0])


    for key, val in huffmanCode.items():
        huffmanCode[key] = val.rjust(8, '0')


    with open('table.json', 'w') as fp:
        res = {v : k for k, v in huffmanCode.items()}
        json.dump(res, fp)

    with open('output.bin', 'wb') as file:
        for ch in string:
            data = huffmanCode[ch]
            byte = int(data, 2)
            bit = "{0:b}".format(byte).rjust(8, '0')
            #print(f"{ch} = {bytes([byte])} = {bit} = {[key for key, val in huffmanCode.items() if bit == val]}")
            file.write(bytes([byte]))

def decode():
    with open('output.bin', 'rb') as inputFile, open('table.json', 'r') as file:
        tableDict = json.load(file)
        data = inputFile.read(1)
        res = ""
        while data:
            val = int.from_bytes(data, byteorder='big')
            bit = "{0:b}".format(val).rjust(8, '0')
            res += tableDict[bit]
            data = inputFile.read(1)
    print(res)

    with open('result.txt', 'w') as file:
        file.write(res)

if __name__ == "__main__":
    op = input("Enter command, e for encode, d for decode: ")
    if op is "e":
        with open('input.txt', 'r') as inputFile:
            string = inputFile.read()
            encode(string)
    elif op is "d":
        decode()

    else:
        print("Unsupported operation.")
        exit(-1)
