using Default;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using WebAPI.Models;

namespace HW10console
{
    class Program
    {
        static void Main(string[] args)
        {
            try
            {
                Container c = new Container(new Uri("http://localhost:59646/"));
                var products = c.Product.Where(p => p.Name.Contains("o"));
                foreach(Product p in products)
                {
                    Console.WriteLine($"{p.Name} cena v roce 2018: {p.Cena2018}, prodanych kusu: {p.Prodano2018}\n" +
                        $"Cena v predchozich letech: 2017 - {p.Cena2017}, 2016 - {p.Cena2016}, 2015 - {p.Cena2015}\n" +
                        $"Prodano v predchozich letech: 2017 - {p.Prodano2017}, 2016 - {p.Prodano2016}, 2015 - {p.Prodano2015}\n");
                }
            }
            catch(Exception e)
            {
                Console.WriteLine(e.Message);
            }
            Console.ReadLine();
        }
    }
}
