using System;
using System.Collections.Generic;
using System.Text;

namespace DOVY.Models
{
    public class Warehouse
    {
        public int Id { get; set; }
        public int IngredientId { get; set; }
        public double Amount { get; set; }

        public virtual Ingredient Ingredient { get; set; }
    }
}
