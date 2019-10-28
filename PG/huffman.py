from nodeTree import NodeTree

def huffmanCodeTree(node, left=True, binString=""):
    if type(node) is str:
        return {node: binString}
    (l, r) = node.children()
    d = dict()
    d.update(huffmanCodeTree(l, True, binString + "0"))
    d.update(huffmanCodeTree(r, False, binString + "1"))
    return d    

def main(string):
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

    print(" Char | Freq  | Huffman code ")
    print("-----------------------------")
    for char, frequency in freq:
        print(" %-4r | %5d | %12s" % (char, frequency, huffmanCode[char]))

if __name__ == "__main__":
    string = input("Enter string to encode: ")
    main(string)
