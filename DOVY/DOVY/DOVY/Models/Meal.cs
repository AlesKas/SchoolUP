using System;
using System.Collections.Generic;
using System.Text;

namespace DOVY.Models
{
    public class Meal { 
        public Meal()
        {
            this.MealConsistsOfs = new HashSet<MealConsistsOf>();
            this.Menus = new HashSet<Menu>();
        }

        public int Id { get; set; }
        public string Name { get; set; }
        public double Price { get; set; }
        public virtual ICollection<MealConsistsOf> MealConsistsOfs { get; set; }
        public virtual ICollection<Menu> Menus { get; set; }
    }
}
