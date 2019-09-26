using System;
using System.IO;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace HW2
{
    class Program
    {
        public static string BytesToReadableValue(long number)
        {
            List<string> suffixes = new List<string> { " B", " kB", " MB", " GB", " TB" };

            for (int i = 0; i < suffixes.Count; i++)
            {
                long temp = number / (int)Math.Pow(1024, i + 1);

                if (temp == 0)
                {
                    return (number / (int)Math.Pow(1024, i)) + suffixes[i];
                }
            }
            return number.ToString();
        }

        //Vlastni metoda na převod nefunguje pro drives, inspirace StackOverflow
        public static string GetHumanReadableFileSize(long value)
        {
            string[] duffixes = { "bytes", "KB", "MB", "GB", "TB" };
            const long byteConversion = 1024;
            if (value < 0) { return "-" + GetHumanReadableFileSize(-value); }
            if (value == 0) { return "0.0 bytes"; }

            int mag = (int)Math.Log(value, byteConversion);
            double adjustedSize = (value / Math.Pow(1000, mag));


            return string.Format("{0:n2} {1}", adjustedSize, duffixes[mag]);
        }

        public static void cmdLine()
        {
            Console.Write("> enter drive to start: ");
            string s = Console.ReadLine();
            DirectoryInfo di = new DirectoryInfo(s);
            DriveInfo[] drives = DriveInfo.GetDrives();
            string way = null;
            if (di.Exists)
            {
                while (true)
                {
                    Console.Write(di.FullName + "> ");
                    String input = Console.ReadLine();
                    if (input != "" && input.Substring(0, 2).Equals("cd"))
                    {
                        way = input.Substring(3);
                        input = input.Substring(0, 2);
                        s = s + '\\' + way;
                    }
                    switch (input)
                    {
                        case "dir":
                            {
                                foreach (DirectoryInfo directory in di.GetDirectories())
                                {
                                    Console.WriteLine(directory.CreationTime + "\t<DIR>\t" + directory);
                                }
                                foreach (FileInfo fi in di.GetFiles())
                                {
                                    string bytes = BytesToReadableValue(fi.Length);
                                    Console.Write(fi.CreationTime + "\t" + bytes + "\t" + fi.Name);
                                    Console.WriteLine();
                                }
                                break;
                            }
                        case "cd":
                            {
                                di = new DirectoryInfo(s);
                                if (!di.Exists)
                                {
                                    throw new Exception("Direcotry does not exist");
                                }
                                break;
                            }
                        case "drives":
                            {
                                foreach (DriveInfo dI in drives)
                                {
                                    if (dI.IsReady)
                                    {
                                        string total = GetHumanReadableFileSize(dI.TotalSize);
                                        string ava = GetHumanReadableFileSize(dI.AvailableFreeSpace);
                                        Console.WriteLine(dI.Name + "\t" + "Total space: " + total + "\t" + "Availible space: " + ava);
                                    }
                                }
                                break;
                            }
                        case "exit":
                            {
                                return;
                            }

                    }

                }
            }
        }


        static void Main(string[] args)
        {
            Console.WriteLine("Press a to enter comand line, press b to load matrix:");
            string aOrB = Console.ReadLine();
            switch (aOrB)
            {
                case "a":
                    {
                        cmdLine();
                        break;
                    }
                case "b":
                    {
                        BinaryMatrix matrix = BinaryMatrix.ReadMatrix(@"D:\Matrix.txt");
                        matrix.set(2, 1, 0);
                        Console.WriteLine(matrix);
                        matrix.WriteMatrix(@"D:\MatrixOut.txt");
                        break;
                    }

            }

            Console.ReadLine();
        }
    }
}