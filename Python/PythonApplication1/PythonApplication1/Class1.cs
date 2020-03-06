using System;

namespace ClassLibrary4
{
    public class Class1
    {
        private static String hellostring = "Hello from C#";
        public static string hello(string andstring)
        {
            return hellostring + " and " + andstring;
        }
        public static double getArea(double num)
        {
            return num * num;
        }
    }
}
