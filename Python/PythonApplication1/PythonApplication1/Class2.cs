using System;
using System.IO;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace SimpleCMD
{
    public class Class2
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
    }
}
