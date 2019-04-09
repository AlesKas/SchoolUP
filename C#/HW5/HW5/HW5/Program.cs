using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Database;

namespace HW5
{
    class Program
    {

        public static void merge(Student[] arr, int start, int mid, int end)
        {
            try
            {
                int l = mid - start + 1;
                int r = end - mid;

                Student[] L = new Student[l + 1];
                Student[] R = new Student[r + 1];


                Array.Copy(arr, start, L, 0, l);
                Array.Copy(arr, mid + 1, R, 0, r);

                L[l] = new Student { Prijmeni = "ŽŽŽŽŽŽŽŽŽŽŽ" };
                R[r] = new Student { Prijmeni = "ŽŽŽŽŽŽŽŽŽŽŽ" };

                int leftIndex = 0;
                int rightIndex = 0;

                for (int k = start; k <= end; k++)
                {
                    if (L[leftIndex].CompareTo(R[rightIndex]) < 0)
                    {
                        arr[k] = L[leftIndex];
                        leftIndex++;
                    }
                    else
                    {
                        arr[k] = R[rightIndex];
                        rightIndex++;
                    }
                }
            }
            catch(Exception e)
            {

            }
        }

        public static void mergeSort(Student[] arr)
        {
            serialMergeSort(arr, 0, arr.Length);
        }


        public static void serialMergeSort(Student[] arr, int start, int end)
        {
            if (start < end)
            {
                int mid = (start + end) / 2;
                serialMergeSort(arr, start, mid);
                serialMergeSort(arr, mid + 1, end);
                merge(arr, start, mid, end);
            }
        }

       

        static void Main(string[] args)
        {
            Student[] arr = new Student[ReadonlyDB.Students.Length];
            for (int i = 0; i < ReadonlyDB.Students.Length; i++)
            {
                arr[i] = ReadonlyDB.Students[i];
            }
            mergeSort(arr);


            //zbaveni se duplicit
            Student[] nonDupl = new Student[arr.Length];
            int index = 0;
            int indexSecond = 0;
            while (indexSecond < arr.Length-1)
            {
                if(!(arr[indexSecond].CompareTo(arr[indexSecond+1]) == 0))
                {
                    nonDupl[index] = arr[indexSecond];
                    index++;
                    indexSecond++;
                }
                else
                {
                    indexSecond++;
                }
            }
            Array.Resize(ref nonDupl, index + 1);

            for(int i = 4; i < 14; i++)
            {
                Console.WriteLine(nonDupl[i].Jmeno + " " + nonDupl[i].Prijmeni);
            }
            Console.WriteLine("-------------");


            var noDuplicities = ReadonlyDB.Students.Select(p => new { p.Jmeno, p.Prijmeni }).Distinct().Skip(4).Take(10).OrderBy(p => p.Prijmeni);
            foreach(var st in noDuplicities)
            {
                Console.WriteLine(st.Jmeno + " " + st.Prijmeni);
            }


            var patak = ReadonlyDB.Students.FirstOrDefault(p => p.Rocnik == 5);
            Console.WriteLine(patak);

            var infs = ReadonlyDB.Students.Count(p => p.OborKomb == "INF");
            Console.WriteLine(infs);

            var lukas = ReadonlyDB.Students.Any(p => p.Jmeno == "Lukáš");
            if(lukas)
            {
                Console.WriteLine("Lukas is existing");
            }
            Console.ReadLine();
        }
    }
}
