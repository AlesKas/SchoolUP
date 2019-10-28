using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ConsoleApp1
{
    class Huffman<T> where T : IComparable
    {
        private readonly Dictionary<T, HuffmanNode<T>> _auxiliaryDict = new Dictionary<T, HuffmanNode<T>>();
        private readonly HuffmanNode<T> _root;

        public Huffman(IEnumerable<T> values)
        {
            var counts = new Dictionary<T, int>();
            var Queue = new Queue<HuffmanNode<T>>();
            int valueCount = 0;

            foreach (T value in values)
            {
                if (!counts.ContainsKey(value))
                {
                    counts[value] = 0;
                }
                counts[value]++;
                valueCount++;
            }

            foreach (T value in counts.Keys)
            {
                var node = new HuffmanNode<T>((double)counts[value] / valueCount, value);
                Queue.Add(node);
                _auxiliaryDict[value] = node;
            }

            while (Queue.Count > 1)
            {
                HuffmanNode<T> leftSon = Queue.Pop();
                HuffmanNode<T> rightSon = Queue.Pop();
                var parent = new HuffmanNode<T>(leftSon, rightSon);
                Queue.Add(parent);
            }

            _root = Queue.Pop();
            _root.IsZero = false;
        }

        public List<int> Encode(T value)
        {
            var returnValue = new List<int>();
            Encode(value, returnValue);
            return returnValue;
        }

        public void Encode(T value, List<int> encoding)
        {
            if (!_auxiliaryDict.ContainsKey(value))
            {
                throw new ArgumentException("Invalid value in Encode");
            }
            HuffmanNode<T> nodeCur = _auxiliaryDict[value];
            var reverseEncoding = new List<int>();
            while (!nodeCur.IsRoot)
            {
                reverseEncoding.Add(nodeCur.Bit);
                nodeCur = nodeCur.Parent;
            }

            reverseEncoding.Reverse();
            encoding.AddRange(reverseEncoding);
        }

        public List<int> Encode(IEnumerable<T> values)
        {
            var returnValue = new List<int>();

            foreach (T value in values)
            {
                Encode(value, returnValue);
            }
            return returnValue;
        }
    }
}
