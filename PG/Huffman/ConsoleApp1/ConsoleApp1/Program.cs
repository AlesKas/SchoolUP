using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ConsoleApp1
{
    class Program
    {
        private const string Example = "this is an example for huffman encoding";

        static void Main(string[] args)
        {
            var huffman = new Huffman<char>(Example);
            List<int> encoding = huffman.Encode(Example);

            var chars = new HashSet<char>(Example);
            foreach (char c in chars)
            {
                encoding = huffman.Encode(c);
                Console.Write("{0}:  ", c);
                foreach (int bit in encoding)
                {
                    Console.Write("{0}", bit);
                }
                Console.WriteLine();
            }
            Console.ReadKey();
        }
    }
}
