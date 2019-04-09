using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace HW2
{
    class BinaryMatrix
    {
        private static int[,] binaryMatrix = new int[3,3];
        private static int col = 0;

        public BinaryMatrix()
        {

        }

        public static BinaryMatrix ReadMatrix(string path)
        {
            FileInfo fs = new FileInfo(path);
            if (fs.Exists)
            {
                StreamReader streamReader = null;
                try
                {
                    streamReader = fs.OpenText();
                    string s;
                    while ((s = streamReader.ReadLine()) != null)
                    {
                        parseTo2Darray(s);
                        Console.WriteLine(s);
                    }
                }
                catch (Exception e)
                {
                    Console.WriteLine("Chyba pri cteni souboru " + e.Message);
                }
                finally
                {
                    if (streamReader != null)
                    {
                        streamReader.Close();
                    }

                }
            }
            return new BinaryMatrix();
        }

        public override string ToString()
        {
            StringBuilder stringBuilder = new StringBuilder();
            for (int j = 0; j < 3; j++)
            {
                for (int i = 0; i < 3; i++)
                {
                    stringBuilder.Append(binaryMatrix[i, j] + " ");
                }
                stringBuilder.Append("\n");
            }
            string ret = stringBuilder.ToString();

            return (ret);
        }

        public void WriteMatrix(string path)
        {
            StreamWriter sw = null;
            try
            {
                sw = new StreamWriter(File.Create(path));
                for (int j = 0; j < 3; j++)
                {
                    for (int i = 0; i < 3; i++)
                    {
                        sw.Write(binaryMatrix[i, j] + " ");
                    }
                    sw.WriteLine();
                }
            }
            catch (Exception e)
            {
                Console.WriteLine("Zapis souboru selhal " + e.Message);
            }
            finally
            {
                if (sw != null)
                {
                    sw.Close();
                }
            }

        }

        public void set(int row, int colm, int num)
        {
            binaryMatrix[colm, row] = num;
        }

        private static void parseTo2Darray(string s)
        {
            for (int i = 0; i <= 4; i = i + 2)
            {
                
                binaryMatrix[i / 2, col] = Int32.Parse(s.Substring(i, 1));
            }
            col++;
        }
    }
}