using Newtonsoft.Json;
using Newtonsoft.Json.Linq;
using System;
using System.Collections;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Edhouse
{
    class Program
    {

        static void Main(string[] args)
        {
            void printMultiply(string input)
            {
                Console.Write($"{input[0]} ");
                for (int i = 1; i < input.Length; i++)
                {
                    Console.Write($"* {input[i]} ");
                }
            }

            try
            {
                string file = File.ReadAllText(@"C:\Users\Aleš\Desktop\input.json");  //input numbers are stored in Json file, Newtonsoft.Json is needed
                var deserializedProduct = (JObject)JsonConvert.DeserializeObject(file);
                var input = deserializedProduct["input"].ToString();
                List<Tuple<long, string>> numbers = new List<Tuple<long, string>>();
                for (int i = 0; i < input.Length; i++)
                {
                    long number = 1; //neutral element to multiply
                    StringBuilder sb = new StringBuilder();
                    for (int j = 0; j < 13; j++)
                    {
                        int element = (int)Char.GetNumericValue(input[i + j]);
                        if (element == 0) //if current element is 0, sequence is skipped
                            break;
                        else
                        {
                            sb.Append(element.ToString());
                            number *= element;
                        }
                        if (j == 12)
                            numbers.Add(Tuple.Create(number, sb.ToString()));
                    }
                }
                numbers.Sort();             
                var last = numbers.Last();
                Console.Write($"{last.Item1} = ");
                printMultiply(last.Item2);
            }
            catch (Exception e)
            {
                Console.WriteLine(e.Message);
            }
            Console.ReadLine();
        }
    }
}
