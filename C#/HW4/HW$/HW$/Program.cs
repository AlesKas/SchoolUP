using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using System.Text;
using System.Threading;
using System.Threading.Tasks;

namespace HW4
{
    class Program
    {
            public static void mergeSort(int[] arr, int depth)
            {
                paralelMergeSort(arr, 0, arr.Length, depth);
            }


            public static void serialMergeSort(int[] arr, int start, int end)
            {
                if (start < end)
                {
                    int mid = (start + end) / 2;
                    serialMergeSort(arr, start, mid);
                    serialMergeSort(arr, mid + 1, end);
                    merge(arr, start, mid, end);
                }
            }

            public static void paralelMergeSort(int[] arr, int start, int end, int depth)
            {
                if (start < end)
                {
                    if (depth == 0)
                    {
                        serialMergeSort(arr, start, end);
                    }
                    else
                    {
                        depth--;
                        int mid = (start + end) / 2;
                        Thread left = new Thread(() => paralelMergeSort(arr,start,mid,depth));
                        Thread right = new Thread(() => paralelMergeSort(arr,mid+1,end,depth));
                        left.Start();
                        right.Start();  
                        left.Join();
                        right.Join();
                        merge(arr, start, mid, end);
                    }
                }
            }

            public static void merge(int[] arr, int start, int mid, int end)
            {
                int l = mid - start + 1;
                int r = end - mid;

                int[] L = new int[l + 1];
                int[] R = new int[r + 1];

                for (int i = 1; i < l; i++)
                {
                    L[i] = arr[start + i - 1];
                }
                for (int i = 1; i < r; i++)
                {
                    R[i] = arr[mid + i];
                }
                L[l] = Int32.MaxValue;
                R[r] = Int32.MaxValue;

                int leftIndex = 0;
                int rightIndex = 0;

                for (int k = l; k <= r; k++)
                {
                    if (L[leftIndex] <= R[rightIndex])
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

            public static int[] getRandomArray(int count)
            {
                int[] arr = new int[count];
                Random num = new Random();
                for (int i = 0; i < arr.Length; i++)
                {
                    arr[i] = num.Next(10000);
                }
                return arr;

            }


        static void Main(string[] args)
        {
            int[] arr = getRandomArray(10000000);
            Stopwatch sw = Stopwatch.StartNew();
            mergeSort(arr, 0);
            sw.Stop();
            Console.WriteLine("Cas behu: {0}ms", sw.Elapsed.TotalMilliseconds);

            int[] arr4 = getRandomArray(10000000);
            Stopwatch sw4 = Stopwatch.StartNew();
            mergeSort(arr4, 1);
            sw4.Stop();
            Console.WriteLine("Cas behu: {0}ms", sw4.Elapsed.TotalMilliseconds);

            int[] arr5 = getRandomArray(10000000);
            Stopwatch sw5 = Stopwatch.StartNew();
            mergeSort(arr5, 2);
            sw5.Stop();
            Console.WriteLine("Cas behu: {0}ms", sw5.Elapsed.TotalMilliseconds);


            int[] arr2 = getRandomArray(10000000);
            Stopwatch sw2 = Stopwatch.StartNew();
            mergeSort(arr2, 3);
            sw2.Stop();
            Console.WriteLine("Cas behu: {0}ms", sw2.Elapsed.TotalMilliseconds);

            int[] arr3 = getRandomArray(10000000);
            Stopwatch sw3 = Stopwatch.StartNew();
            mergeSort(arr, 5);
            sw3.Stop();
            Console.WriteLine("Cas behu: {0}ms", sw3.Elapsed.TotalMilliseconds);



            Console.ReadLine();
        }
    }
}
