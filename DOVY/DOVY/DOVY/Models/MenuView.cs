using System;
using System.Collections.Generic;
using System.Text;

namespace DOVY.Models
{
    public class MenuView
    {
        public MenuView()
        {

        }
        public int Id { get; set; }
        public int MealId { get; set; }
        public string MealName { get; set; }
        public double Price { get; set; }
        public System.DateTime ServeDate { get; set; }
    }
}
