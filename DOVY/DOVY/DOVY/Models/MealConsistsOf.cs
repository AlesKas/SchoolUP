using System;
using System.Collections.Generic;
using System.Text;

namespace DOVY.Models
{
    public class MealConsistsOf
    {

        public int Id { get; set; }
        public Nullable<int> MealId { get; set; }
        public Nullable<int> IngredientId { get; set; }
        public Nullable<double> AmountRequired { get; set; }
        public virtual Meal Meal { get; set; }
        public virtual Ingredient Ingredient { get; set; }

    }
}
