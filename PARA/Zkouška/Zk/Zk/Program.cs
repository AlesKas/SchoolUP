using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading;
using System.Threading.Tasks;

namespace Zk
{
    class Program
    {
        static int poc()
        {
            int i = 0;
            Thread t1 = new Thread(() => {
                for (int j = 0; j < 9; j++)
                {
                    i++;
                }
            });
            Thread t2 = new Thread(() => {
                for (int j = 0; j < 9; j++)
                {
                    i++;
                }
            });
            t1.Start();
            t2.Start();
            return i;
        }

        static int flag()
        {
            int i = 0;
            bool flag = false;
            Thread t1 = new Thread(() =>
            {
                while (!flag)
                    i = 1 - i;
            });
            Thread t2 = new Thread(() =>
            {
                while (!(i == 1))
                {
                    
                }
                flag = false;
            });
            t1.Start();
            t2.Start();
            
            return i;
        }

        static void Main(string[] args)
        {
            int i = poc();
            Console.WriteLine(i);
            Console.WriteLine(flag());
        }
    }
}
