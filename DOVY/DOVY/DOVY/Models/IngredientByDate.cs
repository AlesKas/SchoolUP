using System;
using System.Collections.Generic;
using System.ComponentModel.DataAnnotations;
using System.Text;

namespace DOVY.Models
{
    public class IngredientByDate
    {
        [Key]
        public int IngredientId { get; set; }
        public System.DateTime ServeDate { get; set; }
        public Nullable<double> RequiredSumAmount { get; set; }
        public string UnitOfMeasure { get; set; }
        public string IngredientName { get; set; }
    }
}
