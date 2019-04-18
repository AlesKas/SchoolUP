using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;

namespace WebAPI.Models
{
    public class Product
    {
        public int Id { get; set; }
        public string Name { get; set; }
        public int Cena2015 { get; set; }
        public int Prodano2015 { get; set; }
        public int Cena2016 { get; set; }
        public int Prodano2016 { get; set; }
        public int Cena2017 { get; set; }
        public int Prodano2017 { get; set; }
        public int Cena2018 { get; set; }
        public int Prodano2018 { get; set; }
    }
}