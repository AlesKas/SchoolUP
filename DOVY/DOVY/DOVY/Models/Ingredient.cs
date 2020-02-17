using System;
using System.Collections.Generic;
using System.Text;

namespace DOVY.Models
{
    public class Ingredient
    {
        public Ingredient()
        {
            this.MealConsistsOfs = new HashSet<MealConsistsOf>();
            this.Warehouses = new HashSet<Warehouse>();
        }

        public int Id { get; set; }
        public string Name { get; set; }
        public string UnitOfMeasure { get; set; }
        public virtual ICollection<MealConsistsOf> MealConsistsOfs { get; set; }
        public virtual ICollection<Warehouse> Warehouses { get; set; }
    }
}
