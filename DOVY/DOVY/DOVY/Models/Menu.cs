using System;
using System.Collections.Generic;
using System.Text;

namespace DOVY.Models
{
    public class Menu
    {
        public Menu()
        {
            this.Orders = new HashSet<Order>();
        }

        public int Id { get; set; }
        public int MealId { get; set; }
        public System.DateTime ServeDate { get; set; }

        public virtual Meal Jidlo { get; set; }
        public virtual ICollection<Order> Orders { get; set; }
    }
}
